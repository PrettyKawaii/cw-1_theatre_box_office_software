#include "ticket_system.h"
#include <iostream>
#include "string"
#include <iomanip> // для std::setw
#include <regex>
#include <cstdlib>
#include <Windows.h>

#include "kit1.h"





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
            >> ticket.hallNumber >> ticket.zone >> ticket.seatNumber >> ticket.ageLimit
            >> ticket.saleDate >> ticket.price) {
            tickets.push_back(ticket);
        }
        file.close();
    }
}

void TicketManager::saveTickets() {
    std::ofstream file(dataFile, std::ios::out | std::ios::trunc); // Перезаписываем файл
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл для сохранения!\n";
        return;
    }

    for (const auto& ticket : tickets) {
        file << ticket.id << " "
            << ticket.date << " "
            << ticket.time << " "
            << ticket.performance << " "
            << ticket.hallNumber << " "
            << ticket.zone << " "
            << ticket.seatNumber << " "
            << ticket.ageLimit << " "
            << ticket.saleDate << " "
            << ticket.price << "\n";
    }

    file.close();
    //std::cout << "Билеты успешно сохранены.\n"; // Для отладки (можно убрать)
}


void printTicketsWithCheck(const std::vector<Ticket>& tickets) {
    if (tickets.empty()) {
        std::cout << "\n+=======================================+\n";
        std::cout << "|              Билетов нет              |\n";
        std::cout << "+=======================================+\n";
    }
    else {
        printTickets(tickets); // Используем существующую функцию для вывода
    }
}

std::vector<Ticket> TicketManager::getAvailableTickets() const {
    std::vector<Ticket> result;
    for (const auto& ticket : tickets) {
        if (ticket.saleDate.empty()) {
            result.push_back(ticket);
        }
    }
    return result;
}

void printAvailableTicketsWithCheck(const TicketManager& manager) {
    auto tickets = manager.getAvailableTickets();
    if (tickets.empty()) {
        std::cout << "\n+=======================================+\n";
        std::cout << "|      Нет свободных билетов           |\n";
        std::cout << "+=======================================+\n";
    } else {
        printTickets(tickets);
    }
}

int TicketManager::countAvailableTickets(const std::string& performance) const {
    int count = 0;
    for (const auto& ticket : tickets) {
        if (ticket.saleDate.empty() && ticket.performance == performance) {
            count++;
        }
    }
    return count;
}

void TicketManager::setTicketSaleDate(int id, const std::string& saleDate) {
    auto it = findTicket(id);
    if (it == tickets.end()) {
        std::cerr << "Ошибка: Билет с ID " << id << " не найден!\n";
        return;
    }
    it->saleDate = saleDate;
    std::cout << "Дата продажи билета успешно изменена.\n";
}



int TicketManager::generateNextId() {
    int maxId = 0;
    for (const auto& t : tickets) if (t.id > maxId) maxId = t.id;
    return maxId + 1;
}

void TicketManager::addTicket(const Ticket& ticket) {
    tickets.push_back(ticket);
}

void TicketManager::editTicket(int id, const Ticket& newTicket) {
    auto it = findTicket(id);
    if (it == tickets.end()) {
        std::cerr << "Ошибка: Билет с ID " << id << " не найден!\n";
        return;
    }
    *it = newTicket;  // Заменяем старый билет новыми данными
    std::cout << "Билет успешно изменен.\n";
}

void TicketManager::removeTicket(int id) {
    auto it = findTicket(id);
    if (it == tickets.end()) {
        std::cerr << "Ошибка: Билет с ID " << id << " не найден!\n";
        return;
    }
    tickets.erase(it);
    std::cout << "Билет успешно удален.\n";
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
        isAdmin = it -> isAdmin;
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

std::string inputDate() {
    std::regex datePattern(R"((\d{2})\.(\d{2})\.(\d{4}))"); // Группы для дня, месяца и года
    std::string date;

    while (true) {
        std::cout << "Введите дату (дд.мм.гггг): ";
        std::cin >> date;

        std::smatch matches;
        if (!std::regex_match(date, matches, datePattern)) {
            std::cerr << "Ошибка: неверный формат даты!\n";
            continue;
        }

        // Извлекаем день, месяц и год
        int day = std::stoi(matches[1].str());
        int month = std::stoi(matches[2].str());
        int year = std::stoi(matches[3].str());

        // Проверяем диапазоны
        if (month < 1 || month > 12) {
            std::cerr << "Ошибка: месяц должен быть от 01 до 12!\n";
            continue;
        }

        if (day < 1 || day > 31) {
            std::cerr << "Ошибка: день должен быть от 01 до 31!\n";
            continue;
        }

        // Дополнительная проверка на корректность дня в месяце (например, 30.02 или 31.04)
        // Можно добавить проверку високосного года для февраля
        bool isValid = true;
        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
            isValid = false;
        }
        else if (month == 2) {
            bool isLeap = (year % 400 == 0) || (year % 100 != 0 && year % 4 == 0);
            if (day > (isLeap ? 29 : 28)) {
                isValid = false;
            }
        }

        if (!isValid) {
            std::cerr << "Ошибка: некорректная дата (день не соответствует месяцу)!\n";
            continue;
        }

        return date;
    }
}

