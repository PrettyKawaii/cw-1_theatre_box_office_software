#include "ticket_system.h"

int main() {
    TicketManager ticketManager("tickets.txt");
    UserManager userManager("users.txt");
    
    // Добавляем администратора по умолчанию, если файл пустой
    if (userManager.getAllUsers().empty()) {
        userManager.addUser("admin", "admin123", true);
        userManager.addUser("user", "user123", false);
    }
    std::string m1 = "+============================+";
    std::string m2 = "+----------------------------+";
    int var = 44;
    bool exit = false;
    while (!exit) {
        std::cout << m1 << std::endl;
        std::cout << std::setw(var) << std::left << "|Меню авторизации" << std::right << "|" << std::endl;
        std::cout << m1 << std::endl;

        std::cout << std::setw(var+5) << std::left << "|1. Вход как администратор" << std::right << "|" << std::endl;
        std::cout << m2 << std::endl;
        std::cout << std::setw(var+4) << std::left << "|2. Вход как пользователь" << std::right << "|" << std::endl;
        std::cout << m2 << std::endl;
        std::cout << std::setw(var-10) << std::left << "|3. Выход" << std::right << "|" << std::endl;
        std::cout << m1 << std::endl;

        std::cout << "> ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string login, password;
            bool isAdmin;
            
            std::cout << "\nЛогин: ";
            std::cin >> login;
            std::cout << "Пароль: ";
            std::cin >> password;

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
            std::cin >> password;

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