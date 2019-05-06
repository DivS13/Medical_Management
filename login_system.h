#pragma once

#include <fstream>
#include <iostream>
#include <limits>
#include <string>


template <typename T>
T get_input(const std::string &strQuery);

std::string get_username();
std::string get_password();
void save_user(const std::string username, const std::string password);
void save_admin(const std::string username, const std::string password);

void user_login();
void register_user();
void login_menu();
int  login_fucntion();
void user_log_out();
bool is_user_logged_in();
bool is_admin_logged_in();

void register_admin();
void admin_login();

void log_out_menu();

extern bool user_logged_in;
extern bool admin_logged_in;