// Не-const версия (для изменения билета)
std::vector<Ticket>::iterator TicketManager::findTicket(int id) {
    return std::find_if(tickets.begin(), tickets.end(),
        [id](const Ticket& t) { return t.id == id; });
}

// Const-версия (только для чтения)
std::vector<Ticket>::const_iterator TicketManager::findTicket(int id) const {
    return std::find_if(tickets.cbegin(), tickets.cend(),
        [id](const Ticket& t) { return t.id == id; });
}

bool UserManager::userExists(const std::string& login) const {
    return std::any_of(users.begin(), users.end(),
        [&login](const User& u) { return u.login == login; });
}

std::string inputSaleDate() {
    std::regex datePattern(R"((\d{2})\.(\d{2})\.(\d{4}))");
    std::string date;

    while (true) {
        std::cout << "Введите дату продажи (дд.мм.гггг или оставьте пустым для Free): ";
        std::cin.ignore(); // Очищаем буфер перед вводом строки
        std::getline(std::cin, date);

        // Если строка пустая - билет свободен
        if (date.empty()) {
            return "";
        }

        std::smatch matches;
        if (!std::regex_match(date, matches, datePattern)) {
            std::cerr << "Ошибка: неверный формат даты!\n";
            continue;
        }

        int day = std::stoi(matches[1].str());
        int month = std::stoi(matches[2].str());
        int year = std::stoi(matches[3].str());

        if (month < 1 || month > 12) {
            std::cerr << "Ошибка: месяц должен быть от 01 до 12!\n";
            continue;
        }

        if (day < 1 || day > 31) {
            std::cerr << "Ошибка: день должен быть от 01 до 31!\n";
            continue;
        }

        bool isValid = true;
        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
            isValid = false;
        }
        else if (month == 2) {
            bool isLeap = (year % 400 == 0) || (year % 100 != 0 && year % 4 == 0);
            if (day > (isLeap ? 29 : 28)) {
                isValid = false;
            }
        }

        if (!isValid) {
            std::cerr << "Ошибка: некорректная дата (день не соответствует месяцу)!\n";
            continue;
        }

        return date;
    }
}

std::string inputTime()
{
    std::regex timePattern(R"((\d{2})\:(\d{2}))"); // чч:мм
    std::string time;
    std::smatch matches;
    while (true)
    {
        std::cout << "Введите время (чч:мм): ";
        std::cin >> time;

        if (!std::regex_match(time, matches, timePattern))
        {
            std::cerr << "Ошибка: некорректный формат времени!\n";
            continue;
        }
        
        int hour = std::stoi(matches[1].str());
        int mininutes = std::stoi(matches[2].str());
        
        if (hour < 0 || hour > 23) {
            std::cerr << "Ошибка: час должен быть от 00 до 23!\n";
            continue;
        }
        if (mininutes < 0 || mininutes > 59) {
            std::cerr << "Ошибка: минуты должны быть от 00 до 59!\n";
            continue;
        }
    return time;
    }
   }

template<typename T>
T getInputInRange(const std::string& prompt, T min, T max) {
    T value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail() || value < min || value > max) {
            std::cin.clear();
           // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Ошибка: введите значение от " << min << " до " << max << "\n";
        }
        else {
            return value;
        }
    }
}

std::string inputZone() {
    const std::vector<std::string> zones = { "parter", "balcony", "beletage" };
    std::string zone;

    while (true) {
        std::cout << "Введите зону (parter/balcony/beletage): ";
        std::cin >> zone;

        if (std::find(zones.begin(), zones.end(), zone) == zones.end()) {
            std::cerr << "Ошибка: допустимые значения: parter, balcony, beletage\n";
        }
        else {
            return zone;
        }
    }
}

