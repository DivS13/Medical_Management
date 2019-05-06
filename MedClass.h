#pragma once
#include <string>
#include <iostream> 
#include <fstream>
#include <limits>

class Medicine
{
public :

	std::string getFileName();
	std::string getMedicineName();
	std::string getMedicineFormula();
	void displayMedInfo();
	int getMedUnitsLeft();
	void writeToFile();
	void getFromFile();
	void createFile();
	void setFileName(std::string &recieved);


private:
	
	std::fstream medicine_file;
	
	std::string file_name;
	std::string file_input;
	std::string med_name;
	std::string med_formula;
	std::string expiry_date;
	std::string med_company;
	float med_weight;
	float med_price;
	int med_units_left;
};