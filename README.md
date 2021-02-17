# Procedural Dungeon
![](./readme-assets/demo.gif)

C++ 2d top-down arcade game with procedural generation of the level. 
Game uses SFML as an input & graphics lib with some low-level OpenGL calls for shading.
This game was my graduate C++ project that I wrote at the end of 2018 - start of 2019.
It was my first (at least for me at that time) large OOP project so that codebase is pretty
poor with lack of proper hierarchy, code style and design patterns(although I used some patterns
like observer, singleton, strategy. But codebase still sucks). 

Also it meant to be rough-like but at some point I was out of time and this project was
already more complicated than any work of my groupmates.

Gameplay: player spawns at the first room and they need to go through all rooms to the last one.
When player comes inside last room "You Won" will be displayed & game will close.
When player lost all hearts game will show "Game Over" & close. Pretty simple because this
logic was made at the last night lol.

## Implemented features
- proc generation
- GLSL shades
- parallax background
- simple UI
- culling