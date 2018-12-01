# Enemy2D-Navigation

**This project is made for learning purposes**

## [Engine](https://github.com/OneLoneCoder/olcPixelGameEngine)

The engine used belongs to javidx9 please refer to the engine's github page for info about the license and the engine.


## Objective

The player's goal to move from one point to another point and the enemy's goal to stop the player from reaching its destination and the enemy can only move if the enemy detected the player

## Tasks

- [x] Move the player
- Find a path to the player
	- [x] AStar
- [ ] Move the enemy on the path
- Add Physics
	- [ ] Collisions
- Limit the area that the Enemy can see
	- [ ] Raycasting - ShadowCasting [Site1](https://www.redblobgames.com/articles/visibility/) - [Site2](https://ncase.me/sight-and-light/) 
- [ ] Make a level
- [ ] Make the player Learn how to play the level


## Project Modes

### Debug Mode

Will show a visual representation of the 2d-space nodes that the enemy uses to navigate and identify the nodes that enemy needed to visit before reaching the player

### Release Mode

Will disable the visual representation

## Compiling

### Architecture support
- [x] x64
- [ ] x86 (only tested with Visual Studio but it should work with other project tools if the correct libraries are provided, you will need to edit the configuration of the premake file)

### Platform support
- [x] Windows
- [ ] Linux (Running the app wasn't tested)

Running the project on any other platforms will probably cause an error

### [Premake](https://github.com/premake/premake-core)

**Premake is already included in the project no need to download it**

This project uses premake to generate project files.

Premake is a command line utility which reads a scripted definition of a software project and, most commonly, uses it to generate project files for toolsets like Visual Studio, Xcode, or GNU Make. Built-in and Third-Party Modules add support for even more toolsets.

### Run on Windows 

#### Run using Visual Studio

- [x] Test Compile
- [x] Test running the project

Use premake to generate visual studio 2017 files by running the script provided **GenerateProjectForVS17.bat**

To change the version to 2015 or 2013 just change the version in the Script file.

Then open the project and run the application the main one is ***"FollowPlayer"***

#### Run using Code blocks

- [ ] Test Compile
- [ ] Test running the project

It should work on Code Blocks but you are on your own to configure it as it wasn't tested. A help on how to run the engine using code blocks from javidx9
> Well I wont judge you, but make sure your Code::Blocks installation
is really up to date - you may even consider updating your C++ toolchain
to use MinGW32-W64, so google this. You will also need to enable C++14
in your build options, and add to your linker the following libraries:
user32 gdi32 opengl32 gdiplus

### Run on Linux

- [x] Test Compile
- [ ] Test running the project

The minimum required version of gcc and g++ will be updated soon with the libraries that might be missing for some machines

Make sure you have make installed

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