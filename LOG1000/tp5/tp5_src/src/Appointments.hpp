#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <numeric>

#include "Constants.hpp"
#include "CSVHandler.hpp"


class Appointments
{
public:
    Appointments(std::string filePath);
    void display(unsigned int userCol, std::string userId, std::vector<unsigned int> displayedColumns = {});
    bool schedule(std::string patientId, std::string nurseId);
    int getHoursRate(std::string patientDisease, unsigned int nurseExperience);
    std::vector<std::vector<std::string>>* getData();
    void setData(std::vector<std::vector<std::string>> data);

    //modif
    void displayScreen(std::vector<std::vector<std::string>>& filteredAppointment, std::vector<unsigned int>&displayedColumns);
    std::vector<std::vector<std::string>>filteredAppointment(unsigned int userCol, std::string userId);
    void displayColumns(std::vector<unsigned int>& displayedColumns);
    std::vector<unsigned int> putInColumns(std::vector<unsigned int>& displayedColumns);
    //fin modif
private:
    std::vector<std::string> createNewAppointment(std::string patientId, std::string nurseId);

    std::vector<std::string> _headers;
    CSVHandler _csvHandler;
    //modif
    //std::vector<std::string>>_appointments
    std::vector<std::vector<std::string>> _data;
    //fin modif
    


    const unsigned int _COLUMN_WIDTH = 14;
};
