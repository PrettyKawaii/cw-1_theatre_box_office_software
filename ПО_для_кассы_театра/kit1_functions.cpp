#include <string>
#include <iostream>
#include <conio.h>
#include <cstdlib>

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
    std::string input;  // Для накопления введённых символов
    char ch;

    while ((ch = _getch()) != '\r')     // Пока не нажат Enter
    {
        if (ch >= '0' && ch <= '9')
        {
            std::cout << ch;            // Выводим цифру
            input += ch;                // Добавляем цифру в буфер
        }
        else if (ch == '\b' && !input.empty())  // Если нажат Backspace и есть что удалять
        {
            std::cout << "\b \b";       // Стираем последний символ в консоли
            input.pop_back();           // Удаляем последний символ из буфера
        }
        // Другие символы игнорируем
    }

    if (!input.empty())
    {
        return input[0] - '0';          // Возвращаем первую введённую цифру
    }
    return -1;                          // Если Enter нажат без ввода цифры
}

#include <conio.h>  // Для _getch()
#include <cstdlib>  // Для system()

void waitForAnyKeyAndClear() {
    std::cout << "\nНажмите любую клавишу для продолжения...";
    _getch();                   // Ожидание нажатия любой клавиши
    system("cls||clear");       // Очистка терминала (Windows/Linux)
}

