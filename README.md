OS Simulator – Command Line Operating System Shell
This project is a command-line Operating System simulator written in C++. It mimics a lightweight OS boot sequence, user authentication, a basic process simulation, CPU scheduling algorithms, and a simple virtual memory system. It is intended as an educational tool to demonstrate core OS concepts from the terminal.
Team Members
• Daniel Galindo
Implemented Features
1.	1. User Authentication
The simulator requires a valid username and password before granting access to the shell. 
Authentication is handled through the function authenticateuser() (declared in auth.h). If authentication fails, the OS prints an access denied message and shuts down.
Default credentials used during development:
Username: admin
Password: password123
2.	2. Simple Process Simulation
After a successful login, the simulator first demonstrates a basic process model using the Process class. In main.cpp, two processes p1 and p2 are created with different process IDs, arrival times, and burst times. The code then:
•	• Sets p1 to READY and p2 to NEW.
•	• Prints their current PCB information using showInfo().
•	• Runs p1 one CPU cycle at a time using runOneCycle() until isFinished() returns true.
This part of the simulator illustrates basic process states (NEW, READY, RUNNING, FINISHED) and how a process advances over CPU cycles.
3.	3. CPU Scheduling Simulation
The second part of the program demonstrates CPU scheduling using a SchedProcess structure/class and three classic scheduling algorithms. A vector<SchedProcess> is created with four processes, each containing fields such as PID, arrival time, burst time, remaining time, and statistics placeholders.
The user is prompted to choose one of the following algorithms:
•	• FCFS (First-Come, First-Served) via fcfs(schedProcs)
•	• SJF (Shortest Job First) via sjf(schedProcs)
•	• SRTF (Shortest Remaining Time First) via srtf(schedProcs)
Based on the user’s choice, the corresponding function is called. After scheduling completes, displayResults(schedProcs) is used to show the per-process results and any computed metrics such as waiting time and turnaround time.
4.	4. Virtual Memory Simulation
The final part of the program demonstrates a simple paged virtual memory system through the VirtualMemory class. The simulation uses constants such as NUM_PAGES, FRAME_COUNT, and PAGE_SIZE to describe the logical address space and physical frames.
The flow is:
•	• The program prints the number of pages, frames, and the page size in bytes.
•	• In a loop, the user is asked to enter a logical address between 0 and NUM_PAGES * PAGE_SIZE - 1 (or -1 to stop).
•	• For each logical address, vm.readByte(logicalAddress, fault) is called. The program prints the value read and whether it was a page fault or a hit.
•	• Then vm.writeByte(logicalAddress, newValue, fault2) is called, writing a value based on the address and again indicating whether a page fault occurred on write.
• After the loop ends, vm.printStats() prints summary statistics for the virtual memory system, such as the total number of page faults or hits (depending on your implementation).
This module demonstrates logical versus physical addressing, demand paging, and page faults in a controlled, interactive way.
Program Flow
The high-level execution of main.cpp is:
5.	1. Print a boot message: "[OS] // Booting up this may take a few seconds..."
6.	2. Call authenticateuser(). If it fails, print an access denied message and exit.
7.	3. On success, print a welcome message for the OS shell.
8.	4. Run the simple Process simulation using the Process class.
9.	5. Run the CPU Scheduling simulation (FCFS, SJF, or SRTF) using SchedProcess and Scheduler functions.
10.	6. Run the Virtual Memory simulation using the VirtualMemory class and interactive logical addresses.
11.	7. Print "[OS] // Shutting down." and exit.
Project Structure (Example)
Below is an example structure of the project files. Your actual structure may include more source files as needed.
os-simulator/
│── main.cpp
│── auth.h
│── Process.h
│── Process.cpp
│── Scheduler.h
│── Scheduler.cpp
│── VirtualMemory.h
│── VirtualMemory.cpp
│── README.md

Build Instructions (MSVC – Developer Command Prompt)
This project is designed to be compiled with the Microsoft Visual C++ compiler (MSVC) using the Developer Command Prompt for Visual Studio.
12.	1. Open the Developer Command Prompt for Visual Studio 2022.
13.	2. Navigate to the project folder:
   cd C:\Users\i\OneDrive\Escritorio\os-simulator
14.	3. Verify that all .cpp files are present:
   dir *.cpp
15.	4. Compile all source files in one command:
   cl /EHsc /std:c++17 /Fe:OSsim.exe *.cpp
This command compiles all C++ files in the folder and links them into an executable named OSsim.exe.
Running the Simulator
Once compilation succeeds, run the executable from the same terminal:
   OSsim
You will then see the following sequence:
•	• Boot message.
•	• Login prompt (user authentication).
•	• Process simulation output.
•	• Menu to select a CPU scheduling algorithm (FCFS, SJF, or SRTF).
•	• Virtual memory interactive demo where you enter logical addresses.
•	• Final statistics from the virtual memory module and a shutdown message.
Educational Purpose
This OS simulator is intended for academic and educational use, helping students understand how core operating system concepts such as processes, CPU scheduling, and virtual memory can be modeled and observed through a terminal-based interface.
