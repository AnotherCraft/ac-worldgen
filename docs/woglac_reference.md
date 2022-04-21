# WOGLAC documentation
WOrldGen Language for AnotherCraft or WOGLAC is a language used for describing procedural generation. It has been made for the AnotherCraft game, but the concepts and design are suitable to be used in any voxel based game.

Procedural generation using this system can be fully deterministic - from the same seed, you always get the exact same results (also regardless of in what order you generate the chunks).

### See also
* [Tutorial](docs/woglac_tutorial.md)
* [Function list](docs/function_list.md)

## Core concepts
The language is declarative, using the functional paradigm. The syntax is loosely inspired by C++, but the syntax is heavily adjusted for the worldgen purpose. Writing in WOGLAC is similar to writing shaders in a way where a single shader invocation corresponds with a generation of a single voxel in the world. You can think of it as either writing the code for all the blocks in the world at once or as writing the code for a single block in the world specifically.

The language encapsulates two concepts: the per-block generation as mentioned before plus it also supports generating structures based on grammar-like system with depth-first search. The generation process is fully deterministic, dependent only on the seed value pased to the world generator.

The language is parsed in two passes, so in expressions it is possible to refer to variables/symbols that are defined later in the code. Exception for this are target specifiers, it is not possible to add symbols to scopes defined later in the code. So for example it is possible to do

```WOGLAC
Float a = b + 3; // Ok, In expressions you can use symbols that are defined later
Float b = 1;
```

but it is not possible to do

```WOGLAC
Float test.x = 3; // Not ok: the namespace must be declared first
namespace test;
```

# Lexical

## Keywords
Keywords are:

	area, biome, block, component, condition, extend, false, include, node, overlap, param, pragma, rule, true, void

## Comments
WOGLAC uses standard C++ comment syntax. Block comments can be nested however.
```WOGLAC
// This is a line comment.
/*
	This is a block comment.
	/* Block comments can be nested. */
	This is till a block comment.
*/
```

## Literals
> ```g4
> NumericLiteral: ('#' | '~')? '-'? ([0-9]+ ('.' [0-9]+)? | '.' [0-9]+);
> BlockLiteral: 'block.' [a-zA-Z.0-9]+;
> Identifier: [a-zA-Z_][a-zA-Z_0-9]*;
> ```
* Standard numeric literals.
  * Numeric literals can be optionally prefixed with either `~` or `#`. These have no actual impact on the code, but they have a descriptive semantic.
  * `~` prefix denotes that the numeric literal specifies octave size
  * `#` prefix denotes that the literal specifies a seed
* Identifiers
* `true/false`
* Block literals in form `block.x.y`

# Syntax & semantics

## Scopes and namespaces
> ```g4
> scope: (extend='extend'? type= ('namespace' | 'rule' | 'component' | 'biome') id= extendedIdentifier)? ('{' content+= statement* '}' | ';');
> 
> extendedIdentifier:	id+= Identifier ('.' id+= Identifier)*;
> ```

WOGLAC supports variable scopes and namespaces similar to C++. For named scopes (namespaces, rules, ...), all variables are accessible using the `scope.variable` syntax.

### Definition targets
Most of the definitions can be defined in a scope different to the current scope. This can be done in different ways, depending on the particular definition syntax. The correct way is specified in each definition syntax.
1. In format `scopeType target.id`
   * For example `namespace a.b {}`
1. In format `targetType target definitionType id`
   * For example `component test node (0, 0, 0) x;`
1. Rule expansion has a specific syntax `rule target -> component`

### Extending scopes
While it is not possible to create two scopes with the same identifier (in the same scope), it is possible to use the `extend` keyword and extend an existing scope. Extending works in the same way as if the symbols were added to the original symbol definition.

```WOGLAC
namespace test {
	Float a = 0;
}

namespace test { // Error - cannot redefine namespace
	Float b = 0;
}

Float c = test.b + 1; // Ok - using b from the extension specified below

extend namespace test {
	Float b = 0; // Ok – namespace test now contains both a and b
}
```

### Identifier lookup
Identifier resolution is done as in C++, identifier is first looked up in the current scope, then in the parent scope, and so on. When using scope targets, the identifier resolution is not altered and is still using the actual scope hierarchy as written in code.

