// Registration System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream>
#include<fstream>   //used for file handling
#include<string> 
#include<sstream> 
#include<vector> 


void CreateDB()
{
    std::cout << "Database missing. Creating new db.csv\n";
    std::fstream db;
    db.open("db.csv", std::ios::out);
    db << "username" << "," << "password" << "\n";
    return;
}


std::string InputRegType()
{
    std::string type;
    while (type != "log" && type != "reg")
    {
        std::cout << "Login/Register? (log/reg): ";
        std::cin >> type; // var containing type of action
    }
    return type;
}


std::string CreatePassword() 
{
    std::string typed_password;
    while (true)
    {
        char special[10] = { '!','@','#','$','%','^','&','*','(',')' };
        bool has_capital = false;
        bool has_special = false;

        std::cout << "Type in password with these requirements in mind: \n   1. Should be 8+ characters long \n" <<
            "   2. Must have at least one special character ~,!,@,#,$,%,^,&,*,(,)\n" <<
            "   3. Must have capital letters. \nPassword:";
        std::cin >> typed_password;

        if (typed_password.length() <= 7)
        {
            std::cout << "\n Password not long enought.\n";
            continue;
        }

        for (int char_i = 0; char_i <= (typed_password.length() - 1); char_i++)
        {
            if (std::tolower(typed_password[char_i]) != typed_password[char_i])
            {
                has_capital = true;
            }

            for (int schar_i = 0; schar_i <= 9; schar_i++)
            {
                if (special[schar_i] == typed_password[char_i]) {
                    has_special = true;
                    break;
                }
            }
        }

        if (has_capital && has_special) {
            std::cout << "Account created.\n";
            break;
        }
    }
    return typed_password;
}


std::string GetUsernamePassword(std::string username)
{

    std::ifstream data("db.csv");
    std::string line;
    std::string password;

    while (std::getline(data, line))
    {
        std::stringstream lineStream(line);

        std::string cell;
        std::vector<std::string> parsedRow;

        while (std::getline(lineStream, cell, ','))
        {
            parsedRow.push_back(cell);
        }
        if (username == parsedRow[0])
        {
            password = parsedRow[1];
        }
    }
    return password;
}


std::string CreateUsername()
{
    std::string typed_username;
    std::cout << "Type in username:";
    std::cin >> typed_username;
    bool username_not_taken;
    std::istringstream(GetUsernamePassword(typed_username)) >> username_not_taken;
    if (!username_not_taken)
    {
        std::cout << "This username is taken. Type in another one.\n";
        typed_username = CreateUsername();
    }
    return typed_username;
}


bool Login()
{
    std::string password; // info from database
    std::string typed_username, typed_password; // info from cin to compare

    //verifying existance of type username
    std::cout << "Type in username:";
    std::cin >> typed_username;
    bool username_not_taken;
    password = GetUsernamePassword(typed_username);
    std::istringstream(password) >> username_not_taken;
    if (username_not_taken)
    {
        std::cout << "This username doesn't exist.\n";
        return Login();
    }

    // five attempts to guess password
    for (int attempt = 0; attempt < 5; attempt++)
    {

        std::cout << "Type in password:";
        std::cin >> typed_password;
        if (typed_password == password)
        {
            std::cout << "\nSuccessful login.\n";
            return true;
        }
        else
        {
            std::cout << "\nUsername and password don't match!\n";
        }

        if (attempt == 4)
        {
            std::cout << "\n5 Attempts failed. Stopping program\n";
        }
    }
    return false;
}


bool Register()
{
    std::string typed_username, typed_password; // info from cin

    typed_username = CreateUsername();
    typed_password = CreatePassword();

    std::fstream db;
    db.open("db.csv", std::ios::out | std::ios::app);

    db << typed_username << "," << typed_password << "\n";

    return true;
}


int main()
{   
    std::cout << "Hello!\n";

    // checking that db exists
    std::ifstream db("db.csv");
    if (!db.is_open())
    {
        CreateDB();
    }


    if (InputRegType() == "log")
    {
        if (!Login()) {
            return 0;
        }
        std::cout << "logged in";
    }
    else
    {
        if (!Register()) {
            return 0;
        }
        std::cout << "registered";
    }
}
