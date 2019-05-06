#include "login_system.h"

bool user_logged_in = false;
bool admin_logged_in = false;


bool is_user_logged_in()
{
	return user_logged_in;
}

void user_log_out()
{
	user_logged_in = false;
	std::cout << "User logged out successfully\n";
}

bool is_admin_logged_in()
{
	return admin_logged_in;
}

void admin_log_out()
{
	
	admin_logged_in = false;
	std::cout << "Admin logged out successfully\n";
}

void log_out_menu()
{
	int choice;
	if (is_admin_logged_in())
		std::cout << "Admin is logged in\n\n";
	if (is_user_logged_in())
		std::cout << "User is logged in\n\n";
	if (!is_admin_logged_in() && !is_user_logged_in())
	{
		std::cout << "No one is Logged in.Returning to Login Menu\n\n";
	}
	else
	{
		std::cout << "[0]Return to login menu\n";
		if (is_admin_logged_in())
			std::cout << "[1]Admin Logout\n";
		if (is_user_logged_in());
		std::cout << "[2]User Logout\n";
		choice = get_input<int>("Enter your choice : ");
		if (choice == 0)
			return;
		else if (choice == 1 && is_admin_logged_in())
			admin_log_out();
		else if (choice == 2 && is_user_logged_in())
			user_log_out();
	}
	return;
}

int login_fucntion()
{
	login_menu();
	return 0;
}

template <typename T>
T get_input(const std::string &strQuery)
{
	std::cout << strQuery << "\n> ";
	T out = T();

	while (!(std::cin >> out)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
		std::cout << "Error!" "\n";
		std::cout << strQuery << "\n> ";
	}

	return out;
}

std::string get_password()
{
	std::string password1 = get_input <std::string>("Please enter your password.");
	std::string password2 = get_input <std::string>("Please re-enter your password.");

	while (password1 != password2) {
		std::cout << "Error! Passwords do not match." "\n";
		password1 = get_input <std::string>("Please enter your password.");
		password2 = get_input <std::string>("Please re-enter your password.");
	}

	return password1;
}

std::string get_username()
{
	std::string username = get_input <std::string>("Please enter a username.");
	std::cout << "Username: \"" << username << "\"\n";

	while (get_input <int>("Confirm? [0|1]") != 1) {
		username = get_input <std::string>("Please enter a username.");
		std::cout << "Username: \"" << username << "\"\n";
	}

	return username;
}





void login_menu()
{
	int choice = 0;
	do {
		if (is_user_logged_in() || is_admin_logged_in())
		{
			choice = get_input <int>(
				"\n\n\n\nHello, Would you like to log in or register?" "\n"
				"[1] Login" "\n"
				"[2] Register" "\n"
				"[3] Go Back to Main Menu" "\n"
				"[4] Logout" "\n");
		}
		else
		{
			choice = get_input <int>(
				"\n\n\n\nHello, Would you like to log in or register?" "\n"
				"[1] Login" "\n"
				"[2] Register" "\n"
				"[3] Go Back to Main Menu");
		}

		if (choice == 1)
		{
			std::cout << "[1]User Login \n[2]Admin Login\n";
			choice = get_input<int>("Enter your choice : ");
			if (choice == 1)
			{
				if (is_user_logged_in())
					std::cout << "Some User is already logged in\n";
				else
					user_login();
			}
			else
			{
				if (is_admin_logged_in())
					std::cout << "Admin is already logged in\n";
				else
					admin_login();
			}
		
		}

		else if (choice == 2)
		{
			std::cout << "[1]Register User \n[2]Register Admin\n";
			choice = get_input<int>("Enter your choice : ");
			if (choice == 1)
				register_user();
			else
			{
				int secret_word;
				std::cout << "!!!Secret Code Is Required To register as admin!!!\n";
				secret_word = get_input<int>("Enter Secret Code : ");
				if (secret_word == 11110000)
					register_admin();
				else
					std::cout << "Wrong Secret Code\n";
			}
		}

		else if (choice == 4 && (is_admin_logged_in() || is_user_logged_in()))
			log_out_menu();
		
		
	}while (choice != 3);
}

void user_login()
{


	std::string user = get_username();
	std::string pass = get_password();
	std::string login_pass;

	std::string login_file = "Users\\" + user + ".txt";

	std::ifstream login_user;
	login_user.open(login_file);
	login_user >> login_pass;
	if (!login_user.is_open())
	{
		std::cout << "User not found\n";

	}
	else {
		if (pass == login_pass)
		{
			std::cout << "Welcome " << user << ". You logged in successfully \n";
			user_logged_in = true;
		}
		else
			std::cout << "Wrong Password \n";
	}

	return;
}

void register_user()
{
	std::string username = get_username();
	
	std::string username_file = "Users\\" + username + ".txt";
	
	std::ifstream loginfile(username_file);
	if (loginfile.is_open())
	{
		std::cout << "User already exists.Try Again" << std::endl;

	}
	else
	{
		std::string password = get_password();
		save_user(username, password);
		std::cout << "Registered Successfully with username :- "<<username<<std::endl;
	}
}

void save_user(const std::string username, const std::string password)
{
	
	std::string filename = "Users\\" + username + ".txt";
	
	std::ofstream file(filename);
	file << password << "\n";
}



void admin_login()
{


	std::string user = get_username();
	std::string pass = get_password();
	std::string login_pass;

	std::string login_file = "Admin\\" + user + ".txt";

	std::ifstream login_user;
	login_user.open(login_file);
	login_user >> login_pass;
	if (!login_user.is_open())
	{
		std::cout << "User not found\n";

	}
	else {
		if (pass == login_pass)
		{
			std::cout << "Welcome " << user << ". You logged in successfully \n";
			admin_logged_in = true;
		}
		else
			std::cout << "password does not match for the claimed user \n";
	}

	return;
}

void register_admin()
{
	std::string username = get_username();

	std::string username_file = "Admin\\" + username + ".txt";

	std::ifstream loginfile(username_file);
	if (loginfile.is_open())
	{
		std::cout << "User already exists.Try Again" << std::endl;

	}
	else
	{
		std::string password = get_password();
		save_admin(username, password);
		std::cout << "Registered Successfully with username :- " << username << std::endl;
	}
}

void save_admin(const std::string username, const std::string password)
{

	std::string filename = "Admin\\" + username + ".txt";

	std::ofstream file(filename);
	file << password << "\n";
}
