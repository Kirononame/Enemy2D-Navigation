# Enemy2D-Navigation

**This project is made for learning purposes**

## [Engine](https://github.com/OneLoneCoder/olcPixelGameEngine)

The engine used belongs to javidx9 please **refer** to the engine's github page for info about the license and the engine.


## Objective

The player's goal to move from one point to another point and the enemy's goal to stop the player from reaching its destination and the enemy can only move if the enemy detected the player

## Tasks

- [x] Move the player
- Find a path to the player
  - [x] AStar
- [x] Move the enemy on the path
- Add Physics
  - [ ] Collisions
- Limit the area that the Enemy can see
  - [ ] Raycasting - ShadowCasting [Site1](https://www.redblobgames.com/articles/visibility/) - [Site2](https://ncase.me/sight-and-light/)

## Algorithms

- [x] DFS
- [x] BFS
- [x] AStar

## Controls

* <kbd>Up</kbd> - <kbd>Down</kbd> - <kbd>Right</kbd> - <kbd>Left</kbd> : Move Player
* <kbd>q</kbd> - <kbd>w</kbd> : Change Enemy Speed
* <kbd>n</kbd> : Revert game to normal mode
* <kbd>r</kbd> - <kbd>t</kbd> : Change World Size will also need to revert to normal mode after using it for performance
* <kbd>m</kbd> : Move or Stop Player
* <kbd>v</kbd> : To connect nodes Diagonally
* <kbd>a</kbd> : Use A star algorithm
* <kbd>d</kbd> : Use DFS algorithm
* <kbd>Shift</kbd> + <kbd>d</kbd> : Use DFS Improved algorithm
* <kbd>b</kbd> : Use BFS algorithm
* <kbd>Shift</kbd> + <kbd>b</kbd> : Use BFS Improved algorithm
* Left Mouse Click : Make a wall at a specified node
* <kbd>Shift</kbd> + Left Mouse Click : Move Enemy to a specified node
* <kbd>Ctrl</kbd> + Left Mouse Click : Move Player to a specified node


## Project Modes

### Debug Mode

Will show a visual representation of the 2d-space nodes that the enemy uses to navigate and identify the nodes that enemy needed to visit before reaching the player

### Release Mode

Will disable the visual representation

## Compiling

### Architecture support
- [x] x64

### Platform support
- [x] Windows
- [ ] Linux (It should work but not tested)

### [Premake](https://github.com/premake/premake-core)

**Premake is already included in the project no need to download it**

This project uses premake to generate project files.

Premake is a command line utility which reads a scripted definition of a software project and, most commonly, uses it to generate project files for toolsets like Visual Studio, Xcode, or GNU Make. Built-in and Third-Party Modules add support for even more toolsets.

### Run on Windows 

#### Run using Visual Studio

- [x] Test Compile
- [x] Test running the project

Use premake to generate visual studio 2022 files by running the script provided **GenerateProjectForVS22.bat**


Then open the project and run the application the main one is ***"FollowPlayer"***


### Run on Linux

- [x] Test Compile
- [ ] Test running the project

The minimum required version of gcc and g++ will be updated soon with the libraries that might be missing for some machines

Make sure you have **make** installed

To make the project files go to the root directory of the project then

```sh
.\vendor\bin\linux\premake\premake5 gmake
```
To Compile the project in debug mode

```sh
make config=debug
```

To Compile the project in release mode

```sh
make config=release
```