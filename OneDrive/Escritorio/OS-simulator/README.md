OS Simulator

This project is operating system simulator made in C++.
It includes basic authentication and process management.

HOW TO COMPILE (IMPORTANT)

You have to compile this project using the Developer Command Prompt for Visual Studio,
not directly inside VS Code.

1. Open the Developer Command Prompt.
2. Go to your project folder:
   cd "C:\Users\icalu\OneDrive\Escritorio\OS-simulator"

3. Compile all the files together:
   cl main.cpp auth.cpp Process.cpp

This will create an .exe file in the same folder.

HOW TO RUN

After compiling, type:
   main


FILES
- main.cpp       -> main program
- auth.cpp / auth.h -> handles login
- Process.cpp / Process.h -> process simulation
- README.txt      -> project information

NOTES
You must use the Developer Command Prompt because it has the compiler (cl.exe)
already configured. VS Code alone won’t compile it unless the compiler is added to PATH.


AUTHOR

Daniel Galindo
Texas A&M International University 
