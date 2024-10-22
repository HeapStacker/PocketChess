Pocket Chess 1.0.0
The project is built using C++ and the SDL2 library. This is the first version of the program, so it still contains several bugs.

Build Instructions
You cannot directly build the game from the source code. To try it out, follow these steps:

Download the SDL2, SDL2_image, and SDL2_mixer libraries.

Create a project that includes and links these libraries.

Add the following libraries to the Additional Dependencies:

SDL2.lib
SDL2main.lib
SDL2_image.lib
SDL2_mixer.lib
(Linker -> Input -> Additional Dependencies)
Once your project is set up, replace your project folder with mine and add all the required SDL2 DLL files (bin files) to the folder.

At this point, the game should run if you launch it from Visual Studio. Enjoy! :)

Known Bugs
*Sounds are not implemented yet.
*The options button doesn't work.
*Only the versus mode is playable.
*Window resizing works correctly only in the game state mode.
*You cannot win or lose the game (the king can be captured, but the game doesn’t end).
*The game is not fully optimized.