// Вспомогательные функции
Ticket inputTicket(TicketManager& ticketManager) {
    Ticket ticket;
    ticket.id = ticketManager.generateNextId();
    std::cout << "Автоматически сгенерирован ID: " << ticket.id << "\n";

    ticket.date = inputDate();
    ticket.time = inputTime();
    std::cout << "Введите название представления: ";
    std::cin.ignore();
    std::getline(std::cin, ticket.performance);
    ticket.hallNumber = getInputInRange("Введите номер зала (1-10): ", 1, 10);
    ticket.zone = inputZone();
    ticket.seatNumber = getInputInRange("Введите номер места (1-100): ", 1, 100);
    ticket.ageLimit = getInputInRange("Введите возрастное ограничение (0-18): ", 0, 18);
    ticket.price = getInputInRange("Введите стоимость билета: ", 0.0, 10000.0);
    ticket.saleDate = inputSaleDate();

    return ticket;
}

void printTickets(const std::vector<Ticket>& tickets) {
    std::string m1 = "+=======================================+";
    std::string m2 = "+---------------------------------------+";
    int l1 = 19+4;
    //std::cout << "\n";
    std::cout << m1 << std::endl;
    std::cout << "Список билетов:\n";
    std::cout << m1 << std::endl;
    // Определяем длину самого длинного поля
    const int max_field_length = 13; // "Представление" - 13 символов
    bool isFirstTicket = true;


    for (const auto& ticket : tickets) {

        if (!isFirstTicket)
        {
            std::cout << m2 << std::endl;  // разделитель между билетами
        }
        isFirstTicket = false;
        std::cout << std::left <<"|Билет ID " << std::left << std::setw(30) << ticket.id << "|\n";

        std::cout << "|Дата"; std::cout << std::setw(max_field_length - 4 + 3); std::cout << ": " << std::left << std::setw(l1) << ticket.date << "|\n";
        std::cout << "|Время"; std::cout << std::setw(max_field_length - 5 + 3); std::cout << ": " << std::left << std::setw(l1) << ticket.time << "|\n";
        std::cout << "|Представление"; std::cout << std::setw(max_field_length - 13 + 3); std::cout << ": " << std::left << std::setw(l1) << ticket.performance << "|\n";
        std::cout << "|Зал"; std::cout << std::setw(max_field_length - 3 + 3); std::cout << ": " << std::left << std::setw(l1) << ticket.hallNumber << "|\n";
        std::cout << "|Зона"; std::cout << std::setw(max_field_length - 4 + 3); std::cout << ": " << std::left << std::setw(l1) << ticket.zone << "|\n";
        std::cout << "|Место"; std::cout << std::setw(max_field_length - 5 + 3); std::cout << ": " << std::left << std::setw(l1) << ticket.seatNumber << "|\n";
        std::cout << "|Ограничение"; std::cout << std::setw(max_field_length - 11 + 3); std::cout << ": " << std::left << std::setw(l1) << (std::to_string(ticket.ageLimit) + "+") << "|\n";
        std::cout << "|Дата продажи"; std::cout << std::setw(max_field_length - 11 + 2); std::cout << ": " << std::left << std::setw(l1) << (ticket.saleDate.empty() ? "Free" : ticket.saleDate) << "|\n";        std::cout << "|Цена"; std::cout << std::setw(max_field_length - 4 + 3); std::cout << ": " << std::left << std::setw(l1) << ticket.price << "|\n";

    }
    std::cout << m1 << std::endl;
}

void printUsers(const std::vector<User>& users) {
                  
    std::string m1 = "+==============+=============+=============+";
    std::string m2 = "+--------------+-------------+-------------+";
    bool isFirstUser = true;
    std::string adminStatus;
    int var;

    std::cout << "\nСписок пользователей\n";
    std::cout << m1 << std::endl;
    std::cout << std::left << std::setw(20) << "|Логин" << std::setw(20) << "|Пароль"
        << std::setw(15) << "|Администратор|\n";
    std::cout << m1 << std::endl;
    for (const auto& user : users) {
        if (!isFirstUser)
        {
            std::cout << m2 << std::endl;
        }
        isFirstUser = false;

        if (user.isAdmin)
        {
            adminStatus = "Да";
            var = 15;
        }
        else
        {
            adminStatus = "Нет";
            var = 16;
        }

        std::cout  << "|" << std::left << std::setw(14) <<  user.login << "|" << std::setw(13) <<std::left<< user.password
            << "|" << std::left << std::setw(var) << adminStatus << "|" << "\n";

        
    }
    std::cout << m1 << std::endl;
}
// ticket_system.cpp (только измененные функции)

