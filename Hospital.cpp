#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

struct Hospital {
    string name;
    int totalWaitTime;  // In minutes
    int patientCount;

    // Default constructor required for map[]
    Hospital() : name(""), totalWaitTime(0), patientCount(0) {}
    
    // Constructor with name
    Hospital(string name) : name(name), totalWaitTime(0), patientCount(0) {}

    // Function to calculate the average wait time for the hospital in minutes
    double averageWaitTime() const {
        if (patientCount == 0) return 0.0;
        return static_cast<double>(totalWaitTime) / patientCount;
    }
};

int main() {
    // Declare variables
    string fileName;
    string line;  // For reading entire lines

    // Ask the user for the file name
    cout << "Welcome to the ER Patient Tracker!\n";
    cout << "Please enter the name of the file with patient records: ";
    cin >> fileName;

    // Open the file
    ifstream inputFile(fileName);

    // Check if the file opened successfully
    if (!inputFile) {
        cerr << "Error: Could not open file '" << fileName << "'\n";
        return 1; // Exit program with error
    }

    // Declare a map to store the hospitals and their wait times
    map<string, Hospital> hospitals;

    // Read data from the file line by line
    while (getline(inputFile, line)) {
        size_t lastSpace = line.rfind(' ');
        if (lastSpace == string::npos) continue;  // Skip malformed lines
        
        try {
            int waitTime = stoi(line.substr(lastSpace + 1));
            size_t firstSpace = line.find(' ');
            size_t secondSpace = line.find(' ', firstSpace + 1);
            
            string patientID = line.substr(0, firstSpace);
            string status = line.substr(firstSpace + 1, secondSpace - firstSpace - 1);
            string hospitalName = line.substr(secondSpace + 1, lastSpace - secondSpace - 1);

            // If the hospital doesn't exist in the map, create it
            if (hospitals.find(hospitalName) == hospitals.end()) {
                hospitals[hospitalName] = Hospital(hospitalName);
            }

            // Update the hospital's total wait time and patient count
            hospitals[hospitalName].totalWaitTime += waitTime;
            hospitals[hospitalName].patientCount++;
        } catch (...) {
            cerr << "Warning: Could not parse line: " << line << endl;
            continue;
        }
    }

    // Close the file
    inputFile.close();

    // Create a vector to hold the hospitals for sorting
    vector<Hospital> hospitalList;

    // Transfer data from the map to the vector
    for (const auto& entry : hospitals) {
        hospitalList.push_back(entry.second);
    }

    // Sort the hospitals by average wait time (ascending)
    sort(hospitalList.begin(), hospitalList.end(), [](const Hospital& a, const Hospital& b) {
        return a.averageWaitTime() < b.averageWaitTime();
    });

    // Print the rankings of the hospitals
    cout << "\nHospital Wait Time Rankings (Least to Most) - in minutes:\n";
    cout << "------------------------------------------------------------\n";
    cout << left << setw(30) << "Hospital Name" << setw(20) << "Avg Wait Time (min)" << setw(20) << "Number of Patients" << endl;
    cout << "------------------------------------------------------------\n";

    for (const auto& hospital : hospitalList) {
        cout << left << setw(30) << hospital.name
             << setw(20) << fixed << setprecision(2) << hospital.averageWaitTime()
             << setw(20) << hospital.patientCount << endl;
    }

    // Exit successfully
    return 0;
}
