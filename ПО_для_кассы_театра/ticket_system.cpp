#include "ticket_system.h"
#include "string"

// Реализация TicketManager
TicketManager::TicketManager(const std::string& filename) : dataFile(filename) {
    loadTickets();
}

TicketManager::~TicketManager() {
    saveTickets();
}

void TicketManager::loadTickets() {
    std::ifstream file(dataFile);
    if (file.is_open()) {
        Ticket ticket;
        while (file >> ticket.id >> ticket.date >> ticket.time >> ticket.performance
            >> ticket.hallNumber >> ticket.zone >> ticket.seatNumber >> ticket.ageLimit) {
            tickets.push_back(ticket);
        }
        file.close();
    }
}

void TicketManager::saveTickets() {
    std::ofstream file(dataFile);
    if (file.is_open()) {
        for (const auto& ticket : tickets) {
            file << ticket.id << " " << ticket.date << " " << ticket.time << " "
                << ticket.performance << " " << ticket.hallNumber << " "
                << ticket.zone << " " << ticket.seatNumber << " " << ticket.ageLimit << "\n";
        }
        file.close();
    }
}

void TicketManager::addTicket(const Ticket& ticket) {
    tickets.push_back(ticket);
}

void TicketManager::editTicket(int id, const Ticket& newTicket) {
    auto it = std::find_if(tickets.begin(), tickets.end(),
        [id](const Ticket& t) { return t.id == id; });
    if (it != tickets.end()) {
        *it = newTicket;
    }
}

void TicketManager::removeTicket(int id) {
    tickets.erase(std::remove_if(tickets.begin(), tickets.end(),
        [id](const Ticket& t) { return t.id == id; }), tickets.end());
}

std::vector<Ticket> TicketManager::getAllTickets() const {
    return tickets;
}

std::vector<Ticket> TicketManager::filterTickets(const std::string& field, const std::string& value) const {
    std::vector<Ticket> result;
    for (const auto& ticket : tickets) {
        if ((field == "date" && ticket.date == value) ||
            (field == "performance" && ticket.performance == value) ||
            (field == "zone" && ticket.zone == value)) {
            result.push_back(ticket);
        }
    }
    return result;
}

// Реализация UserManager
UserManager::UserManager(const std::string& filename) : userFile(filename) {
    loadUsers();
}

UserManager::~UserManager() {
    saveUsers();
}

void UserManager::loadUsers() {
    std::ifstream file(userFile);
    if (file.is_open()) {
        User user;
        while (file >> user.login >> user.password >> user.isAdmin) {
            users.push_back(user);
        }
        file.close();
    }
}

void UserManager::saveUsers() {
    std::ofstream file(userFile);
    if (file.is_open()) {
        for (const auto& user : users) {
            file << user.login << " " << user.password << " " << user.isAdmin << "\n";
        }
        file.close();
    }
}

bool UserManager::authenticate(const std::string& login, const std::string& password, bool& isAdmin) {
    auto it = std::find_if(users.begin(), users.end(),
        [&](const User& u) { return u.login == login && u.password == password; });
    if (it != users.end()) {
        isAdmin = it->isAdmin;
        return true;
    }
    return false;
}

void UserManager::addUser(const std::string& login, const std::string& password, bool isAdmin) {
    users.push_back({ login, password, isAdmin });
}

void UserManager::editUser(const std::string& login, const std::string& newPassword, bool newIsAdmin) {
    auto it = std::find_if(users.begin(), users.end(),
        [&](const User& u) { return u.login == login; });
    if (it != users.end()) {
        it->password = newPassword;
        it->isAdmin = newIsAdmin;
    }
}

void UserManager::removeUser(const std::string& login) {
    users.erase(std::remove_if(users.begin(), users.end(),
        [&](const User& u) { return u.login == login; }), users.end());
}

std::vector<User> UserManager::getAllUsers() const {
    return users;
}