```WOGLAC
Float a = 0;

namespace nam {
	Float b = a;
};

Float c = nam.b;

namespace nam2 {
	Float d = 0;

	namespace nam.nam3 {
		Float e = a;
		Float f = nam.b;
		Float g = d;
		Float h = b; // Error - although b is in the parent 'nam' namespace, identifier lookup is done based on the hierarchy defined in code.
	}
}
```

## Types
* `Float`: numeric value
  * Standard numeric literal, for example `0.5`
* `Float2, Float3`: 2- or 3-component float vector
  * Can be constructed using functions `float2(x, y)` and `float3(x, y, z)`.
  * Important function `Float3 worldPos()` 
  * You can get components using the `x`, `y`, `z`, `xy` and similar functions. Is is recommended to use the inline function call syntax, so `vec::x()`.
* `Bool`: boolean true/false
  * Literals `true` and `false`
* `Block`: represents a block type (internally `uint16_t`)
  * Literal in form `block.XXXX` (looks up the block UID). Special common values are `block.air` and `block.undefined`.
* `Rule`: pointer to a structure rule

## Programming conventions
* Types and rules are in `PascalCase`. Variables, biomes, namespaces are in `dromedaryCase`. This is actually enforced by the compiler.
* `~x` prefix is heavily recommended for numeric literals specifying octave sizes.
* `#x` prefix is heavily recommended for numeric literals specifying a seed.
* The recommended way to span ternary operator expression across multiple lines is like this:
	```
	Block resultBlock =
		z < 10 ? block.core.dirt :
		z < 11 ? block.core.grass :
		block.air
		;
	```

## Expressions
WOGLAC supports standard expression syntax:
| Syntax | Description |
| - | - |
|`cond ? then : else` | Ternary expression (`then` can be omitted, in that case `cond` doubles as `then`; calls `select`) |
| `||, &&` | Logical and/or (calls `logOr/And`) |
| `==, !=, >, >=, <, <=` | Comparison (calls `compEq/Neq/Lt/Gt/Leq/Geq`) |
| `+, -` | Add/subtract (calls `add`/`sub`) |
| `*, /` | Multiply/divide (calls `mult`/`div`) |
| `+a, -a, !a` | Unary +/- (+ does nothing, - negates /calls `inverse`/]), logical not (calls `logNot`) |
| `(a)` | Parentheses |

