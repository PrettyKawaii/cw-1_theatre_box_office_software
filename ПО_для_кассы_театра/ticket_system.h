#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cstdlib> 

// Структура для хранения данных о билете
struct Ticket {
    int id;
    std::string date;
    std::string time;
    std::string performance;
    int hallNumber;
    std::string zone;
    int seatNumber;
    int ageLimit;
    std::string saleDate;
    double price;
};

// Структура для хранения данных о пользователе
struct User {
    std::string login;
    std::string password;
    bool isAdmin;
};

// Класс для работы с билетами
class TicketManager {
private:
    std::vector<Ticket> tickets;
    std::string dataFile;

public:
    TicketManager(const std::string& filename);
    ~TicketManager();

    

    std::vector<Ticket> getAvailableTickets() const;
    int countAvailableTickets(const std::string& performance) const;

    // Возвращает итератор на билет с указанным ID (или tickets.end(), если не найден)
    std::vector<Ticket>::iterator findTicket(int id);
    std::vector<Ticket>::const_iterator findTicket(int id) const; // const-версия
    void loadTickets();
    void saveTickets();
    int generateNextId();
    void addTicket(const Ticket& ticket);
    void editTicket(int id, const Ticket& newTicket);
    void removeTicket(int id);
    void setTicketSaleDate(int id, const std::string& saleDate);

    std::vector<Ticket> getAllTickets() const;
    std::vector<Ticket> filterTickets(const std::string& field, const std::string& value) const;


};

// Класс для работы с пользователями
class UserManager {
private:
    std::vector<User> users;
    std::string userFile;

public:
    UserManager(const std::string& filename);
    ~UserManager();

    void loadUsers();
    void saveUsers();
    bool authenticate(const std::string& login, const std::string& password, bool& isAdmin);
    void addUser(const std::string& login, const std::string& password, bool isAdmin);
    void editUser(const std::string& login, const std::string& newPassword, bool newIsAdmin);
    void removeUser(const std::string& login);
    bool userExists(const std::string& login) const;
    std::vector<User> getAllUsers() const;
};

// Прототипы вспомогательных функций
Ticket inputTicket(TicketManager& ticketManager); 
void printTickets(const std::vector<Ticket>& tickets);
void printUsers(const std::vector<User>& users);
void showAdminMenu(TicketManager& ticketManager, UserManager& userManager);
void showUserMenu(TicketManager& ticketManager);
void showTicketMenu(TicketManager& ticketManager);
