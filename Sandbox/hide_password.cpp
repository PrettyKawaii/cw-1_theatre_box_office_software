#include<iostream>
#include<conio.h>
using namespace std;
int main() {
    char pin[100];
    int k = 0;
    cout << "Enter  password : ";
    while (pin[k - 1] != '\r') {
        pin[k] = _getch();
        if ((pin[k - 1] != 127 || pin[k - 1] != 8))
        {
            if (pin[k - 1] != '\r') {
                cout << "*";
            }
            k++;
        }
        else
        {
            std::cout << "Yess!";
            std::cout << "\b \b";
            k--;
        }
        
    }
    pin[k - 1] = '\0';
    cout << "\nYou entered : " << pin << endl;
}

/*
#include <stdio.h>
#include <conio.h>

int main() {
    // Set op = {0, 0, 0, 0, 0, 0} = '\0\0\0\0\0\0' string
    char op[6] = {0};
    for (int i=0; i<5; i++) {
        op[i] = getch();
    }
    printf("Received 5 character Input: %s\n", op);
    return 0;
}
*/