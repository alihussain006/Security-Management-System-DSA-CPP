#pragma once
#ifndef VISITORENTRYQUEUE_H
#define VISITORENTRYQUEUE_H

#include <iostream>
#include <queue>
#include <string>
#include <fstream>

struct Visitor {
    std::string name;
    std::string purpose;
    std::string timeOfEntry;
};

class VisitorEntryQueue {
private:
    std::queue<Visitor> visitorQueue;

public:
    // Add a new visitor
    void addVisitor(const std::string& name, const std::string& purpose, const std::string& time) {
        Visitor newVisitor = { name, purpose, time };
        visitorQueue.push(newVisitor);
        std::cout << "Visitor added: " << name << std::endl;
    }

    // Remove a visitor from the queue
    void removeVisitor() {
        if (!visitorQueue.empty()) {
            Visitor frontVisitor = visitorQueue.front();
            visitorQueue.pop();
            std::cout << "Visitor left: " << frontVisitor.name << std::endl;
        }
        else {
            std::cout << "No visitors to remove." << std::endl;
        }
    }

    // Display all visitors
    void displayVisitors() {
        if (visitorQueue.empty()) {
            std::cout << "No visitors." << std::endl;
            return;
        }

        std::cout << "\nVisitor Log:\n";
        std::cout << "---------------------------------\n";
        std::queue<Visitor> tempQueue = visitorQueue;  // Temporary queue to display without modifying original
        while (!tempQueue.empty()) {
            Visitor v = tempQueue.front();
            std::cout << "Name: " << v.name << ", Purpose: " << v.purpose << ", Time: " << v.timeOfEntry << std::endl;
            tempQueue.pop();
        }
        std::cout << "---------------------------------\n";
    }

    // Save visitor data to file
    void saveToFile() {
        std::ofstream outFile("visitors.txt");
        std::queue<Visitor> tempQueue = visitorQueue;

        while (!tempQueue.empty()) {
            Visitor v = tempQueue.front();
            outFile << v.name << "," << v.purpose << "," << v.timeOfEntry << "\n";
            tempQueue.pop();
        }

        outFile.close();
    }

    // Load visitor data from file
    void loadFromFile() {
        std::ifstream inFile("visitors.txt");
        if (!inFile) {
            std::cout << "No previous visitor data found." << std::endl;
            return;
        }

        std::string name, purpose, time;
        while (getline(inFile, name, ',') && getline(inFile, purpose, ',') && getline(inFile, time)) {
            addVisitor(name, purpose, time);
        }

        inFile.close();
    }
};

#endif