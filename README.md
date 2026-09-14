# cub3D Parsing + Rendering

This repository contains the parsing and validation logic for the `cub3D` project in 42Vienna. the Rendering logic is under development process.

The parser reads a `.cub` configuration file, extracts all required scene information, validates it, and prepares a normalized rectangular map that can be used directly by the raycasting part of the project.

## What the parser handles

The parser extracts and validates:

- North texture path: `NO`
- South texture path: `SO`
- West texture path: `WE`
- East texture path: `EA`
- Floor color: `F`
- Ceiling color: `C`
- Raw map
- Player start position
- Player start direction: `N`, `S`, `E`, or `W`

## Parsing flow

The configuration file is read line by line.

Before the map starts:

- Empty lines are ignored.
- `NO`, `SO`, `WE`, `EA`, `F`, and `C` can appear in any order.
- Duplicate identifiers are rejected.
- Unknown or unexpected information is rejected.
- The map can only start after all required configuration data has been found.

After the map starts:

- Every following line is treated as map content.
- Empty lines are not silently skipped.
- Configuration data appearing after the map has started is therefore rejected during map validation.

The overall flow is:

```text
.cub file
   |
   v
extension check
   |
   v
extract configuration
   |
   v
extract raw map
   |
   v
validate textures
   |
   v
validate RGB colors
   |
   v
validate map
   |
   v
normalize map
   |
   v
transfer data to t_game
```

## Texture parsing

For each texture, the parser:

- Detects the identifier.
- Skips spaces/tabs between the identifier and the path.
- Extracts one texture path.
- Rejects missing paths.
- Rejects duplicated texture identifiers.
- Rejects unexpected extra information after the path.
- Checks that the texture file can be opened.

Example:

```text
NO ./textures/north.xpm
```

is valid, while:

```text
NO ./textures/north.xpm extra
```

is rejected.

## RGB parsing

Floor and ceiling colors are read from:

```text
F 220,100,0
C 225,30,0
```

Spaces around RGB separators are handled during extraction, so inputs such as:

```text
F 220, 100, 0
F 220 , 100 , 0
```

can be normalized before validation.

The RGB validator checks:

- Exactly two commas are present.
- Exactly three RGB components exist.
- Every component contains only digits.
- Every value is in the range `0` to `255`.

The validated values are stored as:

```c
int rgb_floor[3];
int rgb_ceil[3];
```

For the renderer, the three RGB components are later converted into one integer color:

```c
(r << 16) | (g << 8) | b
```

## Map extraction

The map is stored first as a raw `char **`.

Spaces are preserved during parsing because they are meaningful in the original map representation.

Example:

```text
   11111
   10001
11110E01
10000001
11111111
```

The parser does not remove the leading spaces before validation.

## Map validation

Map validation is divided into several independent checks.

### Valid characters

The raw map may contain:

```text
0
1
N
S
E
W
space
```

Any other character causes an error.

### Player validation

Exactly one of the following characters must exist in the complete map:

```text
N
S
E
W
```

The character represents both:

- the player's starting position
- the player's initial orientation

The parser stores:

```c
int  player[2];
char player_dir;
```

where:

```text
player[0] = row
player[1] = column
```

### Wall validation

The parser checks the outer shape of the raw map:

- The first non-space character of every row must be `1`.
- The last non-space character of every row must be `1`.
- The top and bottom rows may only contain walls and spaces.

### Void / playable-tile validation

Playable tiles are:

```text
0
N
S
E
W
```

For every playable tile, its four direct neighbours are checked.

A playable tile must not touch:

- a space / void area
- a position outside an existing row
- a position outside the map

This prevents the playable area from being open to the outside.

## Map normalization

After the raw map has successfully passed validation, a second map is created for the raycaster:

```c
char **rect_map;
```

The normalized map:

- has the same number of rows as the raw map
- uses the longest raw row as its column count
- gives every row the same length
- replaces spaces/void cells with `1`
- fills missing cells in shorter rows with `1`
- replaces `N`, `S`, `E`, or `W` with `0`

The player character can safely become `0` because its position and direction have already been stored separately.

Example:

Raw map:

```text
   11111
   10001
11110E01
10000001
11111111
```

Normalized map:

```text
11111111
11110001
11110001
10000001
11111111
```

This representation is easier for collision detection and raycasting because every row has the same width and the final map contains only walkable cells (`0`) and walls (`1`).

## Data structure

The parser currently uses:

```c
typedef struct s_info
{
    t_texture textures;
    char      *floor;
    char      *ceil;
    int       rgb_floor[3];
    int       rgb_ceil[3];
    char      **map;
    char      **rect_map;
    int       map_row;
    int       max_col;
    int       row;
    int       player[2];
    char      player_dir;
}   t_info;
```

`map` is the original parsed map used for validation.

`rect_map` is the normalized map transferred to the raycasting part of the project.

## Memory management

All dynamically allocated parsing data is released through the parser cleanup functions.

This includes allocated texture paths, RGB strings, the raw parsed map, and the normalized map. Error paths should also release any memory allocated before the error occurred.

## Error handling

The parser rejects, among other cases:

- invalid file extension
- missing configuration values
- duplicate configuration identifiers
- unknown information before the map
- missing texture paths
- inaccessible texture files
- invalid RGB syntax
- RGB values outside `0..255`
- invalid map characters
- missing player
- multiple players
- open maps
- playable cells touching void
- empty lines that break the map
- configuration data appearing after the map starts

On invalid configuration, the program exits cleanly with an error instead of continuing with partially parsed data.

## Testing

Recommended parser tests include:

```text
Valid:
- minimal valid map
- irregular valid map
- leading spaces in map
- different configuration order
- multiple empty lines between configuration elements
- RGB spacing variations

Invalid:
- missing NO/SO/WE/EA
- duplicated texture
- missing F or C
- unknown identifier
- additional data after texture path
- invalid RGB component
- RGB below 0 / above 255
- no player
- multiple players
- invalid map character
- open map
- playable tile touching void
- empty line inside the map
- configuration element after map start
```

Memory tests should also be run on both successful and failing parsing paths.
