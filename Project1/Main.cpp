#include <iostream>
#include <string>
#include "VisitorEntryQueue.hpp"
#include "StaffLinkedList.hpp"
#include "EmergencyReportStack.hpp"
#include "VehicleBST.hpp"

using namespace std;

int main() {
    VisitorEntryQueue vQueue;
    StaffLinkedList sList;
    EmergencyReportStack eStack;
    VehicleBST vBST; 

    // Load data from files when the program starts
    vQueue.loadFromFile();
    sList.loadFromFile();
    eStack.loadFromFile();
    vBST.loadFromFile();

    int choice;
    string name, purpose, time, position, reportDetails, vehicleId, vehicleModel;
    int staffId, entryTime;

    while (true) {
        cout << "\nSecurity Management System\n";
        cout << "1. Add Visitor\n";
        cout << "2. Remove Visitor\n";
        cout << "3. Display All Visitors\n";
        cout << "4. Add Staff\n";
        cout << "5. Remove Staff\n";
        cout << "6. Display All Staff\n";
        cout << "7. Add Emergency Report\n";
        cout << "8. Handle Emergency Report\n";
        cout << "9. Display All Emergency Reports\n";
        cout << "10. Add Vehicle Log\n";
        cout << "11. Display All Vehicles\n";
        cout << "12. Delete Vehicle by ID\n";
        cout << "13. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter visitor name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter visitor purpose: ";
            getline(cin, purpose);
            cout << "Enter entry time: ";
            getline(cin, time);
            vQueue.addVisitor(name, purpose, time);
            break;

        case 2:
            vQueue.removeVisitor();
            break;

        case 3:
            vQueue.displayVisitors();
            break;

        case 4:
            cout << "Enter staff name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter staff position: ";
            getline(cin, position);
            cout << "Enter staff ID: ";
            cin >> staffId;
            sList.addStaff(name, position, staffId);
            break;

        case 5:
            cout << "Enter staff ID to remove: ";
            cin >> staffId;
            sList.removeStaff(staffId);
            break;

        case 6:
            sList.displayStaff();
            break;

        case 7:
            cout << "Enter emergency report details: ";
            cin.ignore();
            getline(cin, reportDetails);
            cout << "Enter report time: ";
            getline(cin, time);
            eStack.pushReport(reportDetails, time);
            break;

        case 8:
            eStack.popReport();
            break;

        case 9:
            eStack.displayReports();
            break;

        case 10:
            cin.ignore();
            cout << "Enter vehicle ID: ";
            getline(cin, vehicleId);

            cout << "Enter vehicle model: ";
            getline(cin, vehicleModel);

            cout << "Enter entry time: ";
            getline(cin, time);

            vBST.insertVehicle(vehicleId, vehicleModel, time);
            break;


        case 11:
            vBST.displayVehicles();
            break;

        case 12:
            cin.ignore();
            cout << "Enter vehicle ID to delete: ";
            getline(cin, vehicleId);
            vBST.removeVehicle(vehicleId);
            break;

        case 13:
            vQueue.saveToFile();
            sList.saveToFile();
            eStack.saveToFile();
            vBST.saveToFile();
            cout << "Exiting...\n";
            return 0;

        default:
            cout << "Invalid choice. Try again!" << endl;
        }
    }

    return 0;
}