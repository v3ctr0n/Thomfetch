/*

kernel = pistons
os = valve gear
cpu  = steam engine
gpu = wheels
memory = boiler
host = locomotive
disk = tender

ascii art was acquired from: https://www.asciiart.eu/vehicles/trains

*/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>

using namespace std;


// Function to execute shell commands and return the output
string exec(string cmd) {
    string result = "";
    char buffer[128]; //temporalily store output of the command
    FILE* pipe = popen(cmd.c_str(), "r"); //convert cmd string to C string
    if (!pipe) throw runtime_error("popen() failed!"); //error if pipe wasn't created
    try {
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) { //read the output of the command from the pipe and append it to the result
            result += buffer;
        }
    } catch (...) { //if exception is thrown, close the pipe
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

// Function to print system information
void print_sys_info() {
    string CPU_MODEL = exec("cat /proc/cpuinfo | grep 'model name' | uniq | awk -F ':' '{print $2}'");
    string GPU_MODEL = exec("lspci | grep VGA | sed 's/.*: //;s/ (rev.*)//'");
    string OS = exec("lsb_release -d | awk -F ':' '{print $2}' | sed 's/^[ \t]*//'");
    string KERNEL = exec("uname -r");
    string MEMORY_USED = exec("free -h | awk '/^Mem:/ {print $3 \"/\" $2}'");
    string HOSTNAME = exec("hostname");
    string DISK_USAGE = exec("df -h / | awk 'NR==2{print $3 \"/\" $2}'");

    string MODEL = exec("cat /sys/devices/virtual/dmi/id/product_name");

    cout << "\033[1;34mLocomotive: " << "\033[0m" << "\033[0;36m"  << MODEL << "\033[0m";
    cout << "\n\033[1;34mSteam engine:" << "\033[0m" << "\033[0;36m" << CPU_MODEL << "\033[0m";
    cout << "\n\033[1;34mWheels: " << "\033[0m" << "\033[0;36m"<< GPU_MODEL << "\033[0m";
    cout << "\n\033[1;34mValve gear: " << "\033[0m" << "\033[0;36m" << OS << "\033[0m";
    cout << "\n\033[1;34mPistons: " << "\033[0m" << "\033[0;36m" << KERNEL << "\033[0m";
    cout << "\n\033[1;34mSteam pressure: " << "\033[0m" << "\033[0;36m" <<  MEMORY_USED << "\033[0m";
    cout << "\n\033[1;34mTender: " << "\033[0m" << "\033[0;36m" <<  DISK_USAGE << "\033[0m";
    cout << "\n\033[1;34mName: " << "\033[0m" << "\033[0;36m" <<  HOSTNAME << "\033[0m" << endl;


}


void printAsciiArt() {
    ifstream inputFile("thom.txt"); // Open the input file
    if (inputFile.is_open()) { // Check if the file is open
            string line;
        while (getline(inputFile, line)) { // Read the file line by line
            cout << "\033[1;34m" <<"\033[2m" << line << "\033[0m" << endl; // Print each line with blue text
        }
        inputFile.close(); // Close the input file
    }
}

int main() {
    printAsciiArt();
    print_sys_info();
    cout << "\n";
    return 0;
}
