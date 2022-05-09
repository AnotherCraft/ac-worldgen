# AC Worldgen application interface

While it is possible to incorporate the worldgen system into your game source code, the worldgen is actually a standalone application that can be easily incorporated into any voxel project.

It works like this:

* The client starts up the `ac-worldgen` application, passing source codes and block UID -> ID mappings in arguments.
  * Block UID -> ID mapping is used for translating block literals in the woglac language (`block.XXXX`) to block IDs (`uint16_t`). The whole system is working with block IDs internally, the UIDs are used only in the compilation step.
* The client then communicates with the worldgen system through the `stdin` and `stdout` pipes of the worldgen process using line-based messages. Errors and messages are printed to `stderr`.
* The communication is very straighforward:
    * The client sends a message asking for data for a certain area (usually generated block IDs for a given chunk, but you can actually request **any** variable marked as `export` is the source code).
    * The worldgen system then **asynchronously** returns the data requested. The order of the result does not have to be the same as the order the requests came in.

That is all. The communication runs **asynchronously** and the worldgen engine can run on **multiple threads**, so it is recommended to keep the worldgen busy and always a number of data requests pending. The worldgen always works with 16×16×16 voxel chunks.

**You don't want to have the worldgen process running in multiple instances. The worldgen uses a huge cache so you might run out of memory. The application itself generates on multiple threads and the communication can be done asynchronously.**

## Usage example
A simple example how the worldgen application is to be used. First, we start the application, passing the source files and block UID mapping:
```
ac_worldgen" --sourceFile test.woglac --blockMapping "block.dirt=10,block.stone=11"
```

The `test.woglac` file can look for example like this:
```WOGLAC
export Block resultBlock = worldPos()::z() < 20 ? block.dirt : block.air;
```

Then, we ask the system to generate a 16^3 chunk on the `0,0,0` position. This is done by sending the `getData` command to worldgen `stdin`:
```
getData 0 0 0 resultBlock Block\n
```

The program then synchronously responds with the generated data:
```
data 0 0 0 resultBlock 8192\n
[8192 bytes of binary raw data]
```

**We've created a sample client code on how to communicate with the worldgen process, you can see it [here](client_example.d)."

## Program options

```
Usage: ac-worldgen (args)

-f <f> | --sourceFile <f>
Source file (accepts multiple). If relative path is provided, it is looked for in lookup directories.

-d <d> | --lookupDirectory <d>
Lookup directory for resources (for .vox, .woglac files).

-s <s> | --seed <s>
Seed for the worldgen (number).

-m <m> | --blockMapping <m>
Block UID (string) -> ID (uint16_t) mapping in format 'uid=id,uid2=id2,uid3=id3'.
Block UIDs have to be prefixed with 'block.', for example 'block.core.air'.
ID 0 is reserved for 'block.air'.
ID 1 is reserved for 'block.undefined'.

--functionList
Emits a function list in the Markdown format.--exportList
Compiles the source files and prints out the list of exports.
```

## `stdin`, `stdout` and `stderr` communication API
Communication with the application is done through **single-line** messages in format `command arg1 arg2 arg3 ... argN\n`. `stdin` is used for sending commands to the application, application then writes messages in the same format to `stdout`. `stderr` is used for printing out messages, warnings and erros, in plain text. 

### `getData` command (client -> worldgen stdin)
```
getData x y z export valueType\n
```

Field | Type | Notes
--- | --- | ---
`x`, `y`, `z` | int32 | Coordinates of the requested chunk. Has to be aligned to 16 blocks (`x,y,z & 0xf == 0`).
`export` | string | Name of the WOGLAC variable we want to get data of (the variable has to be in the root namespace and marked as `export`).
`valueType` | string | What value type the client expects to get (coresponds with WOGLAC variable types, for example `Block` or `Float`, case sensitive). If the value types do not match, worldgen returns an error.

Queries the worldgen system to generate a chunk of data (16×16×16). The request is queued and the application will eventually respond with the `data` message.

### `data` message (worldgen stdout -> client)
```
data x y z export payladSize\n
[raw payload of $payloadSize bytes]
```

Field | Type | Notes
--- | --- | ---
`x`, `y`, `z` | int32 | Coordinates of the generated chunk.
`payloadSize` | number | Size of the data payload immediately following this message (in bytes).

Asynchronous response to the `genData` request from the client, containing the requested data. The data are contained in a raw binary payload immediately following the message.

Although the worldgen system always works with the `16×16×16` voxel chunks, the message does not always return `4096` records: it can also return `256` records or even a single record. This depends on the variable dimensionality: if the variable is known to be constant everywhere in the world or same in the entire chunk, it is not necessary to send the same value 4096 times. The same applies with 2D variables (for example generated by the `perlin2D` function).

The values are returned as a flat array of `4096`, `256` or `1`records where array index `i = x + y * 16 + z * 256`. Depending on the requested variable type, following types are used:

WOGLAC type | C++ equivalent type | Byte size
--- | --- | ---
`Bool` | `uint8_t` | 1
`Block` | `uint16_t` | 2
`Float` | `float` | 4
`Float2` | `float[2]` | 8
`Float3` | `float[3]` | 12 (4-aligned)