## Function calls
There are two function call syntaxes:
* The standard syntax: `function(arg1, arg2, arg3)`.
* The inline syntax: `arg1::function(arg2, arg3)`.
  * This syntax can be better for some cases, for example `vec::x(), vec::length()`.
  * The function calls can be chained this way easily, for example `vec3::xy()::length()`.
  * This is similar to the [Uniform function call syntax](https://en.wikipedia.org/wiki/Uniform_Function_Call_Syntax).

## Pragmas
> ```g4
> 'pragma' id= extendedIdentifier ('=' val= literalExpression)? ';';
> ```

Pragmas are used for altering various behaviour of the procgen. They are mostly used in the grammar-based procgen subsystem.

### Root pragmas
<center>

| Pragma | Type | Default value | Description |
| --- | --- | --- | --- |
`biomeGridSize` | `Float` | `256` | Size of the biome grid. Must be power of two and `>= 16`.

</center>

# Standard procgen
Standard procgen is basically all about defining the `resultBlock` and `chunkZOffset` variables. This is specific to AnotherCraft, you can use any variables you want in your own projects.
```WOGLAC
export Float chunkZOffset = ...;
export Block resultBlock = ...;
```

The `resultBlock` variable represents the block type that is generated by the worldgen. The worldgen code is evaluated for every block in the world (not at once, it is done so on request when the worldgen needs to generate another area).

The `chunkZOffset` variable denotes the Z offset of a chunk in the world. This is specific to the AnotherCraft implementation, where there are chunks of fixed size 16 × 16 × 256 blocks. Chunks are arranged to a 2D grid, meaning there is infinite space in the X and Y axes, but the Z axis (vertical) is limited to only 256 blocks. However, each chunk can start in a different height, allowing the terrain to have unlimited elevation as long as the gradient is not too steep (you cannot elevate more than by 256 blocks of height over 16 horizontal blocks). The `chunkZOffset` defines the elevation of each chunk. Expected dimensionality of this parameter is `PC`. The elevation is rounded to 16 blocks.

Simple example worldgen would be:
```WOGLAC
Float chunkZOffset = 0;
Block resultBlock = worldPos()::z() < 10 ? block.core.dirt : block.air;
```

This worldgen would generate a flatland with 10 blocks of dirt vertically as a ground.

## Variables
> ```g4
> variableDefinition:	exportFlag='export'? type=Type id=extendedIdentifier '=' val=expression ';';
> ```
From a formal perspective, all variables/values can be considered to be fields. That means that a variable can have different values for every point in the space (for each voxel). The variance can be achieved by using functions dependent on the position in the world, such as `worldPos` or noise functions like `perlin2D` or `rand2D`.

Variables are defined in a standard syntax mentioned above, for example:
```WOGLAC
Float a = 3;
```

Once defined, variable value cannot be changed. It is possible to refer to variables defined further in the code, however circular dependency will result in a compilation error.
```WOGLAC
Float a = b + 1; // Ok
Float b = 5;

Float c = d + 1;
Float d = c + 1; // Error: circular dependency
```

### Dimensionality
Dimensionality of a value denotes how much the value changes in relation to position in the world. Some functions, such as `perlinX` or `voronoiX` have multiple variations generating different dimensionality output. Some parameters expect values of certain dimensionality and ignore any data with higher dimensionality.
* `C` | Constant dimensionality
  * Fields with this dimensionality have the same value across the entire world space.
  * Parameters expecting this dimensionality are sampled on position (0, 0, 0).
* `PC` | Per chunk sub-2D dimensionality
  * Fields with this dimensionality have the same value in each horiontal chunk (16 × 16 × entire Z axis, aligned).
  * Parameters expecting this dimensionality are sampled on position (chunkX, chunkY, 0).
* `2D` | 2D dimensionality
  * Fields with this dimensionality have the same value across the entire Z axis.
  * Parameters expecting this dimensionality are sampled on position (x, y, 0).
* `3D` | 3D Dimensionality
  * Fields with this dimensionality can have different value for each position in the space.
  * Parameters expecting this dimensionality are sampled everywhere.

### Overriding
TBD

## Biomes
Biomes is an important subsystem of the procgen system. Biomes are abstract structures that split the world into areas where each area can have different properties assigned. Biomes have two important concepts:
* **Biome conditions** specify conditions under which a specific biome can be selected for a given area.
* **Biome parameters** speficy user-defined parameters usable for altering the character of the proccedural generation.

Biome system works as follows:
1. The world is split into 2D array of tile size 256 × 256 blocks (16 × 16 chunks) (can be changed using the `biomeGridSize` pragma)
1. Node point is randomly selected for each tile
1. Condition fields are evaluted for each biome type at the point the node point in each tile (sampling point is aligned to the chunk origin).
1. A biome with the most fitting conditions is assigned to the given tile.

As a result, we have a grid (larger than chunk grid) where each tile has assigned a biome plus a node point.

### Biome conditions
> ```g4
> biomeConditionStatement: ('biome' biome=extendedIdentifier?)? 'condition' param=extendedIdentifier '=' mean=NumericLiteral '+-' dev=NumericLiteral ';';
> ```

Biome conditions specify under what conditions a biome can be selected for a given area.

The condition is specified in format `condition field = meanValue +- deviation;` where:
* `field` can be any arbitrary field variable (it is recommended to use `2D` dimensionality or less for performance).
* `meanValue` specifies the ideal value of the field variable for the biome to be selected.
* `deviation` specifies acceptable range of around the `meanValue`.

A biome can be selected even if one of its conditions is outside the range specified by deviation. A biome can have any number of conditions. Biomes with larger number of conditions are slightly prioritized over biomes with less conditions.

Examples:
```WOGLAC
Float temperature = 20 + perlin2D(~32, #2524) * 20; // In °C
Float humidity = 50 + perlin2D(~32, #325632) * 50; // In %

biome desert {
	// Desert wants high temperatures and low humidity
	condition temperature = 30 +- 5;
	condition humidity = 0 +- 30;
}

biome tundra;

// You can also define conditions outside the biome scope
biome tundra condition temperature = 0 +- 10;
```

### Biome params
> ```g4
> biomeParamDefinition: 'biome' 'param' type=Type id=extendedIdentifier '?=' defaultValue=expression ';';
> paramSetStatement: (targetType=('biome' | 'rule' | 'component') target=extendedIdentifier)? 'param' param=extendedIdentifier '=' value=expression ';';
> biomeParamExpression: 'biome' '(' method= Identifier ',' param= extendedIdentifier (',' params+= expression)* ')';
> ```

Biome parameters are a form of field variables that can have different values assigned to each biome. Those values can then be interpolated across biome transitions.

First, it is required to declare a biome parameter. For example:
```WOGLAC
namespace test {
	biome param Float terrainHeight ?= 10;
	biome param Block groundBlock ?= block.core.dirt;
}
```
With the code above, we have defined a biome parameter `test.terrainHeight` of type `Float` and with default value `10`. After that it is possible to set the parameter value for any biome. If the parameter is not set for a biome, the default value is used instead. Please note that neither the default value or the set values have to be constant – you can use anything the language provides.

```WOGLAC
biome desert param test.terrainHeight = 20;
biome desert param test.groundBlock = block.core.sand;

extend biome tundra {
	param test.groundBlock = block.core.ice;
}
```

There are multiple methods on how to read the parameter values for a given position:
1. `biome(param, nearest)` returns `param` of the nearest biome to the current world position.
1. `biome(param, nearestSet)` returns `param` of the nearest biome to the current world position that has the parameter set (not left to the default value). If no biomes nearby have the parameter set, default value is returned.
1. `biome(param, weighted, exponent)` return `param` weighted across surrounding biomes. `exponent` specifies exponent of the weighting – the larger the number is, the steeper is the interpolation. This method can be used only for `param` of numerical types (`Float, Float2, Float3`).

All the parameter reading methods consider distances not to the biome tile boundary, but to the tile node point (as described above). Parameter types are not limited to numerical values (except for the `weighted` method).

```WOGLAC
Float resultTerrainHeight = biome(test.terrainHeight, weighted, 1); // Interpolate terrain height across biomes
Block resultGroundBlock = biome(test.groundBlock, nearest); 

Block resultBlock = worldPos()::z() <= resultTerrainHeight ? resultGroundBlock : block.air;
```

# Functions
> ```g4
> functionCallExpression: id= Identifier args= arugmentListExpression;
> arugmentListExpression: '(' (args+= expression ( ',' args+= expression)* ','?)? ')';
> ```

See `woglac_functions.md` for the list of functions with descriptions.

There are two ways to call functions: `func2(func(arg1, arg2, arg3), arg4, arg5)` and `arg1::func(arg2, arg3)::func2(arg4, arg5)`.

## Common function parameters

### `seed`
The WOGLAC procedural generation is fully deterministic. To ensure that the noise/random generation function always return the same values (even if you move them around in the code), they require the `seed` parameter. This value is combined with the world seed and serves as a seed for pseudorandom generator for the given function.

* The expected dimensionality is always `C`.
* Common practice for generating seed values is to just randomly bash on the numeric keyboard.
* It is heavily recommended (for code readability) to prefix numeric values passed to this parameter with the `#x` prefix.

Example:
```WOGLAC
perlin2D(~1, #2432); // Generates perlin noise with seed 2432 (the seed is combined with the world seed)
```

### `octaveSize`
The `octaveSize` parameter denotes scaling of a generator function, is usually in the units of chunks. This value has to always be a whole number >= `1`, otherwise the functions will not work properly.

* The expected dimensionality is always `C`.
* It is heavily recommended (for code readability) to prefix numeric values passed to this parameter with the `~x` prefix.

Example:
```WOGLAC
perlin2D(~1, #2432); // Generates perlin noise with octave size of 1 chunk
```

## Function list
See `woglac_functions.md` for the list of functions with descriptions.

# Grammar-based procgen
As an addition to the functional-based procgen, the system provides a grammar-based procgen system for generating various structures
* The system is based on defining smaller structure parts called **components** that are connected in various ways similar to lego bricks.
* Then there are **rules** that define ways in how the various components can be connected.
* Components are connected through **nodes** – those are placed inside components and define mounting points where other components can be connected to.
* To prevent overlapping, **areas** can be used. Areas are also defined inside the components. The worldgen generates structures in a way that forbids overlapping of the areas with the same name. If you don't define areas, your structures can overlap.

The structure generation process works like this:
* First, the spawning position and entry rule is determined (passed as spawning function parameters).
* There is a stack of unprocessed rules. The rule on the top of the stack is the one currently processed.
* When rule is added on the stack, list of possible expansions is generated.
* System then attempts to find a valid expansion for the rule.
* Expansions usually result in spawning a component. Components can contain nodes that expand into further components based on further rules.
* This expansion traversal is done in a breadth-first manner (by default, can be altered to depth-first using the `depthFirstProbability` rule pragma), meaning the system first attempts to fully expand a current expansion candidate with all its dependencies before it gives up and tries another candidate.

### Spawning the structures
For structure spawning, `spawn*` function family is used (more on that can be found on the function documentation page). But the basic idea is that the `spawn*` function realises a structure generation pass and returns a field representing blocks of the generated structures.

Spawn function have these parameters:
* `entryRule` determines the root rule used for spawning a structure. This is again a field value parameter, meaning you can have different entry rules for each block in the world.
* `maxRadius` determines maximum radius (in chunks) of spawned structures from their spawning point.
  * If the structure spawned goes further than the `maxRadius` from the spawn point, the behaviour is undefined, the structure is cut off on the boundary.
  * Set this parameter to a minimal reasonable value – larger values can have performance impact on the worldgen.
* `seed` is self-explanatory :)
* Then there are parameters that determine the position of spawn points. Basically, for every point in the world, it is determined if a structure should be spawned there or not.

