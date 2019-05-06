#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>

#include "MedClass.h"
#include "login_system.h"

#include <iomanip>
#define _CRT_SECURE_NO_DEPRECATE






void PrintIntro();
int Menu();
void ViewMedicines();
void BuyMedicine(std::string &med_name);
void ViewInventory();
void InventoryUpdate();

void SummaryPrint();
void SummaryUpdate(std::string &entry);

Medicine med;



int main()
{
	int choice;
	
	do {
		PrintIntro();
		choice = Menu();
		if (choice == 1)
		{
			ViewMedicines();
		}
		else if (choice == 2)
		{
			ViewInventory();
		}
		else if (choice == 3)
		{
			SummaryPrint();
		}
		else if (choice == 4)
		{
			login_menu();
			
		}
	} while (choice != 5);

	return 0;
}

void PrintIntro()
{
	std::cout << std::string(2, '\n');
	std::cout << "**********************************************\n";
	std::cout << "Welcome to our medicine management facility!!!\n";
	std::cout << "**********************************************\n";
	std::cout << std::endl << std::endl;
	return;
}

int Menu()
{
	
	int choice;
	std::cout << "\n\n[1] - ViewMedicines \n[2] - ViewInventory \n[3] - Summary\n[4] - Login Menu\n[5] - Exit\n\n";
	choice = get_input<int>("Enter your choice : ");
	
	return choice;
}

void ViewMedicines()
{
	
	int choice;
	std::string medicine_name;
	std::string medicine_filename;
	
	std::cout << "\n\n[1].Browse with medicine name\n[2]Go back to Main Menu\n";
	choice = get_input<int>("Enter your choice : ");
	if (choice == 1)
	{

		medicine_name = get_input<std::string>("Enter Medicine Name : ");
		medicine_filename = "Medicines\\" + medicine_name + ".txt";
		std::ifstream check_med_by_name;
		check_med_by_name.open(medicine_filename);
		if (!check_med_by_name.is_open())
		{
			std::cout << "Medicine not found\n";
			std::cout << "[1].Browse Another Medicine \n[2].Get back to Main Menu\n";
			choice = get_input<int>("Enter your choice : ");
			if (choice == 1)
				ViewMedicines();
			else
				return;
		}
		else
		{
			med.setFileName(medicine_filename);
			med.getFromFile();
			med.displayMedInfo();
			check_med_by_name.close();
			std::cout << "\n[1].Buy Medicine \n[2].Browse Another Medicine \n[3].Get back to Main Menu\n";
			choice = get_input<int>("Enter your choice : ");
			if (choice == 1) 
			{
				
				BuyMedicine(medicine_name);
			}
			else if (choice == 2)
				ViewMedicines();
			else
				return;
		}

	}
	else
	{
		return;
	}
	return;
}

void BuyMedicine(std::string &med_name)
{
	
	if (is_user_logged_in())
	{
		std::string entry;
		std::string name = get_input<std::string>("Enter your name :");
		entry = name + "-" + med_name + "-" ;
		SummaryUpdate(entry);
		std::cout << "Successfully purchased medicine ";
	}
	else
	{
		std::cout << "You need to log in --> \n\n";
		user_login();
		if (is_user_logged_in())
		{
			std::string entry;
			std::string name = get_input<std::string>("Enter your name :");
			entry = name + "-" + med_name + "-";
			SummaryUpdate(entry);
			
			std::cout << "Successfully purchased medicine ";
		}
	}
	return;
}

void ViewInventory()
{
	int choice;
	std::fstream print;
	print.open("Inventory.txt");
	std::string read;
	if (!print.is_open())
		std::cout << "File Not Found\n";
	else
	{
		while (print >> read)
		{

			std::cerr << read << std::endl;
		}

	};

		std::cout << "[1].Add Medicine \n[2].Go back to menu\n";
		choice = get_input<int>("Enter your choice : ");
		if (choice == 1)
			InventoryUpdate();
		else
			return;
	return;
}

void InventoryUpdate()
{
	std::ofstream update_inventory;
	std::string medicine_name;
	std::string medicine_filename;
	Medicine new_med;
	int choice;
	while (!is_admin_logged_in())
	{
		std::cout << "!!!You need administrator access to proceed!!!\n";
		admin_login();
		std::cout << "[1]Proceed \n[2]Return back\n";
		choice = get_input<int>("Enter your choice : ");
		if (choice == 1)
			continue;
		else if (choice == 2)
			return;
	}
	
	medicine_name = get_input<std::string>("Enter Medicine Name : ");
	std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
	medicine_filename = "Medicines\\" + medicine_name + ".txt";
	new_med.setFileName(medicine_filename);
	update_inventory.open("Inventory.txt",std::ios::app);
	update_inventory << std::endl << medicine_name;
	update_inventory.close();

	new_med.createFile();
	new_med.writeToFile();
	return;
}



void SummaryPrint()
{
	std::fstream print;
	print.open("Summary.txt");
	std::string read;
	if (!print.is_open())
		std::cout << "File Not Found\n";
	else
	{
		while (print>>read)
		{
			
			std::cerr << read << std::endl;
		}
		
	}
	return;
}

void SummaryUpdate(std::string &entry)
{
	std::string new_entry;
	
	std::fstream update;
	update.open("Summary.txt", std::ios::app);
	update << std::endl << entry ;
	return;
}