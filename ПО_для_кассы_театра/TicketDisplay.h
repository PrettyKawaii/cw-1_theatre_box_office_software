//#ifndef TICKET_DISPLAY_H
//#define TICKET_DISPLAY_H
//
//#include <iostream>
//#include <iomanip>
//#include <string>
//#include <vector>
//
//class TicketDisplay {
//public:
//    // Константы оформления
//    static const int WIDTH = 70;
//    static const int COL1_WIDTH = 20;
//    static const int COL2_WIDTH = WIDTH - COL1_WIDTH - 3; // -3 для границ
//
//    // Основные элементы интерфейса
//    static void ShowMainMenu();
//    static void ShowAdminMenu();
//    static void ShowUserMenu();
//    static void ShowLoginForm(bool isAdmin);
//    static void ShowAuthStatus(bool isAdmin);
//
//    // Работа с билетами
//    static void ShowTicket(const Ticket& ticket);
//    static void ShowTicketList(const std::vector<Ticket>& tickets);
//    static void ShowTicketForm(const std::string& action);
//
//    // Работа с пользователями
//    static void ShowUserList(const std::vector<User>& users);
//
//    // Вспомогательные методы
//    static void ShowMessage(const std::string& message, bool isError = false);
//    static void ClearScreen();
//    static void WaitForInput();
//
//private:
//    static void PrintHeader(const std::string& title);
//    static void PrintHorizontalLine(char symbol = '=');
//};
//
//#endif // TICKET_DISPLAY_H