#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version,kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  float MemTotal;
  float MemFree;
  float MemAvailable;
  float Buffers;
  string value;
  string key;
  string line;

  std::ifstream stream(kProcDirectory+kMeminfoFilename);
  if(stream.is_open()){
    for(int i = 0; i < 4; i++){
      std::getline(stream, line);
      std::istringstream linestream(line);
      if(i == 0){
        linestream >> value >> MemTotal;
      }
      else if(i == 1){
       linestream >> value >> MemFree;
      }
      else if (i == 2){
        linestream >> value >> MemAvailable;
      }
      else if( i == 3){
        linestream >> value >> Buffers;
      }
      else{
        linestream >> value;
      }
    }
  }
  return 1.0 - (MemFree / (MemTotal - Buffers)) ;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  long uptime;
  string line;

  std::ifstream stream(kProcDirectory+kUptimeFilename);

  if(stream.is_open()){
    std::getline(stream,line);
    std::istringstream linestream(line); 

    linestream >> uptime;
  }
  return uptime; }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  long jiffies;
  
  float uptime = LinuxParser::UpTime();

  jiffies = uptime * sysconf(_SC_CLK_TCK);
  
  return jiffies; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { 
  long activejiffies;
  long token1; 
  long token2;
  long token3;

  string line;
  string pid1 = to_string(pid);
  std::ifstream stream(kProcDirectory + pid1 + kStatFilename);

  if(stream.is_open()){
    std::getline(stream, line);
    std::istringstream linestream(line);
    
    for(int i = 0; i < 17; i++){
      if(i == 14){
        linestream >> token1;
      }
      else if(i == 15)
      {
        linestream >> token2;
      }
      else if(i == 16){
        linestream >> token3; 
      }
      
    }
  }
  long token_total = token1 + token2 + token3;
  return token_total; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  string cpu;
  long token1;
  long token2;
  long token3;
  long token4;
  long token5;
  long token6;
  long token7;
  long token8;
  long token9;
  long token10;

  string line;

  std::ifstream stream(kProcDirectory+kStatFilename);
  if(stream.is_open()){
    std::getline(stream, line);
    std::istringstream linestream(line);

    linestream >> cpu >> token1 >> token2 >> token3 >> token4 >> token5 >> token6 >> token7 >> token8 >> token9 >> token10; 

  }

  long total = token1 + token2 + token3 + token4 + token5 + token6 + token7 + token8 + token9 + token10;
  return total; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  string cpu;
  long token3;
  long token4;

  string line;

  std::ifstream stream(kProcDirectory+kStatFilename);
  if(stream.is_open()){
    std::getline(stream, line);
    std::istringstream linestream(line);

    for(int i = 0; i < 5; i++){
      if(i == 3){
        linestream >> token3;
      }
      else if(i == 4){
        linestream >> token4;
      }
    }
  }
  long token_total = token3 + token4; 
  return token_total; }

