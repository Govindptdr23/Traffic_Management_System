#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <algorithm> // For searching and deleting records
using namespace std;

class Vehicle {
private:
    string registrationNumber;
    string ownerName;

public:
    Vehicle(const string& regNum, const string& owner)
        : registrationNumber(regNum), ownerName(owner) {}

    const string& getRegistrationNumber() const {
        return registrationNumber;
    }

    const string& getOwnerName() const {
        return ownerName;
    }

    void setOwnerName(const string& newName) {
        ownerName = newName;
    }
};

class Challan {
private:
    string registrationNumber;
    double amount;

public:
    Challan(const string& regNum, double amt)
        : registrationNumber(regNum), amount(amt) {}

    const string& getRegistrationNumber() const {
        return registrationNumber;
    }

    double getAmount() const {
        return amount;
    }
};

class TrafficManagementSystem {
private:
    vector<Vehicle> vehicles;
    vector<Challan> challans;

public:
    TrafficManagementSystem() {
        loadVehicleRecordsFromFile(); // Load vehicle records from a file
        loadChallanRecordsFromFile(); // Load challan records from a file
    }

    void welcome() {
        time_t currentTime = time(nullptr);
        cout << endl << endl << " " << asctime(localtime(&currentTime)) << endl << endl;

        cout << "              ****TRAFFIC MANAGEMENT SYSTEM****" << endl;
        cout << "\n* ENTER YOUR DESIRED OPTION:" << endl;
        cout << "  1. Record new vehicles" << endl;
        cout << "  2. Get record of challan" << endl;
        cout << "  3. Search record of vehicles" << endl;
        cout << "  4. Update Vehicle Information" << endl; 
        cout << "  5. Delete Records" << endl; 
        cout << "  6. Exit" << endl;
        cout << "\nPlease enter your desired choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                recordVehicle();
                break;
            case 2:
                recordChallan();
                break;
            case 3:
                searchVehicle();
                break;
            case 4:
                updateVehicleInfo(); 
                break;
         
            case 5:
                deleteRecord(); 
                break;
            case 6:
                exit(0);
                break;
            default:
                cout << "Please enter a valid option!" << endl;
                welcome();
        }
    }

    void recordVehicle() {
        cout << "* --Record of Vehicles-*" << endl;
        cout << "* Enter the vehicle's registration number: ";
        string regNum;
        cin.ignore();
        getline(cin, regNum);

        cout << "* Enter the owner's name: ";
        string ownerName;
        getline(cin, ownerName);

        Vehicle vehicle(regNum, ownerName);
        vehicles.push_back(vehicle);

        saveVehicleRecordsToFile();

        cout << "Vehicle recorded successfully!" << endl;
        welcome();
    }

    void recordChallan() {
        cout << "* --Record of Challan--*" << endl;
        cout << "* Enter the vehicle's registration number: ";
        string regNum;
        cin.ignore();
        getline(cin, regNum);

        cout << "* Enter the challan amount: ";
        double amount;
        cin >> amount;

        Challan challan(regNum, amount);
        challans.push_back(challan);

        saveChallanRecordsToFile();

        cout << "Challan recorded successfully!" << endl;
        welcome();
    }

    void searchVehicle() {
        cout << "* --Search for the Record of Vehicles--*" << endl;
        cout << "* Enter your desired option:" << endl;
        cout << "  1. Search by registration number" << endl;
        cout << "  2. Search by owner's name" << endl;
        cout << "  0. Back to main menu" << endl;
        cout << "Please enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 0:
                welcome();
                break;
            case 1:
                searchVehicleByRegNum();
                break;
            case 2:
                searchVehicleByOwnerName();
                break;
            default:
                cout << "Please enter a valid option!" << endl;
                searchVehicle();
        }
    }

    void searchVehicleByRegNum() {
        cout << "Enter the registration number to search for: ";
        string regNum;
        cin.ignore();
        getline(cin, regNum);

        bool found = false;
        for (const Vehicle& vehicle : vehicles) {
            if (vehicle.getRegistrationNumber() == regNum) {
                cout << "Vehicle found! Owner: " << vehicle.getOwnerName() << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Vehicle not found with registration number: " << regNum << endl;
        }

        searchVehicle();
    }

    void searchVehicleByOwnerName() {
        cout << "Enter the owner's name to search for: ";
        string ownerName;
        cin.ignore();
        getline(cin, ownerName);

        bool found = false;
        for (const Vehicle& vehicle : vehicles) {
            if (vehicle.getOwnerName() == ownerName) {
                cout << "Vehicle found! Registration Number: " << vehicle.getRegistrationNumber() << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No vehicles found with owner's name: " << ownerName << endl;
        }

        searchVehicle();
    }

    void loadVehicleRecordsFromFile() {
        ifstream inFile("vehicle_records.txt");
        if (!inFile) {
            cerr << "Error: Unable to open vehicle records file." << endl;
            return;
        }

        vehicles.clear(); 

        string line;
        while (getline(inFile, line)) {
            size_t commaPos = line.find(',');
            if (commaPos != string::npos && commaPos < line.length() - 1) {
                string regNum = line.substr(0, commaPos);
                string ownerName = line.substr(commaPos + 1);
                Vehicle vehicle(regNum, ownerName);
                vehicles.push_back(vehicle);
            }
        }

        inFile.close();
    }

    void saveVehicleRecordsToFile() const {
        ofstream outFile("vehicle_records.txt");
        if (!outFile) {
            cerr << "Error: Unable to open vehicle records file for writing." << endl;
            return;
        }

        for (const Vehicle& vehicle : vehicles) {
            outFile << vehicle.getRegistrationNumber() << "," << vehicle.getOwnerName() << endl;
        }

        outFile.close();
    }

    void loadChallanRecordsFromFile() {
        ifstream inFile("challan_records.txt");
        if (!inFile) {
            cerr << "Error: Unable to open challan records file." << endl;
            return;
        }

        challans.clear(); 

        string line;
        while (getline(inFile, line)) {
            size_t commaPos = line.find(',');
            if (commaPos != string::npos && commaPos < line.length() - 1) {
                string regNum = line.substr(0, commaPos);
                double amount = stod(line.substr(commaPos + 1)); // Convert string to double
                Challan challan(regNum, amount);
                challans.push_back(challan);
            }
        }

        inFile.close();
    }

    void saveChallanRecordsToFile() const {
        ofstream outFile("challan_records.txt");
        if (!outFile) {
            cerr << "Error: Unable to open challan records file for writing." << endl;
            return;
        }

        for (const Challan& challan : challans) {
            outFile << challan.getRegistrationNumber() << "," << challan.getAmount() << endl;
        }

        outFile.close();
    }
    
    
    void updateVehicleInfo(){
        cout << "* --Update Vehicle Information-- *" << endl;
        cout << "Enter the registration number of the vehicle to update: ";
        string regNum;
        cin.ignore();
        getline(cin, regNum);

        bool found = false;
        for (Vehicle& vehicle : vehicles) {
            if (vehicle.getRegistrationNumber() == regNum) {
                cout << "Enter the new owner's name for the vehicle: ";
                string newName;
                getline(cin, newName);
                vehicle.setOwnerName(newName);
                saveVehicleRecordsToFile(); // Save the updated vehicle records to a file
                found = true;
                cout << "Vehicle information updated successfully!" << endl;
                break;
            }
        }

        if (!found) {
            cout << "Vehicle not found with registration number: " << regNum << endl;
        }

        welcome(); 
    }

    
    void deleteRecord() {
        cout << "* --Delete Records-- *" << endl;
        cout << "1. Delete Vehicle Record" << endl;
        cout << "2. Delete Challan Record" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                deleteVehicleRecord();
                break;
            case 2:
                deleteChallanRecord();
                break;
            default:
                cout << "Please enter a valid option!" << endl;
                deleteRecord();
        }
    }

    void deleteVehicleRecord() {
        cout << "Enter the registration number of the vehicle to delete: ";
        string regNum;
        cin.ignore();
        getline(cin, regNum);

        auto it = remove_if(vehicles.begin(), vehicles.end(), [regNum](const Vehicle& vehicle) {
            return vehicle.getRegistrationNumber() == regNum;
        });

        if (it != vehicles.end()) {
            vehicles.erase(it, vehicles.end());
            saveVehicleRecordsToFile(); // Save the updated vehicle records to a file
            cout << "Vehicle record deleted successfully!" << endl;
        } else {
            cout << "Vehicle not found with registration number: " << regNum << endl;
        }

        welcome(); 
    }

    void deleteChallanRecord() {
	
        cout << "Enter the registration number of the vehicle for which you want to delete a challan: ";
        string regNum;
        cin.ignore();
        getline(cin, regNum);

        auto it = remove_if(challans.begin(), challans.end(), [regNum](const Challan& challan) {
            return challan.getRegistrationNumber() == regNum;
        });

        if (it != challans.end()) {
            challans.erase(it, challans.end());
            saveChallanRecordsToFile(); 
            cout << "Challan record deleted successfully!" << endl;
        } else {
            cout << "No challan found for the vehicle with registration number: " << regNum << endl;
        }

        welcome(); 
    }
};

int main() {
    TrafficManagementSystem tms;
    tms.welcome();
    return 0;
}
