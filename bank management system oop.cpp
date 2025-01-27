#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Customer {
private:
    int CustomerID;
    string Name;
    string PhoneNumber;
    string Address;

public:
    void addCustomer() {
        cout << "Enter Customer ID: ";
        cin >> CustomerID;
        cin.ignore();

        cout << "Enter Customer Name: ";
        getline(cin, Name);

        cout << "Enter Phone Number: ";
        getline(cin, PhoneNumber);

        cout << "Enter Address: ";
        getline(cin, Address);

        ofstream outFile("customers.txt", ios::app);
        if (outFile.is_open()) {
            outFile << CustomerID << "," << Name << "," << PhoneNumber << "," << Address << endl;
            outFile.close();
            cout << "Customer added successfully!\n";
        } else {
            cout << "Error: Could not open file.\n";
        }
    }

    void displayCustomerDetails(int searchID) 
    {
        bool found = false;
        ifstream inFile("customers.txt");

        if (inFile.is_open()) 
        {
            string line;
            while (getline(inFile, line)) 
            {
                int id;
                string name, phone, address;

                size_t pos1 = line.find(",");
                size_t pos2 = line.find(",", pos1 + 1);
                size_t pos3 = line.find(",", pos2 + 1);

                id = stoi(line.substr(0, pos1));
                name = line.substr(pos1 + 1, pos2 - pos1 - 1);
                phone = line.substr(pos2 + 1, pos3 - pos2 - 1);
                address = line.substr(pos3 + 1);

                if (id == searchID) 
                {
                    found = true;
                    cout << "\nCustomer Details:\n";
                    cout << "ID: " << id << "\n";
                    cout << "Name: " << name << "\n";
                    cout << "Phone: " << phone << "\n";
                    cout << "Address: " << address << "\n";
                    break;
                }
            }
            inFile.close();

            if (!found) 
            {
                cout << "Customer with ID " << searchID << " not found.\n";
            }
        }
        else
        {
            cout << "Error: Could not open file.\n";
        }
    }

    void updateCustomerInfo(int updateID)
    {
        bool found = false;
        ifstream inFile("customers.txt");
        ofstream tempFile("temp.txt");

        if (inFile.is_open() && tempFile.is_open()) 
        {
            string line;
            while (getline(inFile, line))
            {
                int id;
                string name, phone, address;

                size_t pos1 = line.find(",");
                size_t pos2 = line.find(",", pos1 + 1);
                size_t pos3 = line.find(",", pos2 + 1);

                id = stoi(line.substr(0, pos1));
                name = line.substr(pos1 + 1, pos2 - pos1 - 1);
                phone = line.substr(pos2 + 1, pos3 - pos2 - 1);
                address = line.substr(pos3 + 1);

                if (id == updateID) 
                {
                    found = true;
                    cout << "Enter new Name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter new Phone Number: ";
                    getline(cin, phone);
                    cout << "Enter new Address: ";
                    getline(cin, address);
                }

                tempFile << id << "," << name << "," << phone << "," << address << endl;
            }

            inFile.close();
            tempFile.close();

            if (found)
            {
                remove("customers.txt");
                rename("temp.txt", "customers.txt");
                cout << "Customer information updated successfully!\n";
            } 
            else
            {
                remove("temp.txt");
                cout << "Customer with ID " << updateID << " not found.\n";
            }
        } 
        else 
        {
            cout << "Error: Could not open file.\n";
        }
    }
};

class Account
{
private:
    int AccountNumber;
    float Balance;
    string AccountType;
    float InterestRate;

public:
    Account(int accountNumber, float balance, string accountType, float interestRate) 
    {
        AccountNumber = accountNumber;
        Balance = balance;
        AccountType = accountType;
        InterestRate = interestRate;
    }

