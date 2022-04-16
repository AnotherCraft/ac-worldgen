# WOGLAC function list
Auto generated from the source code.

# Utility functions 

## `worldPos` 
```WOGLAC
Float3 worldPos(ComponentNode node)
```

Returns position of the provided component node in global world coordinates.
```WOGLAC
Float3 worldPos()
```

Returns world position of the currently calculated block.
## `select` 
```WOGLAC
Float select(Bool cond, Float thn, Float els)
Float2 select(Bool cond, Float2 thn, Float2 els)
Float3 select(Bool cond, Float3 thn, Float3 els)
Bool select(Bool cond, Bool thn, Bool els)
Block select(Bool cond, Block thn, Block els)
Rule select(Bool cond, Rule thn, Rule els)
ComponentNode select(Bool cond, ComponentNode thn, ComponentNode els)
```

If `cond` is `true`, returns `thn`, else returns `els`.
# Vector functions 

## `float2` 
```WOGLAC
Float2 float2(Float x, Float y)
Float2 float2(Float v)
```

Constructs a 2-dimensional vector.
## `float3` 
```WOGLAC
Float3 float3(Float x, Float y, Float z)
Float3 float3(Float2 xy, Float z)
Float3 float3(Float v)
```

Constructs a 3-dimensional vector.
## `x` 
```WOGLAC
Float x(Float2 vec)
Float x(Float3 vec)
```

Returns the `x` component of a vector.
## `y` 
```WOGLAC
Float y(Float2 vec)
Float y(Float3 vec)
```

Returns the `y` component of a vector.
## `z` 
```WOGLAC
Float z(Float3 vec)
```

Returns the `z` component of a vector.
## `xy` 
```WOGLAC
Float2 xy(Float3 vec)
```

Returns the `x` and `y` components of a vector.
## `normalize` 
```WOGLAC
Float2 normalize(Float2 v)
Float3 normalize(Float3 v)
```

Returns the vector normalized.
## `length` 
```WOGLAC
Float length(Float2 v)
Float length(Float3 v)
```

Returns euclidean length of a vector.
## `lengthExp` 
```WOGLAC
Float lengthExp(Float2 v, Float exp)
Float lengthExp(Float3 v, Float exp)
```

Returns length of a vector with the dimensional exponent being `exp` (1 = manhattan, 2 = euclidean).
## `manhattanLength` 
```WOGLAC
Float manhattanLength(Float2 v)
Float manhattanLength(Float3 v)
```

Returns manhattan length of a vector.
## `distance` 
```WOGLAC
Float distance(Float2 vec1, Float2 vec2)
Float distance(Float3 vec1, Float3 vec2)
```

Returns euclidean distance between two vectors.
## `manhattanDistance` 
```WOGLAC
Float manhattanDistance(Float2 vec1, Float2 vec2)
Float manhattanDistance(Float3 vec1, Float3 vec2)
```

Returns manhattan distance between two vectors.
## `distanceTo` 
```WOGLAC
Float distanceTo(Float3 targetWorldPos)
Float distanceTo(Float2 targetWorldPos)
```

Returns distance from the current block to `targetWorldPos` (in world coordinates).
```WOGLAC
Float distanceTo(ComponentNode node)
```

Returns distance from the current block to the provided component node.
## `distanceTo2D` 
```WOGLAC
Float distanceTo2D(Float3 targetWorldPos)
```

Returns distance from the current block to `targetWorldPos` (in world coordinates). Only considers X and Y coordinates.
## `distanceToLine` 
```WOGLAC
Float distanceToLine(Float3 p, Float3 a, Float3 b)
```

Returns distance of the point `p` to a line defined by points `a` and `b`.
# Sampling functions 

## `sampleOffset` 
```WOGLAC
Float sampleOffset(Float variable, Float3 offset)
Float2 sampleOffset(Float2 variable, Float3 offset)
Float3 sampleOffset(Float3 variable, Float3 offset)
Bool sampleOffset(Bool variable, Float3 offset)
Block sampleOffset(Block variable, Float3 offset)
Rule sampleOffset(Rule variable, Float3 offset)
ComponentNode sampleOffset(ComponentNode variable, Float3 offset)
```

