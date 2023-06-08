#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

struct Location {
    string name;
    vector<string> diseases;
};

void addLocation(vector<Location>& locations, const string& locationName) {
    Location newLocation;
    newLocation.name = locationName;
    locations.push_back(newLocation);
    cout << "Location " << locationName << " is successfully added!" << endl;
}

void deleteLocation(vector<Location>& locations, const string& locationName) {
    auto it = find_if(locations.begin(), locations.end(),
                      [&](const Location& location) { return location.name == locationName; });

    if (it != locations.end()) {
        locations.erase(it);
        cout << "Location " << locationName << " is successfully deleted!" << endl;
    } else {
        cout << "Location " << locationName << " does not exist!" << endl;
    }
}

void recordDisease(vector<Location>& locations, const string& locationName,
                   const string& diseaseName) {
    auto it = find_if(locations.begin(), locations.end(),
                      [&](const Location& location) { return location.name == locationName; });

    if (it != locations.end()) {
        it->diseases.push_back(diseaseName);
        cout << "Recorded disease " << diseaseName << " for location " << locationName << endl;
    } else {
        cout << "Location " << locationName << " does not exist!" << endl;
    }
}

void listLocations(const vector<Location>& locations) {
    for (const auto& location : locations) {
        cout << location.name << endl;
    }
}

void listDiseases(const vector<Location>& locations) {
    vector<string> diseases;
    for (const auto& location : locations) {
        for (const auto& disease : location.diseases) {
            diseases.push_back(disease);
        }
    }
    sort(diseases.begin(), diseases.end());
    for (const auto& disease : diseases) {
        cout << disease << endl;
    }
}

void findLocationsWithDisease(const vector<Location>& locations, const string& diseaseName) {
    vector<string> locationNames;
    for (const auto& location : locations) {
        for (const auto& disease : location.diseases) {
            if (disease == diseaseName) {
                locationNames.push_back(location.name);
                break;
            }
        }
    }
    if (locationNames.empty()) {
        cout << "No location with this disease" << endl;
    } else {
        for (const auto& location : locationNames) {
            cout << location << endl;
        }
    }
}

void getCases(const vector<Location>& locations, const string& locationName, const string& diseaseName) {
    for (const auto& location : locations) {
        if (location.name == locationName) {
            int cases = count(location.diseases.begin(), location.diseases.end(), diseaseName);
            cout << "Cases of disease " << diseaseName << " in location " << locationName << ": " << cases << endl;
            return;
        }
    }
    cout << "Location " << locationName << " does not exist!" << endl;
}

void saveDataToFile(const vector<Location>& locations, const string& fileName) {
    ofstream file(fileName);
    if (file.is_open()) {
        for (const auto& location : locations) {
            file << "Location: " << location.name << endl;
            file << "Diseases: ";
            for (const auto& disease : location.diseases) {
             file << disease << ", ";
file << endl;
}
file << endl;
}

file.close();
cout << "Data saved to file: " << fileName << endl;
} else {
cout << "Error opening file: " << fileName << endl;
}
}

int main() {
vector<Location> locations;
string command;

cout << "Welcome to Disease Cases Reporting System!" << endl;
cout << "It is developed by NAILLUUHHH as practical evaluation for the end of Year 3." << endl;

cout << "Need help? Type 'help' then press Enter key." << endl;

while (true) {
cout << "Console >";
getline(cin, command);

if (command == "help") {
cout << "HELP" << endl;
cout << "MENU" << endl;
cout << "add <Location>" << endl;
cout << "Add a new location" << endl;
cout << "delete <Location>" << endl;
cout << "Delete an existing location" << endl;
cout << "record <Location> <Disease>" << endl;
cout << "Record a disease" << endl;
cout << "list locations" << endl;
cout << "List all existing locations" << endl;
cout << "list diseases" << endl;
cout << "List existing diseases in locations" << endl;
cout << "where <Disease>" << endl;
cout << "Find locations where a disease exists" << endl;
cout << "cases <Location> <Disease>" << endl;
cout << "Find cases of a disease in a location" << endl;
cout << "save <Filename>" << endl;
cout << "Save entered data into a file" << endl;
cout << "help" << endl;
cout << "Prints user manual" << endl;
cout << "exit" << endl;
cout << "Exit the program" << endl;
} else if (command == "list locations") {
listLocations(locations);
} else if (command.substr(0, 4) == "add ") {
string locationName = command.substr(4);
addLocation(locations, locationName);
} else if (command.substr(0, 7) == "delete ") {
string locationName = command.substr(7);
deleteLocation(locations, locationName);
} else if (command.substr(0, 7) == "record ") {
string remainingCommand = command.substr(7);
string locationName = remainingCommand.substr(0, remainingCommand.find(' '));
string diseaseName = remainingCommand.substr(locationName.length() + 1);
recordDisease(locations, locationName, diseaseName);
} else if (command == "list diseases") {
listDiseases(locations);
} else if (command.substr(0, 6) == "where ") {
string diseaseName = command.substr(6);
findLocationsWithDisease(locations, diseaseName);
} else if (command.substr(0, 6) == "cases ") {
string remainingCommand = command.substr(6);
string locationName = remainingCommand.substr(0, remainingCommand.find(' '));
string diseaseName = remainingCommand.substr(locationName.length() + 1);
getCases(locations, locationName, diseaseName);
} else if (command.substr(0, 5) == "save ") {
string fileName = command.substr(5);
saveDataToFile(locations, fileName);
} else if (command == "exit") {
cout << "Exiting the program..." << endl;
break;
} else {
cout << "Invalid command! Type 'help' for a list of available commands." << endl;
}
}

return 0;
}

