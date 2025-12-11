#ifndef VEHICLEBST_H
#define VEHICLEBST_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Vehicle {
    string vehicleId;
    string vehicleModel;
    string entryTime;   // ? Now using string like other headers
    Vehicle* left;
    Vehicle* right;
};

class VehicleBST {
private:
    Vehicle* root;

    // Insert helper
    Vehicle* insert(Vehicle* node, const string& id, const string& model, const string& time) {
        if (node == nullptr)
            return new Vehicle{ id, model, time, nullptr, nullptr };

        // Sort by TIME STRING (lexicographically)
        if (time < node->entryTime)
            node->left = insert(node->left, id, model, time);
        else
            node->right = insert(node->right, id, model, time);

        return node;
    }

    // Find min node for deletion
    Vehicle* findMin(Vehicle* node) {
        while (node && node->left != nullptr)
            node = node->left;
        return node;
    }

    // Delete node by ID
    Vehicle* deleteVehicle(Vehicle* node, const string& id) {
        if (!node) return nullptr;

        if (id < node->vehicleId)
            node->left = deleteVehicle(node->left, id);
        else if (id > node->vehicleId)
            node->right = deleteVehicle(node->right, id);
        else {
            // Case 1: No child
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            // Case 2: One child
            else if (!node->left) {
                Vehicle* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {
                Vehicle* temp = node->left;
                delete node;
                return temp;
            }
            // Case 3: Two children
            else {
                Vehicle* temp = findMin(node->right);
                node->vehicleId = temp->vehicleId;
                node->vehicleModel = temp->vehicleModel;
                node->entryTime = temp->entryTime;
                node->right = deleteVehicle(node->right, temp->vehicleId);
            }
        }
        return node;
    }

    // Inorder display
    void inorder(Vehicle* node) {
        if (node) {
            inorder(node->left);
            cout << "ID: " << node->vehicleId
                << " | Model: " << node->vehicleModel
                << " | Time: " << node->entryTime << endl;
            inorder(node->right);
        }
    }

    // Save helper
    void saveToFileHelper(Vehicle* node, ofstream& outFile) {
        if (!node) return;

        outFile << node->vehicleId << ","
            << node->vehicleModel << ","
            << node->entryTime << "\n";

        saveToFileHelper(node->left, outFile);
        saveToFileHelper(node->right, outFile);
    }

public:

    VehicleBST() : root(nullptr) {}

    // Insert vehicle
    void insertVehicle(const string& id, const string& model, const string& time) {
        root = insert(root, id, model, time);
        cout << "Vehicle added successfully.\n";
    }

    // Display all
    void displayVehicles() {
        if (!root) {
            cout << "No vehicle records found.\n";
            return;
        }
        cout << "\n--- Vehicle Log ---\n";
        inorder(root);
        cout << "-------------------\n";
    }

    // Delete by ID
    void removeVehicle(const string& id) {
        root = deleteVehicle(root, id);
        cout << "Vehicle removed (if it existed).\n";
    }

    // Save file
    void saveToFile() {
        ofstream outFile("vehicles.txt");
        saveToFileHelper(root, outFile);
        outFile.close();
    }

    // Load file
    void loadFromFile() {
        ifstream inFile("vehicles.txt");
        if (!inFile) {
            cout << "No previous vehicle data found.\n";
            return;
        }

        string id, model, time;
        while (getline(inFile, id, ',') &&
            getline(inFile, model, ',') &&
            getline(inFile, time)) {

            insertVehicle(id, model, time);
        }

        inFile.close();
    }

};

#endif
