#include "ticket_system.h"
#include "TicketDisplay.h"

static void showAdminMenu(TicketManager& tm, UserManager& um) {
    bool back = false;
    while (!back) {
        TicketDisplay::ClearScreen();
        TicketDisplay::ShowAdminMenu();

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1: {
            auto tickets = tm.getAllTickets();
            TicketDisplay::ShowTicketList(tickets);
            TicketDisplay::WaitForInput();
            break;
        }
        case 2: {
            auto users = um.getAllUsers();
            TicketDisplay::ShowUserList(users);
            TicketDisplay::WaitForInput();
            break;
        }
        case 3: back = true; break;
        default: TicketDisplay::ShowMessage("Неверный выбор!", true);
        }
    }
}

static void showUserMenu(TicketManager& tm) {
    bool back = false;
    while (!back) {
        TicketDisplay::ClearScreen();
        TicketDisplay::ShowUserMenu();

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1: {
            auto tickets = tm.getAllTickets();
            TicketDisplay::ShowTicketList(tickets);
            TicketDisplay::WaitForInput();
            break;
        }
        case 2: back = true; break;
        default: TicketDisplay::ShowMessage("Неверный выбор!", true);
        }
    }
}