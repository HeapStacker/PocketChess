#Pocket Chess 1.0.0

The project is made with c++ and sdl2 lib. This is the first ver. of the program so it has many bugs.

BUILD
You can't build the game from source code. To try it out, download the sdl2, sdl2_image and sdl2_mixer libs and create the project that will include and link them.

Also insert these libs in Additional Dependencies
SDL2.lib
SDL2main.lib
SDL2_image.lib
SDL2_mixer.lib
Linker->Input->Additional Dependecies ...

Now you can replace your project folder with mine and hopefully the game will work when you run it from *visual studio*.
Enjoy :)


*Bugs*
-sounds are not implemented yet
-options button doesn't work
-only the versus mode is playable
-resizeing the window is proper only in the game state mode
-you cann't win or lose the game(you can kill the king)
-the game is not optimised fully
-...
