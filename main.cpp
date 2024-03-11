#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
using namespace std;
ifstream f("CARD");
ofstream g("History");
double transfer(double balance, double amount) {
    if (amount > balance) {
        cout << "Insufficient funds!\n";
        return balance;
    } else {
        balance = balance - amount;
        cout << "Transfer successful!\n";
        return balance;
    }
}
double payBill(double balance, double amount) {
    if (amount > balance) {
        cout << "Insufficient funds!\n";
        return balance;
    } else {

        balance = balance - amount;
        cout << "Bill paid successfully!\n";
        return balance;
    }
}
void personalizedGreeting() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int hour = ltm->tm_hour;
    if (hour < 12)
        cout << "Good morning!\n";
    else if (hour < 18)
        cout << "Good afternoon!\n";
    else
        cout << "Good evening!\n";
}
int main() {
    personalizedGreeting();
    system("echo Insert card");
    int max=4;
    while(max)
    {
        double balance;
        string response;
        int option;
        int PIN1, newPIN, PIN2;
        cout << "Enter PIN: \n _ _ _ _ \n";
        cin >> PIN1;
        f >> PIN2;
        f >> balance;
        if (PIN1 == PIN2) {
            cout << "Welcome! \n";
            while (true) {
                ofstream h("CARD");
                h<<PIN2<<"\n"<<balance;
                cout << "\n  Choose the service you want: \n";
                cout << "1. Check balance \n";
                cout << "2. Deposit \n";
                cout << "3. Withdraw \n";
                cout << "4. Change PIN \n";
                cout << "5. Transfer \n";
                cout << "6. Pay a bill \n";
                cout << "7. Exit \n";
                cin >> option;
                switch (option) {
                    double amount1, amount2, amount3, amount4;
                    case 1:
                        cout <<"Your current balance is "<< balance <<"$"<< "\n";
                        break;
                    case 2:
                        cout << "Enter the amount you want to deposit: \n";
                        cin >> amount1;
                        balance = balance + amount1;
                        cout << "Transaction successful! \n";
                        g<<"Deposited: "<< amount1 <<"\n";
                        break;
                    case 3:
                        cout << "Minimum 25 USD        COMMISSION 3.5% \n";
                        cout << "Enter the amount you want to withdraw: \n";
                        cin >> amount2;
                        if (amount2 < 25) {
                            cout << "Minimum 25 USD \n";
                            break;
                        } else if (amount2 > balance)
                            cout << "Insufficient funds!\n";
                        else
                        {
                            balance = balance - amount2 - amount2 * 3.5 / 100;
                            cout << "Withdrawal successful!\n";
                            g << "Withdrawal: "<< amount2 <<"\n";
                            break;
                        }
                        break;
                    case 4:
                        cout << "Are you sure? \n";
                        cin >> response;
                        for (char & c : response) c = toupper(c);
                        if (response == "YES") {
                            cout << "Enter the new PIN \n";
                            cin >> newPIN;
                            int k = 0, x = newPIN;
                            while (x) {
                                x = x / 10;
                                k++;
                            }
                            if (k == 4) {
                                g<<"PIN changed from " << PIN2 <<" to " << newPIN <<"\n";
                                PIN2 = newPIN;
                                cout << "PIN changed successfully! \n New PIN is " << PIN2;
                                break;
                            } else {
                                cout << "The PIN needs to contain 4 characters!";
                                break;
                            }
                        } else
                            break;
                    case 5:
                        char IBAN[100];
                        cout << "Enter the beneficiaries IBAN \n";
                        cin >> IBAN;
                        cout << "Enter the amount you want to transfer: \n";
                        cin >> amount3;
                        balance = transfer(balance, amount3);
                        g<<"Transfer made to: "<< IBAN << " money transferred: " << amount3 <<"\n";

                        break;
                    case 6:
                        char FIRM[100];
                        cout << "Enter the name of the FIRM \n";
                        cin >> FIRM;
                        cout << "Enter the amount you want to pay: \n";
                        cin >> amount4;
                        balance = payBill(balance, amount4);
                        g << "Bill payed to: " << FIRM << " money transferred: "<< amount4<<"\n";
                        break;
                    case 7:
                        cout << "Goodbye!";
                        return 0;
                }
            }
        }
        else
        {
            cout << "Incorrect PIN!\n You have " << max-1 << " attempts remaining \n";
            max--;
        }
    }
    cout << "CARD BLOCKED";
    return 0;
}