//#include "TicketDisplay.h"
//#include "TicketSystem.h" // Ваш основной заголовочный файл
//
//using namespace std;
//
//void TicketDisplay::ClearScreen() {
//#ifdef _WIN32
//    system("cls");
//#else
//    system("clear");
//#endif
//}
//
//void TicketDisplay::WaitForInput() {
//    cout << "\nНажмите Enter для продолжения...";
//    cin.ignore();
//    cin.get();
//    ClearScreen();
//}
//
//void TicketDisplay::PrintHorizontalLine(char symbol) {
//    cout << "+" << string(WIDTH, symbol) << "+" << endl;
//}
//
//void TicketDisplay::PrintHeader(const string& title) {
//    PrintHorizontalLine();
//    int padding = (WIDTH - title.length()) / 2;
//    cout << "|" << setw(padding + title.length()) << right << title
//        << setw(WIDTH - padding - title.length() + 1) << "|" << endl;
//    PrintHorizontalLine();
//}
//
//void TicketDisplay::ShowMainMenu() {
//    ClearScreen();
//    PrintHeader("КАССА ТЕАТРА");
//
//    const string options[] = {
//        "Вход как администратор",
//        "Вход как пользователь",
//        "Выход"
//    };
//
//    for (int i = 0; i < 3; i++) {
//        cout << "| " << left << setw(3) << to_string(i + 1) + "."
//            << setw(WIDTH - 5) << options[i] << " |" << endl;
//        PrintHorizontalLine('-');
//    }
//    cout << "| " << left << setw(3) << "0."
//        << setw(WIDTH - 5) << "Выход" << " |" << endl;
//    PrintHorizontalLine();
//
//    cout << "Ваш выбор: ";
//}
//
//void TicketDisplay::ShowAdminMenu() {
//    PrintHeader("МЕНЮ АДМИНИСТРАТОРА");
//
//    const string options[] = {
//        "Управление билетами",
//        "Управление пользователями",
//        "Просмотр статистики",
//        "Выход в главное меню"
//    };
//
//    for (int i = 0; i < 4; i++) {
//        cout << "| " << left << setw(3) << to_string(i + 1) + "."
//            << setw(WIDTH - 5) << options[i] << " |" << endl;
//        PrintHorizontalLine('-');
//    }
//    cout << "Ваш выбор: ";
//}
//
//void TicketDisplay::ShowTicket(const Ticket& ticket) {
//    PrintHeader("ИНФОРМАЦИЯ О БИЛЕТЕ");
//
//    auto printRow = [](const string& label, const string& value) {
//        cout << "| " << left << setw(COL1_WIDTH) << label
//            << "| " << setw(COL2_WIDTH) << value << " |" << endl;
//        };
//
//    printRow("ID билета:", to_string(ticket.id));
//    printRow("Представление:", ticket.performance);
//    printRow("Дата:", ticket.date);
//    printRow("Время:", ticket.time);
//    printRow("Зал:", to_string(ticket.hallNumber));
//    printRow("Зона:", ticket.zone);
//    printRow("Место:", to_string(ticket.seatNumber));
//    printRow("Возрастное ограничение:", to_string(ticket.ageLimit));
//
//    PrintHorizontalLine();
//}
//
//void TicketDisplay::ShowTicketList(const vector<Ticket>& tickets) {
//    PrintHeader("СПИСОК БИЛЕТОВ");
//
//    // Шапка таблицы
//    cout << "| " << left << setw(8) << "ID"
//        << "| " << setw(20) << "Представление"
//        << "| " << setw(12) << "Дата"
//        << "| " << setw(8) << "Зал"
//        << "| " << setw(10) << "Место" << " |" << endl;
//    PrintHorizontalLine('-');
//
//    // Данные
//    for (const auto& ticket : tickets) {
//        cout << "| " << setw(8) << ticket.id
//            << "| " << setw(20) << (ticket.performance.length() > 18 ?
//                ticket.performance.substr(0, 15) + "..." : ticket.performance)
//            << "| " << setw(12) << ticket.date
//            << "| " << setw(8) << ticket.hallNumber
//            << "| " << setw(10) << ticket.zone + "-" + to_string(ticket.seatNumber) << " |" << endl;
//    }
//
//    PrintHorizontalLine();
//    cout << "Всего билетов: " << tickets.size() << endl;
//}
//
//void TicketDisplay::ShowMessage(const string& message, bool isError) {
//    PrintHorizontalLine('*');
//    cout << (isError ? " ОШИБКА: " : " ") << message << endl;
//    PrintHorizontalLine('*');
//    WaitForInput();
//}