    void deposit(float amount) 
    {
        if (amount > 0) 
        {
            Balance += amount;
            cout << "Deposited: " << amount << "\n";
            cout << "New Balance: " << Balance << "\n";
        }
        else 
        {
            cout << "Deposit amount must be positive.\n";
        }
    }

    void withdraw(float amount)
    {
        if (amount > 0 && amount <= Balance) 
        {
            Balance -= amount;
            cout << "Withdrew: " << amount << "\n";
            cout << "New Balance: " << Balance << "\n";
        }
        else 
        {
            cout << "Insufficient balance or invalid withdrawal amount.\n";
        }
    }

    void calculateInterest() 
    {
        float interest = (Balance * InterestRate) / 100;
        cout << "Interest Earned: " << interest << "\n";
        Balance += interest; 
        cout << "New Balance after Interest: " << Balance << "\n";
    }

    void displayAccountDetails() 
    {
        cout << "\nAccount Details:\n";
        cout << "Account Number: " << AccountNumber << "\n";
        cout << "Account Type: " << AccountType << "\n";
        cout << "Balance: " << Balance << "\n";
        cout << "Interest Rate: " << InterestRate << "%\n";
    }

    void saveAccountToFile() 
    {
        ofstream outFile("accounts.txt", ios::app);
        if (outFile.is_open()) 
        {
            outFile << AccountNumber << "," << Balance << "," << AccountType << "," << InterestRate << endl;
            outFile.close();
            cout << "Account details saved successfully!\n";
        } 
        else 
        {
            cout << "Error: Could not open file to save account details.\n";
        }
    }

    static void loadAccountsFromFile()
    {
        ifstream inFile("accounts.txt");
        if (inFile.is_open()) 
        {
            string line;
            while (getline(inFile, line)) 
            {
                int accountNumber;
                float balance, interestRate;
                string accountType;

                size_t pos1 = line.find(",");
                size_t pos2 = line.find(",", pos1 + 1);
                size_t pos3 = line.find(",", pos2 + 1);

                accountNumber = stoi(line.substr(0, pos1));
                balance = stof(line.substr(pos1 + 1, pos2 - pos1 - 1));
                accountType = line.substr(pos2 + 1, pos3 - pos2 - 1);
                interestRate = stof(line.substr(pos3 + 1));

                cout << "\nAccount Number: " << accountNumber << endl;
                cout << "Balance: " << balance << endl;
                cout << "Account Type: " << accountType << endl;
                cout << "Interest Rate: " << interestRate << "%" << endl;
            }
            inFile.close();
        }
        else 
        {
            cout << "Error: Could not open file to load account details.\n";
        }
    }
};

class Admin 
{
private:
    string AdminID;
    string Password;

public:
    Admin(string adminID, string password)
    {
        AdminID = adminID;
        Password = password;
    }

    bool authenticateAdmin(string id, string password)
    {
        if (id == AdminID && password == Password) 
        {
            cout << "Admin authenticated successfully.\n";
            return true;
        } 
        else 
        {
            cout << "Invalid Admin ID or Password.\n";
            return false;
        }
    }

    void viewAllAccounts() 
    {
        ifstream inFile("accounts.txt");
        if (inFile.is_open()) 
        {
            string line;
            cout << "\nViewing All Accounts:\n";
            while (getline(inFile, line)) 
            {
                int accountNumber;
                float balance, interestRate;
                string accountType;

                size_t pos1 = line.find(",");
                size_t pos2 = line.find(",", pos1 + 1);
                size_t pos3 = line.find(",", pos2 + 1);

                accountNumber = stoi(line.substr(0, pos1));
                balance = stof(line.substr(pos1 + 1, pos2 - pos1 - 1));
                accountType = line.substr(pos2 + 1, pos3 - pos2 - 1);
                interestRate = stof(line.substr(pos3 + 1));

                cout << "\nAccount Number: " << accountNumber << endl;
                cout << "Balance: " << balance << endl;
                cout << "Account Type: " << accountType << endl;
                cout << "Interest Rate: " << interestRate << "%" << endl;
            }
            inFile.close();
        }
        else
        {
            cout << "Error: Could not open file to load account details.\n";
        }
    }

