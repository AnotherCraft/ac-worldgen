# Woglac tutorial

Let's give you some quick introduction what you can do with WOGLAC and how you can do it.

### See also

* [Language reference](docs/woglac_reference.md)
* [Function list](docs/function_list.md)

## Basic contepts

Writing in WOGLAC is similar to writing shaders, though the approach is more functional. We're basically writing a function `f(x, y, z) -> block`, that takes a position as an input and returns a block that belongs on that position. This means that technically, every block can be computed completely independently (and in parallel) and you can ask for any block at any position in the world without having to generate other blocks around.

This is more or less true even in practice, except the worldgen system works with 16×16×16 chunks and uses some heavy caching for the temporary results.

## Tutorials

1. [Flatlands](tutorial/01_flatland.md)
2. [Hills](tutorial/02_hills.md)
3. [Caves](tutorial/03_caves.md)
4. [Voronoi/Worley noise, mountains](tutorial/04_voronoi.md) 
5. [Domain warping](tutorial/05_warping.md)
6. Biomes
7. Structures
8. VOX imports