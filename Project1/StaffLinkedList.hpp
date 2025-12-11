#pragma once
#ifndef STAFFLINKEDLIST_H
#define STAFFLINKEDLIST_H

#include <iostream>
#include <string>
#include <fstream>

struct Staff {
    std::string name;
    std::string position;
    int staffId;
    Staff* next;
};

class StaffLinkedList {
private:
    Staff* head;

public:
    StaffLinkedList() : head(nullptr) {}

    // Add a new staff member
    void addStaff(const std::string& name, const std::string& position, int id) {
        Staff* newStaff = new Staff{ name, position, id, nullptr };
        if (!head) {
            head = newStaff;
        }
        else {
            Staff* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newStaff;
        }
        std::cout << "Staff added: " << name << std::endl;
    }

    // Remove a staff member
    void removeStaff(int id) {
        if (!head) {
            std::cout << "No staff members to remove." << std::endl;
            return;
        }

        Staff* temp = head;
        Staff* prev = nullptr;

        if (temp && temp->staffId == id) {  // If head node holds the staff to delete
            head = temp->next;
            delete temp;
            std::cout << "Staff removed." << std::endl;
            return;
        }

        // Search for the staff to remove
        while (temp && temp->staffId != id) {
            prev = temp;
            temp = temp->next;
        }

        if (!temp) {
            std::cout << "Staff not found." << std::endl;
            return;
        }

        prev->next = temp->next;
        delete temp;
        std::cout << "Staff removed." << std::endl;
    }

    // Display all staff members
    void displayStaff() {
        if (!head) {
            std::cout << "No staff members." << std::endl;
            return;
        }

        Staff* temp = head;
        std::cout << "\nStaff List:\n";
        std::cout << "----------------------------\n";
        while (temp) {
            std::cout << "ID: " << temp->staffId << ", Name: " << temp->name << ", Position: " << temp->position << std::endl;
            temp = temp->next;
        }
        std::cout << "----------------------------\n";
    }

    // Save staff data to file
    void saveToFile() {
        std::ofstream outFile("staff.txt");
        Staff* temp = head;
        while (temp) {
            outFile << temp->staffId << "," << temp->name << "," << temp->position << "\n";
            temp = temp->next;
        }
        outFile.close();
    }

    // Load staff data from file
    void loadFromFile() {
        std::ifstream inFile("staff.txt");
        if (!inFile) {
            std::cout << "No previous staff data found." << std::endl;
            return;
        }

        std::string name, position;
        int id;
        while (inFile >> id) {
            inFile.ignore(1, ',');
            getline(inFile, name, ',');
            getline(inFile, position);
            addStaff(name, position, id);
        }

        inFile.close();
    }
};

#endif