# ScratchApp - Empty Windows App Template in C++

In order to build this project with the included batch file, you need to run the vcvars64.bat from your Visual Studio install folder in a command window to build with msvc or you need to add the required paths to the system path variable to build with g++. You can run the included shell.bat after changing the install folders to do this quickly and consistently.


The app comes with keyboard input set for a hotkey (escape) and a regular key ('w') from which you can add more on your own. They are read from a struct that logs when it's pressed down and for how many frames the button have been held down for.

Also in the app there's a basic single-layer framebuffer with two functions to write RGB & RGBA squares and circles to the app window to get you started.
