#include <iostream>  
#include <fstream>   
#include <string>    
#include "TimeCode.h"  

using namespace std;

// Function to check if a line contains a valid TimeCode in format "hh:mm"
bool hasTimeCode(const string& input) {
    size_t pos = input.find(":");
    if (pos != string::npos && pos >= 2 && pos + 2 < input.length()) {
        string tc = input.substr(pos - 2, 5);
        return (isdigit(tc[0]) && isdigit(tc[1]) && tc[2] == ':' && isdigit(tc[3]) && isdigit(tc[4]));
    }
    return false;
}

// Function to extract and convert a valid "hh:mm" string into a TimeCode object
TimeCode strToTimeCode(const string& input) {
    size_t pos = input.find(":");
    if (pos == string::npos || pos < 2 || pos + 2 >= input.length()) {
        return TimeCode(0, 0); // Return a default TimeCode if invalid
    }
    
    string parsed = input.substr(pos - 2, 5);
    int hours = stoi(parsed.substr(0, 2));
    int minutes = stoi(parsed.substr(3, 2));

    return TimeCode(hours, minutes);
}

int main() {
    ifstream inputFile("Space_Corrected.csv");  // Open file
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file Space_Corrected.csv." << endl;
        return 1;
    }

    cout << "Opening file Space_Corrected.csv." << endl;
    cout << "Processing TimeCodes..." << endl;

    TimeCode totalTime; // Accumulates valid TimeCodes
    int count = 0;      // Tracks valid TimeCode entries

    string line;
    
    while (getline(inputFile, line)) {  // Read file line by line
        if (hasTimeCode(line)) {
            totalTime = totalTime + strToTimeCode(line);
            count++;
        }
    }

    if (count > 0) {
        TimeCode averageTime = totalTime / count;
        cout << "Average TimeCode: " << averageTime.ToString() << endl;
    } else {
        cout << "No valid TimeCodes found in the file." << endl;
    }

    cout << "Closing file Space_Corrected.csv." << endl;
    inputFile.close();
    return 0;
}