// Вспомогательные функции
Ticket inputTicket() {
    Ticket ticket;
    std::cout << "Введите ID: ";
    std::cin >> ticket.id;
    std::cout << "Введите дату (дд.мм.гггг): ";
    std::cin >> ticket.date;
    std::cout << "Введите время (чч:мм): ";
    std::cin >> ticket.time;
    std::cout << "Введите название представления: ";
    std::cin.ignore();
    std::getline(std::cin, ticket.performance);
    std::cout << "Введите номер зала: ";
    std::cin >> ticket.hallNumber;
    std::cout << "Введите зону (parter/balcony/beletage ): ";
    std::cin >> ticket.zone;
    std::cout << "Введите номер места: ";
    std::cin >> ticket.seatNumber;
    std::cout << "Введите возрастное ограничение: ";
    std::cin >> ticket.ageLimit;
    return ticket;
}

void printTickets(const std::vector<Ticket>& tickets) {
    std::string m1 = "+===========================================================+";
    std::cout << m1 << std::endl;
    std::cout << "\nСписок билетов:\n";
    /*std::cout << std::setw(3) << "ID" << std::setw(24) << "Дата" << std::setw(22) << "Время"
        << std::setw(30) << "Представление" << std::setw(8) << "Зал"
        << std::setw(10) << "Зона" << std::setw(10) << "Место" << std::setw(28) << "Ограничение\n";
    for (const auto& ticket : tickets) {
        std::cout << std::setw(3) << ticket.id << std::setw(12) << ticket.date << std::setw(11) << ticket.time
            << std::setw(30) << ticket.performance << std::setw(8) << ticket.hallNumber
            << std::setw(10) << ticket.zone << std::setw(10) << ticket.seatNumber << std::setw(28) << ticket.ageLimit << "\n";
    }*/
    std::cout << "---\n";
#include <iomanip> // для std::setw

    // Определяем длину самого длинного поля
    const int max_field_length = 13; // "Представление" - 13 символов

    for (const auto& ticket : tickets) {
        std::cout << "Билет ID " << ticket.id << "\n";

        std::cout << "Дата"; std::cout << std::setw(max_field_length - 4 + 3); std::cout << ": " << ticket.date << "\n";
        std::cout << "Время"; std::cout << std::setw(max_field_length - 5 + 3); std::cout << ": " << ticket.time << "\n";
        std::cout << "Представление"; std::cout << std::setw(max_field_length - 13 + 3); std::cout << ": " << ticket.performance << "\n";
        std::cout << "Зал"; std::cout << std::setw(max_field_length - 3 + 3); std::cout << ": " << ticket.hallNumber << "\n";
        std::cout << "Зона"; std::cout << std::setw(max_field_length - 4 + 3); std::cout << ": " << ticket.zone << "\n";
        std::cout << "Место"; std::cout << std::setw(max_field_length - 5 + 3); std::cout << ": " << ticket.seatNumber << "\n";
        std::cout << "Ограничение"; std::cout << std::setw(max_field_length - 11 + 3); std::cout << ": " << ticket.ageLimit << "\n";

        std::cout << "---\n";  // разделитель между билетами
    }
    std::cout << m1 << std::endl;
}

void printUsers(const std::vector<User>& users) {
    std::cout << "\nСписок пользователей:\n";
    std::cout << std::setw(40) << "Логин" << std::setw(40) << "Пароль"
        << std::setw(30) << "Администратор\n";
    for (const auto& user : users) {
        std::cout << std::setw(20) << user.login << std::setw(20) << user.password
            << std::setw(15) << (user.isAdmin ? "Да" : "Нет") << "\n";
    }
}
void showTicketMenu(TicketManager& ticketManager) {
    int choice;
    bool back = false;

    while (!back) {
        std::cout << "\nУправление билетами:\n";
        std::cout << "1. Просмотреть все билеты\n";
        std::cout << "2. Добавить билет\n";
        std::cout << "3. Редактировать билет\n";
        std::cout << "4. Удалить билет\n";
        std::cout << "5. Фильтровать билеты\n";
        std::cout << "6. Назад\n";
        std::cout << "> ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            auto tickets = ticketManager.getAllTickets();
            printTickets(tickets);
            break;
        }
        case 2: {
            Ticket ticket = inputTicket();
            ticketManager.addTicket(ticket);
            std::cout << "Билет добавлен!\n";
            break;
        }
        case 3: {
            int id;
            std::cout << "Введите ID билета для редактирования: ";
            std::cin >> id;
            Ticket ticket = inputTicket();
            ticketManager.editTicket(id, ticket);
            std::cout << "Билет изменен!\n";
            break;
        }
        case 4: {
            int id;
            std::cout << "Введите ID билета для удаления: ";
            std::cin >> id;
            ticketManager.removeTicket(id);
            std::cout << "Билет удален!\n";
            break;
        }
        case 5: {
            std::string field, value;
            std::cout << "Введите поле для фильтрации (date/performance/zone): ";
            std::cin >> field;
            std::cout << "Введите значение: ";
            std::cin >> value;
            auto tickets = ticketManager.filterTickets(field, value);
            printTickets(tickets);
            break;
        }
        case 6:
            back = true;
            break;
        default:
            std::cout << "Неверный выбор!\n";
        }
    }
}