float LinuxParser::AggCpuUtil(){
  float CpuUtil;
  string line;
  string cpu;
  float user;
  float nice;
  float system;
  float idle;
  float iowait; 
  float irq;
  float softirq;
  float steal;
  float guest;
  float guest_nice;

  std::ifstream stream(kProcDirectory+kStatFilename);
  if(stream.is_open()){
    std::getline(stream, line);
    std::istringstream linestream(line);

    linestream >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
  }

  float usertime = user - guest;
  float nicetime = nice - guest_nice;
  float idealtime = idle + iowait;
  float systemalltime = system + irq + softirq;
  float virtalltime = guest + guest_nice;
  float total = usertime + nicetime + idealtime + systemalltime + steal + virtalltime;

  CpuUtil = (total - idealtime)/total; 

  return CpuUtil;
};
// TODO: Read and return CPU utilization
//vector<string> LinuxParser::CpuUtilization() { return {};}
vector<string> LinuxParser::CpuUtilization() { 
  string line;
  string data;
  vector<string> CpuUtil{};

  std::ifstream stream(kProcDirectory+kStatFilename);
  if(stream.is_open()){
    std::getline(stream, line);
    std::istringstream linestream(line);
    while(linestream >> data){
      if(data != "cpu"){
        CpuUtil.emplace_back(data);
      }
    }
  }

  return CpuUtil; }
  
  float LinuxParser::CpuProcessInfo(int pid){
    string line;
    string pid1 = to_string(pid);
    float utime;
    float stime;
    float cutime;
    float cstime;
    float starttime; 
    string value;

    std::ifstream stream(kProcDirectory+pid1+kStatFilename);
    if(stream.is_open()){
      std::getline(stream, line);
      std::istringstream linestream(line);

      for(int i = 0; i < 22; i++){

        linestream >> value;

        if(i == 13){
          utime = stof(value);
        }
        else if (i == 14){
          stime = stof(value);
        }
        else if (i == 15){
          cutime = stof(value);
        }
        else if(i == 16){
          cstime = stof(value);
        }

        else if(i == 21){
          starttime = stof(value);
        }
        else{
          value = value;
        }
      }
    }

    float total = (utime + stime + cutime + cstime)/sysconf(_SC_CLK_TCK);

    float seconds = LinuxParser::UpTime() - (starttime/sysconf(_SC_CLK_TCK));

    return (total/seconds);
  }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  int total_processes;
  string procs; 
  string line;

  std::ifstream stream(kProcDirectory+kStatFilename);
  if(stream.is_open()){
    for(int i = 0; i < 9; i++){
      std::getline(stream, line);
    }
    std::istringstream linestream(line);

    linestream >> procs >> total_processes;
  }
  return total_processes; }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  int running_processes;
  string procs;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if(stream.is_open()){
    for(int i = 0; i < 10; i++){
      std::getline(stream, line);
    }
    std::istringstream linestream(line);

    linestream >> procs >> running_processes;
  }
  return running_processes; }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string command;
  string pid1 = to_string(pid);
  string line;

  std::ifstream stream(kProcDirectory + pid1 + kCmdlineFilename);
  if(stream.is_open()){
    std::getline(stream, line);
  }
  
  return line; }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string line;
  string value1;
  int value2;
  string pid1 = to_string(pid);
 

  std::ifstream stream(kProcDirectory+pid1+kStatusFilename);
  if(stream.is_open()){
      for(int i = 0 ; i < 18; i++){
        std::getline(stream, line);
      }
      std::istringstream linestream(line);
      linestream >> value1 >> value2;
      
    }
    
    value2 = value2 * .001;
    string value = to_string(value2);
  return value; }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string line;
  string value;
  string key;
  string pid1 = to_string(pid);

  std::ifstream stream(kProcDirectory+pid1+kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid") {
          return value;
        }
      }
    }
  }
  
  return value; }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 

  string line;
  string uid;
  string Uid = LinuxParser::Uid(pid);
  string user;
  std::ifstream stream(kPasswordPath);

  if (stream.is_open()) {
      std::getline(stream, line);
      std::istringstream linestream(line);
      while (linestream >> uid) {
        if (uid == Uid){
          return line;
        }
      }
    
  }

  std::replace(line.begin(), line.end(), '/', ' '); 
  std::replace(line.begin(), line.end(), ':', ' '); 

  std::istringstream linestream2(line);
  linestream2 >> user;
  return user;}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  string line;
  string user;
  string pid1 = to_string(pid);
  long uptime;
  string value;

  std::ifstream stream(kProcDirectory+pid1+kStatFilename);

  if(stream.is_open()){
    std::getline(stream,line);
    std::istringstream linestream(line);

    for(int i = 0; i < 22; i++){
      linestream >> value;

      if(i == 21){
      uptime = stof(value);
      }
      else
      {
        value = value;
      }
      

    }
  }

  uptime = uptime/sysconf(_SC_CLK_TCK);
  return uptime; }