Returns value of `variable` sampled on a world position of (`worldPos() + offset`).
## `sampleAt` 
```WOGLAC
Float sampleAt(Float variable, ComponentNode node)
Float2 sampleAt(Float2 variable, ComponentNode node)
Float3 sampleAt(Float3 variable, ComponentNode node)
Bool sampleAt(Bool variable, ComponentNode node)
Block sampleAt(Block variable, ComponentNode node)
Rule sampleAt(Rule variable, ComponentNode node)
ComponentNode sampleAt(ComponentNode variable, ComponentNode node)
```

Returns value of `variable` sampled on position of the given node.
```WOGLAC
Float sampleAt(Float variable, Float3 worldPos)
Float2 sampleAt(Float2 variable, Float3 worldPos)
Float3 sampleAt(Float3 variable, Float3 worldPos)
Bool sampleAt(Bool variable, Float3 worldPos)
Block sampleAt(Block variable, Float3 worldPos)
Rule sampleAt(Rule variable, Float3 worldPos)
ComponentNode sampleAt(ComponentNode variable, Float3 worldPos)
Float sampleAt(Float variable, Float2 worldPos)
Float2 sampleAt(Float2 variable, Float2 worldPos)
Float3 sampleAt(Float3 variable, Float2 worldPos)
Bool sampleAt(Bool variable, Float2 worldPos)
Block sampleAt(Block variable, Float2 worldPos)
Rule sampleAt(Rule variable, Float2 worldPos)
ComponentNode sampleAt(ComponentNode variable, Float2 worldPos)
```

Returns value of `variable` sampled on the given world position. The position doesn't have to be constant.
## `sampleGradient2D` 
```WOGLAC
Float2 sampleGradient2D(Float value, Float dist)
```

Returns 2D gradient of `value`, calculated as `float2(val[x + dist] - val[x - dist], val[y + dist] - val[y - dist]) / (1 + dist * 2)`
## `sampleAvg2D` 
```WOGLAC
Float sampleAvg2D(Float value, Float dist)
Float2 sampleAvg2D(Float2 value, Float dist)
Float3 sampleAvg2D(Float3 value, Float dist)
```