The result of the function is then a field of blocks. `block.undefined` is returned for positions where no structure/block was generated. This is to determine where structures explicitly require air and where they don't care about what block is there.

In a single structure pass, infinite number of structures can be generated. It is up to the worldgen programmer to make sure that the structures don't overlap. No overlap checking is done between components from different structures (from different spawn points). If overlap happens, block of one of the structures is returned in an unspecified manner.

### Expressions inside grammar-based procgen
In grammar-based procgen, you can use everything from the functional part. That means that all variables defined are fields and can have different values for different positions in the world. You can also refer to field variables defined outside the structures - for example you can make your structure spawning dependent on the terrain height.

## Components
As stated before, components are building blocks of structures. They contain blocks, nodes and areas.

Each component has its own local coordinate system (however you can still access the global coordinate system using the `worldPos()` function). The coordinate system differs from the world coordinate system:
* Since the components are placed into various places in the world, the coordinates are translated.
* Components can also be rotated (both horizontally and vertically) or mirrored, depending on the expansion rules.

If expressions for block, node or area positions are fields, they are sampled at the entry point of the component (position of the spawing rule). Instead of using separate component expressions syntax `(Float x, Float y, Float z)`, it is also possible to use vector expression syntax `(Float3 v)`, for example `node (float3(1, 1, 1)) x;`.

