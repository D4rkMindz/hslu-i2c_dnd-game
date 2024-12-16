# DnD Game

## Installation

1. Clone repository
2. Ensure that the parameter --rooms is given as argument for your run configuration (example: --rooms
   /Users/developer/code/c/fallen-kingdom/rooms.json)
3. Build & Success

## Configuration

### Rooms

You MUST provide a rooms JSON file. In this file, you must have the rooms configured as follows:

```
{
  "rooms": [
    {
      "id": number,
      "name": String,
      "description": String[], // Multiple lines for the description of the room
      "look_around": String[], // Multiple lines for the look around text of the room
      "monsters": String[],    // Array of monsters (currently implemented: Slime, Skeleton, Skeleton King)
      "exits": {
        "north": number,       // id of another room or null or -1
        "east": number,        // id of another room or null or -1
        "south": number,       // id of another room or null or -1
        "west": number,        // id of another room or null or -1
      },
      "secret_passage": number // id of another room or null or -1
    }
  ]
}
```

The rooms are expandable, the boss room must have no exits.

Use ./rooms.json as reference.

```bash
$ ./FallenKingdom --rooms ./rooms.json
```