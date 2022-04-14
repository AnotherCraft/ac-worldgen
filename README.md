# AC Worldgen
This is a repository for a worldgen system for AnotherCraft. The system is completely standalone and can be used for world generation in any voxel-based game.

The system uses it's own programming language called WOGLAC (WOrldGen Language for AnotherCraft), specification of the language can be found in the [ac-docs repository](https://github.com/AnotherCraft/ac-docs/tree/master/woglac).

Files in `woglac/parser` are autogenerated by Antlr4 from grammar `grammar/Woglac.g4` (you can use the `grammar/gen_parser.sh` script).

## Third-party resources
* Qt6
* Antlr4
* Tracy

## TODO
* Get rid of the Qt dependency (it's not really that necessary)