### Component blocks
> ```g4
> componentBlockStatement:
>	('component' target=extendedIdentifier)? 'block' startPos=positionExpression endPos=positionExpression? '=' val=expression ';';
>
> positionExpression:
>	'(' (x= expression ',' y= expression ',' z= expression | vec= expression) ')';
> ```

There are multiple ways to define what blocks a component constists of. You can set each block programatically, for example:
```WOGLAC
component example {
	block (0, 0, 0) = block.core.stone;
	block (0, 0, 1) = block.core.bricks;
}
```
and so on. This syntax means that on the position `(0, 0, 1)` (x, y, z), a stone block will be spawned, and so on.

You can also set blocks for a whole area:
```WOGLAC
component example {
	block (0, 0, 0) (0, 0, 5) = block.core.stone;
}
```
This syntax means theat all blocks between `(0, 0, 0)` and `(0, 0, 5)` (inclusive) will be set to stone.

You are, however, not limited to constant block types. The component block syntax accepts any field expression, so you can for example do this:
```WOGLAC
component example {
	Float radius = 5;
	Float3 center = float3(5, 5, 5);
	block (0, 0, 0) (10, 10, 10) = localPos()::distance(center) < radius ? block.core.stone : block.undefined;
}
```
This would for example generate a sphere with radius 5 and center at `(5, 5, 5)`. Instead of writing out individual components, you can also use a single expression of type `Float3`.

### Component areas
> ```g4
> componentAreaStatement:
>	('component' target=extendedIdentifier)? 'area' startPos=positionExpression endPos=positionExpression ('(' canOverlap='#'? mustOverlap='!'? isVirtual='?'? ')')? name=Identifier? ';';
> ```

