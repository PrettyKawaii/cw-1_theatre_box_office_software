// ПО_для_кассы_театра.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <stdio.h>                      
#include <string.h>
#include <string>

std::string getLogin()
{
    std::string login;
    std::cout << "Введите логин: ";
    std::cin >> login;
    return login;
}
std::string getPassword()
{
    std::string password;
    std::cout << "Введите пароль: ";
    std::cin >> password;
    return password;
}



int main()
{
    //std::cout << "Hello World!\n";
    std::string admin_login, admin_password, input_login, input_password;

    admin_login = "adminus";
    admin_password = "easy_password";

    bool isMatched = false;

    while (!isMatched)
    {
        input_login = getLogin();
        input_password = getPassword();
        if (input_login == admin_login && input_password == admin_password)
        {
            std::cout << "Авторизация прошла успешно. Вы администратор." << std::endl;
            isMatched = true;
        }
        else
        {
            std::cout << "Неверная комбинация логина и пароля. Повторите попытку." << std::endl;
            std::cin;
        }
    }



}






// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
