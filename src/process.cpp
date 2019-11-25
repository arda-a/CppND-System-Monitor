#include <unistd.h>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include "../include/linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// Return this process's ID
int Process::Pid() { return _pid; }

// Return this process's CPU utilization
float Process::CpuUtilization() {
  string uptime;
  string line;
  std::ifstream stream(LinuxParser::kProcDirectory + to_string(Pid()) + LinuxParser::kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    for (size_t i = 1; i < 23; i++) {
      linestream >> uptime;
      if(i == 14)
        break;
    }
  }
  return stol(uptime) / sysconf(_SC_CLK_TCK);
 }

// Return the command that generated this process
string Process::Command() { return LinuxParser::Command(Pid()); }

// Return this process's memory utilization
string Process::Ram() {
  _ram = std::stof(LinuxParser::Ram(Pid())) / 1000.f;

  std::stringstream ss;
  ss << std::fixed << std::setprecision(2) << _ram;
  std::string ramString = ss.str();

  return ramString;
}

// Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(Pid()); }

// Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(Pid()); }

// Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const { return _ram > a._ram; }