By default, components can be spawned in such way that they overlap each other. To prevent this, it is necessary to define areas. Once they are defined, the structure generator ensures that no areas with the same name overlap. Areas are always cuboid shaped.

```
component c {
	area (0, 0, 0) (5, 5, 5) areaName;
}
```

The code above will create an area spanning across the given coordinates (inclusive). The name of the area can be omitted (the overlap will then be checked against all other areas that don't have a name).

Areas can have their behaviour altered optionally:
```WOGLAC
component c {
  area (0, 0, 0) (1, 1, 1) (# ! ?) areaName;
}
```
* The `#` symbol can be used to specify that the area actually can overlap a previously spawned area (but further spawned areas cannot overlap this area).
* The `!` symbol can be used to specify that the area is **required** to overlap some previously spawned area.
* The `?` symbol can be used to specify that the area is virtual – it is used only for checking and further areas should completely ignore it.

### Component includes
> ```g4
> componentIncludeStatement:
>	'component' 'include' file=StringLiteral '{' content+= componentIncludeStatementParam* '}';
>
> componentIncludeStatementParam:
>	block= componentIncludeStatementBlockParam
>	| node= componentIncludeStatementNodeParam;
>
> componentIncludeStatementBlockParam:
>	id=NumericLiteral '->' 'block' val=expression ';';
>
> componentIncludeStatementNodeParam:
>	id=NumericLiteral '->' 'node' com=componentNodeStatementCommonPart;
> ```
Instead of defining the component blocks manually in code, it is also possible to import components from files.

Supported file formats:
<center>

File format | Supported editors
| --- | --- |
[vox](https://github.com/ephtracy/voxel-model/blob/master/MagicaVoxel-file-format-vox.txt) | [MagicaVoxel editor](https://ephtracy.github.io/) <br> [Goxel editor](https://goxel.xyz/)

</center>

Voxel files can be imported using the `component include` syntax construct:
```WOGLAC
component c {
	component include "file.vox" {
		0 -> block block.core.stone;
		1 -> node (x+) n1 -> Rule;
	}

	node (2, 2, 2) n2;
}
```

Voxel files use internal voxel identification using numerical IDs. During import, mapping from those voxel file ids to is defined - the voxels can be mapped to actual blocks using the `(id) -> block (block);` syntax or nodes can be created using the `(id) -> node (...);` syntax.

The type of the block mapped to a certain ID can again be a field expression:
```WOGLAC
component c {
	Block block0 = rand2D(#2542) < 0.5 ? block.core.stone : block.core.dirt;

	component include "file.vox" {
		0 -> block block0;
	}
}
```

### Component pragmas
<center>

| Pragma | Type | Default value | Description |
| --- | --- | --- | --- |
`allowMirroring` | `Bool` | `false` | Allow mirroring of the component

</center>


## Component nodes
> ```g4
> componentNodeStatement:
>	('component' target=extendedIdentifier)? 'node' pos=positionExpression cmn=componentNodeStatementCommonPart;
>
> componentNodeStatementCommonPart:
>	prop=componentNodePropertiesSection? group=Identifier? ('->' rule_=extendedIdentifier)? contentOrSemicolon;
>
> componentNodePropertiesSection:
>	'(' notAdjacent='='? horizontalEdge='|'? verticalEdge='-'? ori=componentNodeOrientationExpression (ori2=componentNodeOrientationExpression)? ')';
>
> positionExpression:
>	'(' (x= expression ',' y= expression ',' z= expression | vec= expression) ')';
> ```

Nodes define mounting points where the components can be connected with other components. Nodes have an optional identifier that allows using the node as a spawn point for rules. Node names are not unique - you can have multiple nodes with the same name. When using a node name in expressions (when using the nodes as arguments for functions), the first defined node with that name is used. Further defined nodes can be accessed using `nodeName_2`, `nodeName_3` etc.

Same as in the component block statements, the node position can be an expression.

Basic node definition can be done like so:
```WOGLAC
component c {
	node (0, 0, 0) n;
}
```
This will create node `n` on position `(0,0,0)`. This node can be used as a spawn point for the component in rules.

As mentioned before, it is possible to define multiple nodes with the same name:
```WOGLAC
component c {
	node (0, 0, 0) n;
	node (0, 0, 5) n;
}
```
In this case, one of the nodes would be randomly selected to be used as a spawnpoint (and if that failed, the other one would be selected).

Nodes can also be used for spawning futher rules and components:
```WOGLAC
rule R {
	// ...
}
component c {
	node (0, 0, 0) n -> R;
}
```
This node would expand according to rule `R`.

### Component node orientations
![](etc/img/nodeOrientations.png)

It is usually useful to connect components in such way that the connection is seamless. For example you can have a T-shaped intersection corridor and you want the components to connect corretly in the way that is illustrated in the image above.

For these use cases, it is possible to specify node orientation. That can be achieved by adding extra parentheses after the node position and specifying the orientation in there (corresponds to the `componentNodePropertiesSection` nonterminal in the grammar):
```WOGLAC
component c1 {
	node (0, 0, 0) (x-) n1;
	node (1, 1, 0) (y+) n2;
	node (2, 0, 0) (x+) n3;
}
```

There are six possible orientations: `x-, x+, y-, x+, z-, z+`. Additionally, it is possible to specify secondary oritentation perpendicular to the primary one. The secondary orientation determines where is "up". So it is possible to rotate the components both horizontally and vertically.

When the orientation is specified for nodes, they're by default set as adjacent – meaning that they are connected in a way so the connecting nodes are adjacent to each other and they do not occupy the same block. If you want the nodes to overlap, set the `adjacent` pragma for the node to `false`:
```WOGLAC
node (0, 0, 0) n {
	pragma adjacent = false;
}
```
or add `=` to the beginning of the orientation parenthesis expression:
```WOGLAC
node (0, 0, 0) (= x+) n;
```

### Edge component nodes
![](etc/img/nodeEdges.png)

In certain situations, for example when you have even block count wide corridors, the point of symmetry/connection is not in the center of a block but on the edge. For that, nodes can be defined to operate on an edge. This can be configured separately for vertical and horizontal direction using the `horizontalEdge` and `verticalEdge` pragmas. There is also a special syntax for it where you can put `|` (for horizontal edge) and `-` (for vertical edge) in the node orientation parenthesis (the required order is `(=|- primaryOri secondaryOri)`).

### Component node pragmas
<center>

| Pragma | Type | Default value | Description |
| --- | --- | --- | --- |
`allowRotation` | `Bool` | `true` for `z-, z+` and `false` for `x-, x+, y-, y+` | Allows rotation perpendicular to the component orientation normal 
`adjacent` | `Bool` | `true` is orientation is set, otherwise `false` | Connect nodes in a way so they don't overlap but are adjacent
`horizontalEdge` | `Bool` | `false` | Connect nodes not on the center of the block, but on the right edge (in relation to the node orientation)
`verticalEdge` | `Bool` | `false` | Connect nodes not on the center of the block, but on the top edge (in relation to the node orientation)

</center>

## Rules
Rules define... well rules of what component will actually be spawned. The used terminology is that rules *expand* into components. A rule can have multiple possible expansions, each with different priority and probability. 

### Rule pragmas
<center>``

| Pragma | Type | Default value | Description |
| --- | --- | --- | --- |
`depthFirstProbability` | `Float` | `0` | Probability that the rule will expand depth-first (will put current rule expansions to the top of the queue) opposed to breadth-frist (would add current rule expansions to the end of the queue)

``</center>

### Rule expansions
> ```g4
> ruleExpansionStatement:
>	'rule' target=extendedIdentifier? '->' (expansionTarget=extendedIdentifier ('::' node=Identifier)? | 'void') ('!' priority=NumericLiteral)? (':' probabilityRatio=NumericLiteral)? content=contentOrSemicolon;
> ```

```WOGLAC
component c1 {
	node (0, 0, 0) n1;
}
component c2 {
	node (0, 0, 0) n2;
	node (0, 0, 5) n2;
}
rule R {
	rule -> c1::n;
	rule -> c2::n;
}
component c3 {
	node (1, 0, 0) n3 -> R;
}
```

In the example above, component `c3` has a node `n3` that expands according to rule `R`. Rule `R` can expand either to component `c1` on the node `n1`, or to component `c2` on either of the two nodes with the name `n2`.

Both expansions have the same priority and probabilty, so when expanding, one is picked at random. If the expansion failed for any reason (overlapping areas, condition check failed), the structure generator tries to expand to the other component. The generator first tries all possible expansions of a single component before it tries expanding it differently - meaning it will also try connecting to both nodes `c2::n2`.

Probabilities and prioritites can be also altered. The generator first attempts all expansions with the lowest priority before trying out a higher priority. Priority and probability for exach rule expansion can be set via the `priority` and `probabilityRatio` pragmas or using a shorthand syntax:
```WOGLAC
rule R {
	rule -> c1::n !1 :50;
	rule -> c1::n :50;
	rule -> c1::n !1;
	rule -> c2::n {
		pragma priority = 1;
		pragma probabilityRatio = 50;
	}
}
```

The `!prio` construct is used to define a priority and the `:prob` is used to define a probability ratio. Lower priority numbers have higher priority. Default priority is `1`.

Probabilities are defined as ratios, meaning a rule expansion with probability ratio `200` is twice as likely to be selected as rule expansion with probability ratio `100`. Default probability ratio is `100`. If an expansion randomly selected based on the probability ratios fails, another expansion candidate is selected respecting probability ratios of the remaining candidates.


### Rule-rule expansion
A rule can be set up to expand to another rule:
```WOGLAC
rule R {

}
rule R2 {
    rule -> R;
}
```

### Void rule expansion
A rule can be also set up to expand into nothing. This can be achieved using the `rule -> void;` syntax:
```WOGLAC
rule R {
	rule -> c::n;
	rule -> void;
}
```

By default, the void expansion has priority `9999`, meaning it is only used as a fallback if no other expansion succeeds. The priority (and probability) can be changed using the standard syntax.


### Rule expansion pragmas
<center>

| Pragma | Type | Default value | Description |
| --- | --- | --- | --- |
`priority` | `Float` | `1` (or `9999` for void expansion) | Priority of the expansion. Lower number means higher priority. You can also use the `:xxx` shorthand syntax.
`probabilityRatio` | `Float` | `100` | Probability of selecting the expansion, relative to other expansions. You can also use the `!xxx` shorthand syntax.

</center>

## Params
> ```g4
> paramDefinition:
>	(targetType=('rule' | 'component') target=extendedIdentifier?)? 'param' type=Type id=Identifier ('?=' defaultValue=expression)? ';';
>
> paramSetStatement:
>	(targetType=('biome' | 'rule' | 'component') target=extendedIdentifier)? 'param' param=extendedIdentifier '=' value=expression ';';
> ```
Structure generation also supports parametric generation, where paremeters are passed down the expansion tree.

A param must be declared in any scope that wants to read it:
```WOGLAC
param Float remainingLength ?= 10;
```

The `?=` operator states that the value provided is the *default* value. If a parameter with the given name and type does does not exist (was not passed from a parent), it is created and set to the provided value. Otherwise, value passed from the parent is used.

Parameters are passed down the expansion tree regardless of whether they are declared in the child scopes or not. Once a parameter is defined, it is always passed. Default values do not have to be same everywhere, only the first default value encountered is used. The default value can be omitted, that can however result in a worlgen error if the parameter was not defined before.

After declaring the parameter, it is acessible through its identifier in the scope.

### Setting parameters
To set a parameter, there is a simple syntax:
```WOGLAC
param paramName = value;
```

When setting parameter, the new value is passed down the expansion tree. **When reading the parameter in the current scope, the old value is returned.** You also have to declare the parameter for the scope if you want to read it.

The parameter does not have to be declared in the scope for setting.

Parameters passed can also be fields, so you can for example pass a result of a `perlin2D` function and so on.

## Conditions
> ```
> structureConditionStatement:
>	(targetType=('component' | 'rule') target=extendedIdentifier?)? 'condition' cond=expression ';';
> ```

Conditions can restrict if a rule, rule expansion or component can be used. The syntax is very simple: `condition (expr);` where `expr` is any expression that evaluates to `Bool`. If the condition evaluates to false, the appropriate rule, rule expansion or component cannot be used.

```WOGLAC
Float terrainHeight = perlin2D(#2532, ~4) * 10;

component c {
	node (0, 0, 0) bottom;

	// Terrain height must be > 0 at the point of the 'bottom' node, otherwise this component cannot be spawned.
	condition terrainHeight::sampleAt(bottom) > 0;
}
```