void showUserMenu(UserManager& userManager) {
    int choice;
    bool back = false;

    while (!back) {
        std::cout << "\nУправление пользователями:\n";
        std::cout << "1. Просмотреть всех пользователей\n";
        std::cout << "2. Добавить пользователя\n";
        std::cout << "3. Редактировать пользователя\n";
        std::cout << "4. Удалить пользователя\n";
        std::cout << "5. Назад\n";
        std::cout << "> ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            auto users = userManager.getAllUsers();
            printUsers(users);
            break;
        }
        case 2: {
            std::string login, password;
            bool isAdmin;
            std::cout << "Введите логин: ";
            std::cin >> login;
            std::cout << "Введите пароль: ";
            std::cin >> password;
            std::cout << "Администратор? (1 - да, 0 - нет): ";
            std::cin >> isAdmin;
            userManager.addUser(login, password, isAdmin);
            std::cout << "Пользователь добавлен!\n";
            break;
        }
        case 3: {
            std::string login, password;
            bool isAdmin;
            std::cout << "Введите логин для редактирования: ";
            std::cin >> login;
            std::cout << "Введите новый пароль: ";
            std::cin >> password;
            std::cout << "Администратор? (1 - да, 0 - нет): ";
            std::cin >> isAdmin;
            userManager.editUser(login, password, isAdmin);
            std::cout << "Пользователь изменен!\n";
            break;
        }
        case 4: {
            std::string login;
            std::cout << "Введите логин для удаления: ";
            std::cin >> login;
            userManager.removeUser(login);
            std::cout << "Пользователь удален!\n";
            break;
        }
        case 5:
            back = true;
            break;
        default:
            std::cout << "Неверный выбор!\n";
        }
    }
}

void showAdminMenu(TicketManager& ticketManager, UserManager& userManager) {
    int choice;
    bool back = false;

    while (!back) {
        std::cout << "\nМеню администратора:\n";
        std::cout << "1. Управление билетами\n";
        std::cout << "2. Управление пользователями\n";
        std::cout << "3. Выход\n";
        std::cout << "> ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            showTicketMenu(ticketManager);
            break;
        case 2:
            showUserMenu(userManager);
            break;
        case 3:
            back = true;
            break;
        default:
            std::cout << "Неверный выбор!\n";
        }
    }
}

void showUserMenu(TicketManager& ticketManager) {
    int choice;
    bool back = false;

    while (!back) {
        std::cout << "\nМеню пользователя:\n";
        std::cout << "1. Просмотреть все билеты\n";
        std::cout << "2. Поиск билетов\n";
        std::cout << "3. Выход\n";
        std::cout << "> ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            auto tickets = ticketManager.getAllTickets();
            printTickets(tickets);
            break;
        }
        case 2: {
            std::string field, value;
            std::cout << "Введите поле для поиска (date/performance/zone): ";
            std::cin >> field;
            std::cout << "Введите значение: ";
            std::cin >> value;
            auto tickets = ticketManager.filterTickets(field, value);
            printTickets(tickets);
            break;
        }
        case 3:
            back = true;
            break;
        default:
            std::cout << "Неверный выбор!\n";
        }
    }
}