Samples at offsets (0,0), (dist,0), (-dist,0), (0,dist) and (0,-dist) and returns the average.`
# Biome functions 

## `biomeParam_nearest` 
```WOGLAC
Float biomeParam_nearest(Float var)
Float2 biomeParam_nearest(Float2 var)
Float3 biomeParam_nearest(Float3 var)
Bool biomeParam_nearest(Bool var)
Block biomeParam_nearest(Block var)
Rule biomeParam_nearest(Rule var)
ComponentNode biomeParam_nearest(ComponentNode var)
```

**This function cannot be used in the WOGLAC language. There is a special syntax construct for biome params.**

Returns value of variable $var of the nearest biome.
## `biomeParam_nearestSet` 
```WOGLAC
Float biomeParam_nearestSet(Float var)
Float2 biomeParam_nearestSet(Float2 var)
Float3 biomeParam_nearestSet(Float3 var)
Bool biomeParam_nearestSet(Bool var)
Block biomeParam_nearestSet(Block var)
Rule biomeParam_nearestSet(Rule var)
ComponentNode biomeParam_nearestSet(ComponentNode var)
```

**This function cannot be used in the WOGLAC language. There is a special syntax construct for biome params.**

Returns value of variable $var of the nearest biome that has the variable set.
## `biomeParam_weighted` 
```WOGLAC
Float biomeParam_weighted(Float var, Float exp)
Float2 biomeParam_weighted(Float2 var, Float exp)
Float3 biomeParam_weighted(Float3 var, Float exp)
```

**This function cannot be used in the WOGLAC language. There is a special syntax construct for biome params.**

Returns value of variable $var weighted across surrounding biomes. The $exp adjusts exponent for the individual weights (1 = linear interpolation).
# Structure functions 

## `spawn2D` 
```WOGLAC
Block spawn2D(Rule entryRule, Float maxRadius, Float seed, Float spawnZ, Bool spawnCondition)
```

Creates a structure procgen pass and returns generated blocks (block.undefined on places where nothing was generated to differentiate from generated block.air). Structures can expand up to `maxRadius` chunks from the entry chunk. For each (x, y, `spawnZ`) point in space, the `entryRule` is expanded if `spawnCondition` is `true`.
## `localPos` 
```WOGLAC
Float3 localPos()
```

Returns component-local position.
## `localSeed` 
```WOGLAC
Float localSeed()
```

Returns component-local seed.
# Noise functions 

## `randC` 
```WOGLAC
Float randC(Float seed)
```

Returns random value [0–1], constant everywhere.
## `randPC` 
```WOGLAC
Float randPC(Float seed)
```

Returns random value [0–1], different for each chunk.
## `rand2D` 
```WOGLAC
Float rand2D(Float seed)
```

Returns random value [0–1], different for every column.
## `rand3D` 
```WOGLAC
Float rand3D(Float seed)
```

Returns random value [0–1], different for every block.
## `valueNoisePC` 
```WOGLAC
Float valueNoisePC(Float octaveSize, Float seed, Float nodeValue)
```

Linearly interpolates between values at node points that are determined by `nodeValue`.
## `valueNoise2D` 
```WOGLAC
Float valueNoise2D(Float octaveSize, Float seed, Float nodeValue)
```

Linearly interpolates between values at node points that are determined by `nodeValue`.
## `perlin2D` 
```WOGLAC
Float perlin2D(Float octaveSize, Float seed)
```

Returns 2D Perlin noise value [-1–1].
## `perlin3D` 
```WOGLAC
Float perlin3D(Float octaveSize, Float seed)
```

Returns 3D Perlin noise value [-1–1].
## `voronoi2D` 
```WOGLAC
Float voronoi2D(Float octaveSize, Float seed, Float resultType, Float metricExponent)
```

Returns 2D Voronoi-diagram based value. 
* `resultType=0` -> distance to the edge (2ndDist-1stDist)
* `resultType=1` -> distance to the nearest point (1stDist)
* `resultType=2` -> 1stDist / 2ndDist
## `voronoi2DColored` 
```WOGLAC
Float voronoi2DColored(Float octaveSize, Float seed, Float resultType, Float metricExponent, Float coloring)
```

Same as voronoi2D, except each node now accepts `coloring`; there are no edges between nodes of the same color. For that to work, there are special `resultType` values:
* `resultType=10` -> weighted distance from center
* `resultType=11` -> nearest point coloring
* `resultType=12` -> weighted distance from border
## `poissonDisc2DBool` 
```WOGLAC
Bool poissonDisc2DBool(Float seed, Float radius)
```

Spreads points pseudorandomly on the 2D plane. Each point has a `radius` (2D dimensionality) that can be between 1 and 16. Distance of any two points is not less than sum of their radii. Returns true if there is a point on the current position or false if there isn't.
# Aggregation functions 

## `minPC` 
```WOGLAC
Float minPC(Float val)
```

Returns minimum value of `val` across the entire chunk. Expects `val` to have `2D` dimensionality.
## `maxPC` 
```WOGLAC
Float maxPC(Float val)
```

Returns maximum value of `val` across the entire chunk. Expects `val` to have `2D` dimensionality.
# Math functions 

## `min` 
```WOGLAC
Float min(Float a, Float b)
Float2 min(Float2 a, Float2 b)
Float3 min(Float3 a, Float3 b)
```

Returns minimum of the two values.
## `max` 
```WOGLAC
Float max(Float a, Float b)
Float2 max(Float2 a, Float2 b)
Float3 max(Float3 a, Float3 b)
```

Returns maximum of the two values.
## `smoothMin` 
```WOGLAC
Float smoothMin(Float a, Float b, Float k)
```

Returns smoothed minimum of the two values with smoothing radius `k`.
## `smoothMax` 
```WOGLAC
Float smoothMax(Float a, Float b, Float k)
```

Returns smoothed maximum of the two values with smoothing radius `k .
## `clamp` 
```WOGLAC
Float clamp(Float v, Float min, Float max)
Float2 clamp(Float2 v, Float2 min, Float2 max)
Float3 clamp(Float3 v, Float3 min, Float3 max)
```

Returns value `v` limited to bounds [`min–max`].
## `clamp01` 
```WOGLAC
Float clamp01(Float v)
Float2 clamp01(Float2 v)
Float3 clamp01(Float3 v)
```

Returns value `v` limited to bounds [0-1].
## `mix` 
```WOGLAC
Float mix(Float a, Float b, Float p)
Float2 mix(Float2 a, Float2 b, Float2 p)
Float3 mix(Float3 a, Float3 b, Float3 p)
```

Returns `a * (1 - p) + b * p`.
## `abs` 
```WOGLAC
Float abs(Float v)
Float2 abs(Float2 v)
Float3 abs(Float3 v)
```

