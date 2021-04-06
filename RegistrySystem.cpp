#include "RegistrySystem.h"

RegistrySystem::RegistrySystem()
{
    database_name = "db.csv";
    CreateDB();
}

std::string RegistrySystem::Login()
{
    std::string password; // info from database
    std::string typed_username, typed_password; // info from cin to compare

    //verifying existance of type username
    std::cout << "Type in username:";
    std::cin >> typed_username;
    bool username_not_taken;
    password = GetUsernamePassword(typed_username);
    // if a password exists, then the password's username exists
    std::istringstream(password) >> username_not_taken; 
    if (username_not_taken)
    {
        std::cout << "This username doesn't exist.\n";
        return Login();
    }

    // five attempts to guess password
    while (true)
    {

        std::cout << "Type in password:";
        std::cin >> typed_password;

        if (typed_password == password)
        {
            std::cout << "\nSuccessful login.\n";
            username = typed_username;
            return password;
        }

        else
        {
            std::cout << "\nUsername and password don't match!\n";
        }
    }
    return 0;
}

std::string RegistrySystem::Register()
{
    std::string typed_username, typed_password; 

    typed_username = CreateUsername();
    typed_password = CreatePassword();

    std::fstream db;
    db.open("db.csv", std::ios::out | std::ios::app);
    db << typed_username << "," << typed_password << "\n";

    std::cout << "Account created.\n";
    return username = typed_username;
}

void RegistrySystem::CreateDB()
{
    std::fstream db;
    std::ifstream file(database_name);
    if (!file.is_open()) {
        std::cout << database_name <<" missing. Creating new database file\n";
        db.open(database_name, std::ios::out);
    }
    return;
}

std::string RegistrySystem::CreatePassword()
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
        std::cout << std::endl;
        
        if (typed_password.length() <= 7)
        {
            std::cout << "Password not long enought.\n";
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
            break;
        }
    }
    return typed_password;
}

std::string RegistrySystem::CreateUsername()
{
    std::string typed_username;
    std::cout << "Type in username:";
    std::cin >> typed_username;
    std::cout << std::endl;
    bool username_not_taken;
    std::istringstream(GetUsernamePassword(typed_username)) >> username_not_taken;
    if (!username_not_taken)
    {
        std::cout << "This username is taken. Type in another one.\n";
        typed_username = CreateUsername();
    }
    return typed_username;
}

std::string RegistrySystem::GetUsernamePassword(std::string typed_username)
{
    std::ifstream data(database_name);
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
        if (typed_username == parsedRow[0])
        {
            password = parsedRow[1];
        }
    }
    return password;
}
