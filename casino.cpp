#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

class Customer
{
public:
       char name[20];
       int deposit;
       int referenceNumber;

       void newDeposit(int amount)
       {
              deposit += amount;
              cout << "Your total balance is: " << deposit << endl;
       }

       void modify(int randomNumber, int playerNumber)
       {
              if (randomNumber != playerNumber)
              {
                     deposit -= 100;
                     cout << "Your current balance is " << deposit << endl;
              }
              else
              {
                     deposit += 50;
                     cout << "Your current balance is " << deposit << endl;
              }
       }

       int getReferenceNumber() const
       {
              return referenceNumber;
       }

       void createAccount()
       {
              cout << "Enter your name: ";
              cin.ignore();
              cin.getline(name, 20);
              srand(time(0));
              referenceNumber = rand() % 1000;
              cout << "Your reference number is: " << referenceNumber << endl;
              cout << "PLEASE REMEMBER IT." << endl;
              do
              {
                     cout << "Please enter your initial deposit amount (>= 1000): ";
                     cin >> deposit;
              } while (deposit < 1000);
              cout << "Account created successfully." << endl;
       }
};

void depositMoney(int amount)
{
       int refNo;
       bool found = false;
       Customer customer;
       fstream file;
       file.open("customer.txt", ios::binary | ios::in | ios::out);
       cout << "Enter your reference number: ";
       cin >> refNo;
       while (!file.eof() && !found)
       {
              file.read(reinterpret_cast<char *>(&customer), sizeof(Customer));
              if (customer.getReferenceNumber() == refNo)
              {
                     customer.newDeposit(amount);
                     file.seekp(-sizeof(Customer), ios::cur);
                     file.write(reinterpret_cast<char *>(&customer), sizeof(Customer));
                     found = true;
              }
       }
       file.close();
}

void playGame()
{
       Customer customer;
       bool found = false;
       fstream file;
       file.open("customer.txt", ios::binary | ios::in | ios::out);
       int refNo;
       cout << "Enter your reference number: ";
       cin >> refNo;
       while (!file.eof() && !found)
       {
              file.read(reinterpret_cast<char *>(&customer), sizeof(Customer));
              if (customer.getReferenceNumber() == refNo)
              {
                     int playerNumber;
                     cout << "Enter any number between 0-10: ";
                     cin >> playerNumber;
                     srand(time(0));
                     int randomNumber = rand() % 10;
                     cout << "Computer generated number is: " << randomNumber << endl;
                     customer.modify(randomNumber, playerNumber);
                     char choice;
                     cout << "Would you like to play another round (Y/N): ";
                     cin >> choice;
                     choice = toupper(choice);
                     if (choice == 'Y')
                            playGame();
                     else
                            cout << "Thank you for playing." << endl;
                     found = true;
              }
       }
       file.close();
}

void displayWelcomeMessage()
{
       cout << "\n\n\n\tWelcome to our casino!!!" << endl;
       cout << "\nHere, for every wrong guess you will be penalized with Rs. 100." << endl;
       cout << "But for every right guess, you get Rs. 50. So, best of luck." << endl;
       system("pause");
}

void writeAccount()
{
       Customer customer;
       ofstream outFile("customer.txt", ios::binary | ios::app);
       customer.createAccount();
       outFile.write(reinterpret_cast<char *>(&customer), sizeof(Customer));
       outFile.close();
}

int main()
{
       displayWelcomeMessage();
       system("cls");
       int choice;
       do
       {
              cout << "\n\n1. Create an account\n2. Deposit money\n3. PLAY!!!\n4. Quit" << endl;
              cout << "\nPlease select your choice: ";
              cin >> choice;
              system("cls");
              switch (choice)
              {
              case 1:
                     writeAccount();
                     break;
              case 2:
                     int amount;
                     cout << "Enter the amount: ";
                     cin >> amount;
                     depositMoney(amount);
                     break;
              case 3:
                     playGame();
                     break;
              case 4:
                     cout << "Thank you for your time." << endl;
                     break;
              default:
                     cout << "Please enter a valid option." << endl;
                     continue;
              }
              cin.ignore();
              cin.get();
              system("cls");
       } while (choice != 4);
       return 0;
}
