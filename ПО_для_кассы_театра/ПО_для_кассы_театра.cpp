// ПО_для_кассы_театра.cpp (измененная функция main)

#include "ticket_system.h"
#include "kit1.h"
#include <conio.h>
#include <cstdlib> // Добавлен заголовочный файл для system()


//добавить стоимость и дату. посчитать кол-во свободных билетов по выбранному представлению + фильтрация





int main() {
    TicketManager ticketManager("tickets.txt");
    UserManager userManager("users.txt");

    // Добавляем администратора по умолчанию, если файл пустой
    if (userManager.getAllUsers().empty()) {
        userManager.addUser("admin", "password1", true);
        userManager.addUser("user", "password2", false);
    }
    std::string m1 = "+============================+";
    std::string m2 = "+----------------------------+";
    int var = 44;
    bool exit = false;
    while (!exit) {
        std::cout << m1 << std::endl;
        std::cout << std::setw(var) << std::left << "|Меню авторизации" << std::right << "|" << std::endl;
        std::cout << m1 << std::endl;

        std::cout << std::setw(var + 5) << std::left << "|1. Вход как администратор" << std::right << "|" << std::endl;
        std::cout << m2 << std::endl;
        std::cout << std::setw(var + 4) << std::left << "|2. Вход как пользователь" << std::right << "|" << std::endl;
        std::cout << m2 << std::endl;
        std::cout << std::setw(var - 10) << std::left << "|3. Выход" << std::right << "|" << std::endl;
        std::cout << m1 << std::endl;

        std::cout << "> ";

        int choice;
        choice = inputDigit();
        //std::cin >> choice;

        system("cls||clear"); // Очистка терминала

        switch (choice) {
        case 1: {
            std::string login, password;
            bool isAdmin;

            std::cout << "\nЛогин: ";
            std::cin >> login;
            std::cout << "Пароль: ";
            password = maskPassword();

            if (userManager.authenticate(login, password, isAdmin)) {
                if (isAdmin) {
                    std::cout << "\nВы успешно авторизовались как администратор.\n" << std::endl;
                    showAdminMenu(ticketManager, userManager);
                }
                else {
                    std::cout << "\nУ вас нет прав администратора!\n";
                }
            }
            else {
                std::cout << "\nНеверный логин или пароль!\n\n";
            }
            break;
        }
        case 2: {
            std::string login, password;
            bool isAdmin;
            std::cout << "Логин: ";
            std::cin >> login;
            std::cout << "Пароль: ";
            password = maskPassword();

            if (userManager.authenticate(login, password, isAdmin)) {
                std::cout << "\nВы успешно авторизовались как пользователь." << std::endl;
                showUserMenu(ticketManager);
            }
            else {
                std::cout << "Неверный логин или пароль!\n\n";
            }
            break;
        }
        case 3:
            exit = true;
            break;
        default:
            std::cout << "Неверный выбор!\n";
        }
    }

    return 0;
}