    void deleteAccount(int accountNumber) 
    {
        ifstream inFile("accounts.txt");
        ofstream outFile("temp.txt");

        if (inFile.is_open() && outFile.is_open()) 
        {
            string line;
            bool accountFound = false;

            while (getline(inFile, line)) 
            {
                size_t pos1 = line.find(",");
                int accountInFile = stoi(line.substr(0, pos1));

                if (accountInFile == accountNumber) 
                {
                    accountFound = true;
                    cout << "Account " << accountNumber << " deleted successfully.\n";
                    continue; 
                } 
                else
                {
                    outFile << line << endl;
                }
            }

            if (!accountFound) 
            {
                cout << "Account with Account Number " << accountNumber << " not found.\n";
            }

            inFile.close();
            outFile.close();

            remove("accounts.txt");
            rename("temp.txt", "accounts.txt");

        } 
        else
        {
            cout << "Error: Could not open file to delete account.\n";
        }
    }
};

void showMenu()
{
    cout << "========================================\n";
    cout << "        Welcome to Bank Management System\n";
    cout << "========================================\n";
    cout << "Please choose an option from the menu below:\n";
    cout << "----------------------------------------\n";
    cout << "1. Add a New Customer\n";
    cout << "2. View Customer Details\n";
    cout << "3. Update Customer Information\n";
    cout << "4. Create a New Account\n";
    cout << "5. Deposit Money into Account\n";
    cout << "6. Withdraw Money from Account\n";
    cout << "7. Calculate Interest on Account\n";
    cout << "8. View All Accounts\n";
    cout << "9. Admin Login\n";
    cout << "10. Exit the System\n";
    cout << "----------------------------------------\n";
    cout << "Please select an option (1-10): ";

}

int main() 
{
    Customer customer;
    Account account(1001, 5000.0, "Saving", 5.0); 
    Admin admin("admin", "aman111");  
    int choice;

    while (true) 
    {
        showMenu();
        cin >> choice;
        switch (choice) 
        {
            case 1:
                customer.addCustomer();
                break;
            case 2: {
                int id;
                cout << "Enter Customer ID: ";
                cin >> id;
                customer.displayCustomerDetails(id);
                break;
            }
            case 3: {
                int id;
                cout << "Enter Customer ID to Update: ";
                cin >> id;
                customer.updateCustomerInfo(id);
                break;
            }
            case 4: {
                int accNum;
                string type;
                float balance, interestRate;
                cout << "Enter Account Number: ";
                cin >> accNum;
                cout << "Enter Account Type (e.g., Saving/Checking): ";
                cin >> type;
                cout << "Enter Initial Balance: ";
                cin >> balance;
                cout << "Enter Interest Rate: ";
                cin >> interestRate;
                Account newAccount(accNum, balance, type, interestRate);
                newAccount.saveAccountToFile();
                break;
            }
            case 5: {
                float amount;
                cout << "Enter Deposit Amount: ";
                cin >> amount;
                account.deposit(amount);
                break;
            }
            case 6: {
                float amount;
                cout << "Enter Withdrawal Amount: ";
                cin >> amount;
                account.withdraw(amount);
                break;
            }
            case 7:
                account.calculateInterest();
                break;
            case 8:
                account.loadAccountsFromFile();
                break;
            case 9: {
                string id, password;
                cout << "Enter Admin ID: ";
                cin >> id;
                cout << "Enter Admin Password: ";
                cin >> password;
                if (admin.authenticateAdmin(id, password)) {
                    admin.viewAllAccounts();
                }
                break;
            }
            case 10:
                cout << "Exiting the system.\n";
                return 0;
            default:
                cout << "Invalid option, please try again.\n";
        }
    }
}
