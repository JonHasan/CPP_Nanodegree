# CppND-System-Monitor


This is the second project in the Nanodegree. I needed to be able to parse linux system files in order to create a system monitor. This one had its own unique set of challenges but it was just an exercise in Object Oriented Programming. I will be going over the basics in detail. 

## Task 1 : Updating the Linux_Parser.Cpp

This was a chunky file when all the updates were complete. However, it looks like a lot of the implementations were not very efficient. I will go through each one. 

### LinuxParser::MemoryUtilization()

I instantiated all variables as floats. I made a stream variable and put in the directory of kProcDirectory + kMemInfoFilename. When the stream was open, a for loop was used to go over four lines that each had an important piece of data. The first had MemTotal, second had MemFree, third had MemAvailable and the fourth had Buffers. The equation of 

1 - (MemFree / (MemTotal - Buffers))

was used to calculate the memory utilization. The reviewer had a more efficient solution. using two while loops. The first one was getting the line from the filestream. The second was constantly checking the linestream output for a certain key. 

### LinuxParser::UpTime()

For this function I opened up a stream again and got a single line and then used >> to get the uptime. 

### LinuxParser::Jiffies()

For this function, I used the previously defined UpTime() function to get the uptime. This was then multiplied with sysconf(_SC_CLK_TCK). This is the clock ticks per second

### LinuxParser::

### 

####

## Task 2 : Updating the Process.cpp 
This file seemed to be composed mostly of getter functions. Only the results of the functions were being returned.
The values returned from the getters are as follows. 

Process:Pid() returns the pid or the process number

Process::CpuUtilization() returns the cpuUtilization_ or the amount of CPU that is being taken up by the process

Process::command() returns command_ or the actual command that started the process

Process::user() returns user_ or the actual user that started the process

Process:Uptime() returns uptime_ or the lifetime of the process

Process:operator<(Process const& a) returns a boolean that compares two process objects. This overloads the comparison operator 

## Task 3

## Task 4

## Task 5

## Motivation

This project is an attempt to recreate something similar to HTOP. It is a linux system monitor that shows CPU utilization of different processes. This project will allow us to develop our Object Oriented Programming skills and scope resolution skills. 

![System Monitor](images/monitor.png)

## Udacity Linux Workspace
[Udacity](https://www.udacity.com/) provides a browser-based Linux [Workspace](https://engineering.udacity.com/creating-a-gpu-enhanced-virtual-desktop-for-udacity-497bdd91a505) for students. 

You are welcome to develop this project on your local machine, and you are not required to use the Udacity Workspace. However, the Workspace provides a convenient and consistent Linux development environment we encourage you to try.

## ncurses
[ncurses](https://www.gnu.org/software/ncurses/) is a library that facilitates text-based graphical output in the terminal. This project relies on ncurses for display output.

Within the Udacity Workspace, `.student_bashrc` automatically installs ncurses every time you launch the Workspace.

If you are not using the Workspace, install ncurses within your own Linux environment: `sudo apt install libncurses5-dev libncursesw5-dev`

## Make
This project uses [Make](https://www.gnu.org/software/make/). The Makefile has four targets:
* `build` compiles the source code and generates an executable
* `format` applies [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) to style the source code
* `debug` compiles the source code and generates an executable, including debugging symbols
* `clean` deletes the `build/` directory, including all of the build artifacts

## Instructions

1. Clone the project repository: `git clone https://github.com/JonHasan/CPP_Nanodegree/Project 2 : System Monitor`

2. Build the project: `make build`

3. Run the resulting executable: `./build/monitor`
![Starting System Monitor](images/starting_monitor.png)

4. Follow along with the lesson.

5. Implement the `System`, `Process`, and `Processor` classes, as well as functions within the `LinuxParser` namespace.

6. Submit!
