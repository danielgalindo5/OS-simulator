# OS Simulator

This project is a command-line-based Operating System shell simulator. It is designed to mimic the boot-up process, user authentication, and a basic command shell environment.

### Team Members
* Daniel Galindo

### Features
* **User Authentication:** The simulator requires a valid username and password to grant access to the shell. The authentication logic is handled by the `auth.h` and `auth.obj` files.
* **Interactive Shell:** Once authenticated, the user can interact with a command-line interface. The shell provides a welcome message and a prompt for user commands.
* **Boot-Up Sequence:** The program includes a simulated boot-up sequence with a short delay before displaying the login prompt.

### How to Use
1.  **Run the executable:** Execute the `main.exe` file.
2.  **Authenticate:** Enter the correct username and password at the prompt.
3.  **Explore the shell:** Once authenticated, you will have access to the shell environment.

### Files
* `main.exe`: The executable file for the OS simulator.
* `main.obj`: The object file for the main program logic.
* `auth.h`: The header file containing the declaration for the authentication function.
* `auth.obj`: The object file for the authentication implementation.