void showTicketMenu(TicketManager& ticketManager) {
    int choice;
    bool back = false;
    std::string m1 = "+===============================================+";
    std::string m2 = "+-----------------------------------------------+";
    int var = 63;

    while (!back) {
        std::cout << "\n";

        std::cout << m1 << std::endl;
        std::cout << std::setw(var + 3) << std::left << "|Управление билетами" << std::right << "|" << std::endl;
        std::cout << m1 << std::endl;
        std::cout << std::setw(var + 5) << std::left << "|1. Просмотреть все билеты" << std::right << "|" << std::endl;
        std::cout << m2 << std::endl;
        std::cout << std::setw(var - 2) << std::left << "|2. Добавить билет" << std::right << "|" << std::endl;
        std::cout << m2 << std::endl;
        std::cout << std::setw(var + 3) << std::left << "|3. Редактировать билет" << std::right << "|" << std::endl;
        std::cout << m2 << std::endl;
        std::cout << std::setw(var - 3) << std::left << "|4. Удалить билет" << std::right << "|" << std::endl;
        std::cout << m2 << std::endl;
        std::cout << std::setw(var + 2) << std::left << "|5. Фильтровать билеты" << std::right << "|" << std::endl;
        std::cout << m2 << std::endl;
        std::cout << std::setw(var + 11) << std::left << "|6. Просмотреть свободные билеты" << std::right << "|" << std::endl;
        std::cout << m2 << std::endl;
        std::cout << std::setw(var + 3) << std::left << "|7. Подсчитать свободные билеты по представлению" << std::right << "|" << std::endl;
        std::cout << m2 << std::endl;
        std::cout << std::setw(var + 12) << std::left << "|8. Установить дату продажи билета" << std::right << "|" << std::endl;
        std::cout << m2 << std::endl;
        std::cout << std::setw(var - 10) << std::left << "|9. Назад" << std::right << "|" << std::endl;
        std::cout << m1 << std::endl;


        std::cout << "> ";
        int choice;
        choice = inputDigit();

        system("cls||clear"); // Очистка терминала

        switch (choice) {
        case 1: {
            auto tickets = ticketManager.getAllTickets();
            printTicketsWithCheck(tickets); 
            waitForAnyKeyAndClear();
            break;
        }
        case 2: {
            Ticket ticket = inputTicket(ticketManager);
            ticketManager.addTicket(ticket);
            break;
        }
        case 3: {
            int id;
            std::cout << "Введите ID билета для редактирования: ";
            std::cin >> id;
            Ticket ticket = inputTicket(ticketManager);
            ticketManager.editTicket(id, ticket);
            break;
        }
        case 4: {
            int id;
            std::cout << "Введите ID билета для удаления: ";
            std::cin >> id;
            ticketManager.removeTicket(id);
            break;
        }
        case 5: {
            std::string field, value;
            std::cout << "Введите поле для фильтрации (date/performance/zone): ";
            std::cin >> field;

            if (field == "zone") {
                value = inputZone(); // Используем существующую проверку зоны
            }
            else {
                std::cout << "Введите значение: ";
                std::cin >> value;
            }

            auto tickets = ticketManager.filterTickets(field, value);
            if (tickets.empty()) {
                std::cout << "\n+=======================================+\n";
                std::cout << "|      Билеты не найдены               |\n";
                std::cout << "+=======================================+\n";
            }
            else {
                printTickets(tickets);
            }
            waitForAnyKeyAndClear();
            break;

        }
        case 6: {
            auto tickets = ticketManager.getAvailableTickets();
            printTicketsWithCheck(tickets);
            waitForAnyKeyAndClear();
            break;
        }
        case 7: {
            std::string performance;
            std::cout << "Введите название представления: ";
            
            std::getline(std::cin, performance);
            int count = ticketManager.countAvailableTickets(performance);
            std::cout << "Количество свободных билетов на '" << performance << "': " << count << "\n";
            break;
        }
        case 8: {
            int id;
            std::cout << "Введите ID билета: ";
            std::cin >> id;
            std::string saleDate = inputSaleDate();
            ticketManager.setTicketSaleDate(id, saleDate);
            break;
        }
        case 9:
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
    std::string m1 = "+=================================+";
    std::string m2 = "+---------------------------------+";
    int var = 43;

    while (!back) {
        std::cout << std::endl;
        std::cout << m1 << std::endl;
        std::cout << std::setw(var + 15) << std::left << "|Управление пользователями" << std::right << "|" << std::endl;
        std::cout << m1 << std::endl;
        std::cout << std::setw(var + 3) << std::left << "|1. Просмотреть всех пользователей" << std::right << "|" << std::endl;
        std::cout << m2 << std::endl;
        std::cout << std::setw(var + 11) << std::left << "|2. Добавить пользователя" << std::right << "|" << std::endl;
        std::cout << m2 << std::endl;
        std::cout << std::setw(var + 16) << std::left << "|3. Редактировать пользователя" << std::right << "|" << std::endl;
        std::cout << m2 << std::endl;
        std::cout << std::setw(var + 10) << std::left << "|4. Удалить пользователя" << std::right << "|" << std::endl;
        std::cout << m2 << std::endl;
        std::cout << std::setw(var - 4) << std::left << "|5. Назад" << std::right << "|" << std::endl;
        std::cout << m1 << std::endl;

        std::cout << "> ";
        int choice;
        choice = inputDigit();

        system("cls||clear"); // Очистка терминала

        switch (choice) {
        case 1: {
            auto users = userManager.getAllUsers();
            printUsers(users);
            waitForAnyKeyAndClear();
            break;
        }
        case 2: {
            std::string login, password;
            bool isAdmin;
            std::cout << "Введите логин: ";
            std::cin >> login;

            if (userManager.userExists(login)) {
                std::cout << "Ошибка: пользователь с таким логином уже существует!\n";
                waitForAnyKeyAndClear();
                break;
            }

            std::cout << "Введите пароль: ";
            std::cin >> password;
            std::cout << "Администратор? (1 - да, 0 - нет): ";
            std::cin >> isAdmin;
            userManager.addUser(login, password, isAdmin);
            std::cout << "Пользователь добавлен!\n";
            waitForAnyKeyAndClear();
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
            waitForAnyKeyAndClear();
            break;
        }
        case 4: {
            std::string login;
            std::cout << "Введите логин для удаления: ";
            std::cin >> login;
            userManager.removeUser(login);
            std::cout << "Пользователь удален!\n";
            waitForAnyKeyAndClear();
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
    std::string m1 = "+============================+";
    std::string m2 = "+----------------------------+";
    int var = 44;

    while (!back) {
        std::cout << m1 << std::endl;
        std::cout << std::setw(var + 3) << std::left << "|Меню администратора" << std::right << "|" << std::endl;
        std::cout << m1 << std::endl;
        std::cout << std::setw(var + 3) << std::left << "|1. Управление билетами" << std::right << "|" << std::endl;
        std::cout << m2 << std::endl;
        std::cout << std::setw(var) << std::left << "|2. Управление пользователями" << std::right << "|" << std::endl;
        std::cout << m2 << std::endl;
        std::cout << std::setw(var - 10) << std::left << "|3. Выход" << std::right << "|" << std::endl;
        std::cout << m1 << std::endl;

        std::cout << "> ";
        int choice;
        choice = inputDigit();

        system("cls||clear"); // Очистка терминала

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
        std::string m1 = "+==================================+";
        std::string m2 = "+----------------------------------+";
        int var = 50;

        std::cout << m1 << std::endl;
        std::cout << std::setw(var + 1) << std::left << "|Меню пользователя" << std::right << "|" << std::endl;
        std::cout << m1 << std::endl;
        std::cout << std::setw(var + 5) << std::left << "|1. Просмотреть все билеты" << std::right << "|" << std::endl;
        std::cout << m2 << std::endl;
        std::cout << std::setw(var - 3) << std::left << "|2. Поиск билетов" << std::right << "|" << std::endl;
        std::cout << m2 << std::endl;
        std::cout << std::setw(var - 10) << std::left << "|3. Выход" << std::right << "|" << std::endl;
        std::cout << m1 << std::endl;

        std::cout << "> ";
        int choice;
        choice = inputDigit();

        system("cls||clear"); // Очистка терминала

        switch (choice) {
        case 1: {
            auto tickets = ticketManager.getAllTickets();
            printTickets(tickets);
            waitForAnyKeyAndClear();
            break;
        }
        case 2: {
            std::string field, value;
            std::cout << "Введите поле для поиска (date/performance/zone): ";
            std::cin >> field;

            if (field == "zone") {
                value = inputZone(); // Используем существующую проверку зоны
            }
            else {
                std::cout << "Введите значение: ";
                std::cin >> value;
            }

            auto tickets = ticketManager.filterTickets(field, value);
            if (tickets.empty()) {
                std::cout << "\n+=======================================+\n";
                std::cout << "|      Билеты не найдены               |\n";
                std::cout << "+=======================================+\n";
            }
            else {
                printTickets(tickets);
            }
            waitForAnyKeyAndClear();
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

