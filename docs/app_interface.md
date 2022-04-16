# AC Worldgen application interface

While it is possible to incorporate the worldgen system into your game source code, the worldgen is actually a standalone application that can be easily incorporated into any voxel project.

It works like this:

* The client starts up the `ac-worldgen` application, passing source codes and block UID -> ID mappings in arguments.
  * Block UID -> ID mapping is used for translating block literals in the woglac language (`block.XXXX`) to block IDs (`uint16_t`). The whole system is working with block IDs internally, the UIDs are used only in the compilation step.
* The client then communicates with the worldgen system through the `stdin` and `stdout` pipes of the worldgen process.
* The communication is very straighforward:
    * The client sends a message asking for data for a certain area (usually generated block IDs for a given chunk, but you can actually request **any** variable marked as `export` is the source code).
    * The worldgen system then **asynchronously** returns the data requested.

That is all. The communication runs **asynchronously** and the worldgen engine can run on **multiple threads**, so it is recommended to keep the worldgen busy and always a number of data requests pending. The worldgen always works with 16×16×16 voxel chunks.

## Usage example
A simple example how the worldgen application is to be used. First, we start the application, passing the source files and block UID mapping:
```
ac_worldgen" --sourceFile test.woglac --blockMapping "{\"block.dirt\": 10}"
```

The `test.woglac` file can look for example like this:
```WOGLAC
export Block resultBlock = worldPos()::z() < 20 ? block.dirt : block.air;
```

Then, we ask the system to generate a 16^3 chunk on the `0,0,0` position. This is done by sending the `getData` command to worldgen `stdin`:
```
{"type": "getData", "export": "resultBlock", "x": 0, "y": 0, "z": 0, "valueType": "Block"}\n
```

The program then responds with the generated data:
```
{"export":"resultBlock","payloadSize":8192,"recordCount":4096,"type":"data","x":0,"y":0,"z":0}\n
[8192 bytes of binary raw data]
```

## Program options

```
  -?, -h, --help                           Displays help on commandline options.
  --help-all                               Displays help including Qt specific options.
  -f, --sourceFile <sourceFile>            Source file (accepts multiple)
  -d, --lookupDirectory <lookupDirectory>  Lookup directory for resources (for example .vox files for structure generator, accepts multiple)
  -s, --seed <seed>                        Seed for the worldgen (number)
  -m, --blockMapping <blockMapping>        Block UID (string) -> ID (uint16_t) mapping in JSON object format.
                                           Block UIDs have to be prefixed with 'block.', for example 'block.core.air'.
                                           ID 0 is reserved for 'block.air'.
                                           ID 1 is reserved for 'block.undefined'.
  -t, --threadCount <threadCount>          Number of worker threads (default: min(idealThreadCount - 2, 4))
  --functionList <functionList>            Emits a function list in the Markdown format and exists the application
  --exportList                             Compiles the source files and prints out the list of exports.
```

## `stdin` and `stdout` communication API
Communication with the application is done through **single-line JSON object** messages folowed by `\n`. The JSON message itself has to be in the compact format and not contain any newlines (except for escaped ones in the string literals). The message type is indicated by the `type` field.

The application responds to the client the same way. If the message contains the `payloadSize` field, that indicates that there are raw binary data immediately following the received message. Do not read the payload using the `readLine` function, always read exactly `payloadSize` bytes.

### `getData` command (client -> worldgen)
Field | Type | Notes
--- | --- | ---
`type` | `"getData"` |
`x`, `y`, `z` | int32 | Coordinates of the requested chunk. Has to be aligned to 16 blocks (`x,y,z & 0xf == 0`).
`export` | string | Name of the WOGLAC variable we want to get data of (the variable has to be in the root namespace and marked as `export`).
`valueType` | string | What value type the client expects to get (coresponds with WOGLAC variable types, for example `Block` or `Float`, case sensitive). If the value types do not match, worldgen returns an error.

Queries the worldgen system to generate a chunk of data (16×16×16). The request is queued and the application will eventually respond with the `data` message.

### `data` message (worldgen -> client)
Field | Type | Notes
--- | --- | ---
`type` | `"data"` |
`x`, `y`, `z` | int32 | Coordinates of the generated chunk.
`payloadSize` | number | Size of the data payload immediately following this message (in bytes).
`recordCount` | number | How many records there are in the payload (= `payloadSize / record size`).

Asynchronous response to the `genData` request from the client, containing the requested data. The data are contained in a raw binary payload immediately following the JSON message (there's still the `/n` after the message).

Although the worldgen system always works with the `16×16×16` voxel chunks, the message does not always return `4096` records: it can also return `256` records or even a single record. This depends on the variable dimensionality: if the variable is known to be constant everywhere in the world or same in the entire chunk, it is not necessary to send the same value 4096 times. The same applies with 2D variables (for example generated by the `perlin2D` function).

The values are returned as a flat array of `4096`, `256` or `1`records where array index `i = x + y * 16 + z * 256`. Depending on the requested variable type, following types are used:

WOGLAC type | C++ equivalent type | Byte size
--- | --- | ---
`Bool` | `uint8_t` | 1
`Block` | `uint16_t` | 2
`Float` | `float` | 4
`Float2` | `float[2]` | 8
`Float3` | `float[3]` | 12 (4-aligned)

### `message` message (worldgen->client)
Field | Type | Notes
--- | --- | ---
`type` | `"message"` |
`message` | string | Content of the message

Message passed to the client. Is sent only when something screws up.