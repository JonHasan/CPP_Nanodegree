#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
//defining function below removes bottom portion of screen
vector<Process>& System::Processes() {
    processes_.clear();

    vector<int> pids = LinuxParser::Pids();

    for(int pid: pids){
     Process process(pid);

     processes_.emplace_back(process);
    } 

    std::sort(processes_.begin(), processes_.end()); //use overloaded operator >
    return processes_; }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
    string kernel = LinuxParser::Kernel();
    return kernel; }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
    float memory_utilization = LinuxParser::MemoryUtilization();
    return memory_utilization; }

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
    string os = LinuxParser::OperatingSystem();
    return os; }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { 
    int running_processes = LinuxParser::RunningProcesses();
    return running_processes; }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { 
    int total_processes = LinuxParser::TotalProcesses(); 
    return total_processes; }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { 
    
    long int uptime = LinuxParser::UpTime();
    return uptime; }