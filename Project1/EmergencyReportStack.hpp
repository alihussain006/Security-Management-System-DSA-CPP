#pragma once
#ifndef EMERGENCYREPORTSTACK_H
#define EMERGENCYREPORTSTACK_H

#include <iostream>
#include <string>
#include <fstream>

struct EmergencyReport {
    std::string reportDetails;
    std::string reportTime;
    EmergencyReport* next;
};

class EmergencyReportStack {
private:
    EmergencyReport* top;

public:
    EmergencyReportStack() : top(nullptr) {}

    // Push a new emergency report onto the stack
    void pushReport(const std::string& details, const std::string& time) {
        EmergencyReport* newReport = new EmergencyReport{ details, time, top };
        top = newReport;
        std::cout << "Emergency report added." << std::endl;
    }

    // Pop the most recent emergency report
    void popReport() {
        if (top) {
            EmergencyReport* temp = top;
            top = top->next;
            delete temp;
            std::cout << "Emergency report handled." << std::endl;
        }
        else {
            std::cout << "No emergency reports to handle." << std::endl;
        }
    }

    // Display all emergency reports
    void displayReports() {
        if (!top) {
            std::cout << "No emergency reports available." << std::endl;
            return;
        }

        EmergencyReport* temp = top;
        std::cout << "\nEmergency Reports:\n";
        std::cout << "---------------------------\n";
        while (temp) {
            std::cout << "Details: " << temp->reportDetails << ", Time: " << temp->reportTime << std::endl;
            temp = temp->next;
        }
        std::cout << "---------------------------\n";
    }

    // Save emergency report data to file
    void saveToFile() {
        std::ofstream outFile("emergency_reports.txt");
        EmergencyReport* temp = top;
        while (temp) {
            outFile << temp->reportDetails << "," << temp->reportTime << "\n";
            temp = temp->next;
        }
        outFile.close();
    }

    // Load emergency reports from file
    void loadFromFile() {
        std::ifstream inFile("emergency_reports.txt");
        if (!inFile) {
            std::cout << "No previous emergency reports found." << std::endl;
            return;
        }

        std::string details, time;
        while (getline(inFile, details, ',') && getline(inFile, time)) {
            pushReport(details, time);
        }

        inFile.close();
    }
};

#endif