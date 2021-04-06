#pragma once
#include<iostream>
#include<fstream>   //used for file handling
#include<string> 
#include<sstream> 
#include "utility_functions.h"


class RegistrySystem
{
public:
	RegistrySystem();
	std::string username;
	std::string database_name;
	std::string Login(); // Login into User account. Returns username
	std::string Register(); // Register and automatically login into account. Returns username
private:
	// If database is missing, creates a new one
	void CreateDB();

	// When registering, validation for username
	std::string CreateUsername();

	// When registering, validation for password
	std::string CreatePassword();

	// When logging in, gets the password for the username typed in by the anon
	std::string GetUsernamePassword(std::string typed_username);
};
