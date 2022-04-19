# Caves
So far we've only worked with heightmap-based terrain generation, which was mostly 2D. Now let's enrich our worldgen with fully 3D elements - caves. We'll be using [3D Perlin Noise](https://en.wikipedia.org/wiki/Perlin_noise) for that. In WOGLAC, we have function `Float perlin3D(Float octaveSize, Float seed)`, which works basically the same as the `perlin2D` function, except the generated noise is 3-dimensional.

Let's see how the noise looks like:
```WOGLAC

```