Returns absolute value of the parameter
## `floor` 
```WOGLAC
Float floor(Float v)
Float2 floor(Float2 v)
Float3 floor(Float3 v)
```


## `ceil` 
```WOGLAC
Float ceil(Float v)
Float2 ceil(Float2 v)
Float3 ceil(Float3 v)
```


## `round` 
```WOGLAC
Float round(Float v)
Float2 round(Float2 v)
Float3 round(Float3 v)
```


## `fract` 
```WOGLAC
Float fract(Float v)
Float2 fract(Float2 v)
Float3 fract(Float3 v)
```

Returns fractional part of the number `x - trunc(x)`.
## `pow` 
```WOGLAC
Float pow(Float v, Float e)
```

Returns power of `v` to the exponent `e`.
## `sin` 
```WOGLAC
Float sin(Float x)
```

Returns `sin(x)`, `x` is in radians.
## `cos` 
```WOGLAC
Float cos(Float x)
```

Returns `cos(x)`, `x` is in radians.
# Basic math functions 

## `inverse` 
```WOGLAC
Float inverse(Float a)
Float2 inverse(Float2 a)
Float3 inverse(Float3 a)
```

Returns negative value of the argument (`-a`).
## `add` 
```WOGLAC
Float add(Float a, Float b)
Float2 add(Float2 a, Float2 b)
Float2 add(Float2 a, Float b)
Float3 add(Float3 a, Float3 b)
Float3 add(Float3 a, Float b)
```


## `sub` 
```WOGLAC
Float sub(Float a, Float b)
Float2 sub(Float2 a, Float2 b)
Float2 sub(Float2 a, Float b)
Float3 sub(Float3 a, Float3 b)
Float3 sub(Float3 a, Float b)
```


## `mult` 
```WOGLAC
Float mult(Float a, Float b)
Float2 mult(Float2 a, Float2 b)
Float2 mult(Float2 a, Float b)
Float3 mult(Float3 a, Float3 b)
Float3 mult(Float3 a, Float b)
```


## `div` 
```WOGLAC
Float div(Float a, Float b)
Float2 div(Float2 a, Float2 b)
Float2 div(Float2 a, Float b)
Float3 div(Float3 a, Float3 b)
Float3 div(Float3 a, Float b)
```


## `mod` 
```WOGLAC
Float mod(Float a, Float b)
Float2 mod(Float2 a, Float2 b)
Float2 mod(Float2 a, Float b)
Float3 mod(Float3 a, Float3 b)
Float3 mod(Float3 a, Float b)
```

Floating point modulo (C++ fmod)
# Basic logic functions 

## `logOr` 
```WOGLAC
Bool logOr(Bool a, Bool b)
```


## `logAnd` 
```WOGLAC
Bool logAnd(Bool a, Bool b)
```


## `logNot` 
```WOGLAC
Bool logNot(Bool a)
```


## `bool` 
```WOGLAC
Bool bool(Block a)
```

Converts to bool (returns `true` if the block is not `block.undefined`, even with air.)
# Comparison functions 

## `compEq` 
```WOGLAC
Bool compEq(Float a, Float b)
Bool compEq(Float2 a, Float2 b)
Bool compEq(Float3 a, Float3 b)
Bool compEq(Bool a, Bool b)
Bool compEq(Block a, Block b)
Bool compEq(Rule a, Rule b)
Bool compEq(ComponentNode a, ComponentNode b)
Bool compEq(Float2 a, Float b)
Bool compEq(Float3 a, Float b)
```


## `compNeq` 
```WOGLAC
Bool compNeq(Float a, Float b)
Bool compNeq(Float2 a, Float2 b)
Bool compNeq(Float3 a, Float3 b)
Bool compNeq(Bool a, Bool b)
Bool compNeq(Block a, Block b)
Bool compNeq(Rule a, Rule b)
Bool compNeq(ComponentNode a, ComponentNode b)
Bool compNeq(Float2 a, Float b)
Bool compNeq(Float3 a, Float b)
```


## `compLt` 
```WOGLAC
Bool compLt(Float a, Float b)
```


## `compGt` 
```WOGLAC
Bool compGt(Float a, Float b)
```


## `compLeq` 
```WOGLAC
Bool compLeq(Float a, Float b)
```


## `compGeq` 
```WOGLAC
Bool compGeq(Float a, Float b)
```


