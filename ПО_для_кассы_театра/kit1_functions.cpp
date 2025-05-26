#include <string>
#include <iostream>
#include <conio.h>

std::string maskPassword()
{
    std::string password = "";
    char ch;
    const int MAX_PASSWORD_LENGTH = 128;
    while ((ch = _getch()) != '\r')
    {
        if (ch == '\b') {
            if (!password.empty())
            {
                password.pop_back();
                std::cout << "\b \b";
            }
        }
        else if (ch >= 32 && ch <= 126 && password.length() < MAX_PASSWORD_LENGTH) {
            password.push_back(ch);
            std::cout << '*';
        }
    }
    return password;
}

int inputDigit() 
{
    char ch;
    while ((ch = _getch()) != '\r')     // Пока не нажат Enter
    {  
        if (ch >= '0' && ch <= '9') 
        {
            std::cout << ch;            // Выводим цифру
            return ch - '0';            // Преобразуем символ в число (например, '5' → 5)
        }
                                        // Если нажат Backspace или другой символ — игнорируем
    }
    return -1;                          // Если Enter нажат без ввода цифры
}