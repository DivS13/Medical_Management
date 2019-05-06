#include "MedClass.h"


std::string Medicine::getFileName()
{
	return file_name;
}

std::string Medicine::getMedicineName()
{
	return med_name;
}

std::string Medicine::getMedicineFormula()
{
	return med_formula;
}

void Medicine::displayMedInfo()
{
	std::cout << "Details of selected medicine : \n\n";
	std::cout << "Medicine name :- " << med_name << std::endl;
	std::cout << "Medicine formula :- " << med_formula << std::endl;
	std::cout << "Medicine weight :- " << med_weight << std::endl;
	std::cout << "Medicine Price :- " << med_price << std::endl;
	std::cout << "Medicine Expiry Date :- " << expiry_date << std::endl;
	std::cout << "Meicine Comapny :- " << med_company << std::endl;
}

int Medicine::getMedUnitsLeft()
{
	return med_units_left;
}

void Medicine::writeToFile()
{
	
	
	medicine_file.open(file_name);
	std::cout << "Enter details of medicine in following format :- \n";
	std::cout << "Name Formula Weight Price Company Expiry\n";
	getline(std::cin, file_input);
	medicine_file << file_input;
	medicine_file.close();
	std::cout << "File input validated\n";
}

void Medicine::getFromFile()
{
	medicine_file.open(file_name);
	medicine_file >> med_name>>med_formula>>med_weight>>med_price>>med_company>>expiry_date;
	medicine_file.close();
}

void Medicine::createFile()
{
	
	
	std::ofstream create_file(file_name);
	if (!create_file.is_open())
		std::cout << "file is not opening\n";
	create_file.close();
}

void Medicine::setFileName(std::string &recieved)
{
	file_name = recieved;
}


