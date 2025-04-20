#include "ticket_system.h"

int main() {
    TicketManager ticketManager("tickets.txt");
    UserManager userManager("users.txt");

    // Добавляем администратора по умолчанию, если файл пустой
    if (userManager.getAllUsers().empty()) {
        userManager.addUser("admin", "admin123", true);
        userManager.addUser("user", "user123", false);
    }

    bool exit = false;
    while (!exit) {
        std::cout << "\nГлавное меню:\n";
        std::cout << "1. Вход как администратор\n";
        std::cout << "2. Вход как пользователь\n";
        std::cout << "3. Выход\n";
        std::cout << "> ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string login, password;
            bool isAdmin;
            std::cout << "Логин: ";
            std::cin >> login;
            std::cout << "Пароль: ";
            std::cin >> password;

            if (userManager.authenticate(login, password, isAdmin)) {
                if (isAdmin) {
                    showAdminMenu(ticketManager, userManager);
                }
                else {
                    std::cout << "У вас нет прав администратора!\n";
                }
            }
            else {
                std::cout << "Неверный логин или пароль!\n";
            }
            break;
        }
        case 2: {
            std::string login, password;
            bool isAdmin;
            std::cout << "Логин: ";
            std::cin >> login;
            std::cout << "Пароль: ";
            std::cin >> password;

            if (userManager.authenticate(login, password, isAdmin)) {
                showUserMenu(ticketManager);
            }
            else {
                std::cout << "Неверный логин или пароль!\n";
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