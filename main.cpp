// #include <iostream>
// #include <chrono>
// #include <iomanip>
// #include <fstream>
#include <bits/stdc++.h>
#include "my_header.h"
using namespace std;

class Expense
{
public:
    string title;
    string date;
    int amount;

public:
    // default constructor for vector initialization
    Expense() : title(""), date(""), amount(0) {}
    Expense(string title, string date, int amount) : title(title), date(date), amount(amount) {}
    Expense(string title, int amount) : Expense(title, get_current_date(), amount) {}

    string get_current_date()
    {
        auto now = std::chrono::system_clock::now();
        // Convert the system time to a time_t object
        time_t currentTime = chrono::system_clock::to_time_t(now);

        // Convert the time_t object to a tm structure
        tm *currentTm = std::localtime(&currentTime);

        // Format the date using std::put_time
        stringstream ss;
        ss << put_time(currentTm, "%d-%m-%Y");
        return ss.str();
    }
};

class ExpenseTracker
{
private:
    my_vector<Expense> expenses;
    string filename;

public:
    ExpenseTracker(string filename) : filename(filename)
    {
        loadExpense(expenses);
    }

    // Add new expense
    void saveExpense()
    {
        ofstream file(filename);
        if (!file)
        {
            cout << "Error opening file" << endl;
            return;
        }
        for (auto entry : expenses)
        {
            file << entry.title << "," << entry.date << "," << entry.amount << "\n";
        }
        file.close();
        cout << "Expense saved successfully" << endl;
    }

    void addExpense()
    {
        string title;
        int amount;
        cout << "Enter Expense Title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter Expense amount: ";
        cin >> amount;
        expenses.push_back(Expense(title, amount));
        saveExpense();
    }

    // load expense data from file
    void loadExpense(my_vector<Expense> &loaded_expenses)
    {
        ifstream file(filename);
        if (!file)
        {
            cout << "Error opening file" << endl;
            return;
        }
        string line, title, date, amountStr;
        int amount;
        while (getline(file, line))
        {
            istringstream iss(line);
            if (getline(iss, title, ',') && getline(iss, date, ',') && (iss >> amount))
            {
                Expense item(title, date, amount);
                loaded_expenses.push_back(item);
            }
        }
        file.close();
    }

    void displayExpense(int i, Expense &e)
    {
        cout << setw(4) << i + 1 << setw(14) << e.date << setw(20) << e.title << setw(8) << e.amount << endl;
    }

    void displayHeader()
    {
        cout << endl;
        cout << setw(4) << "ID" << setw(10) << "Date" << setw(20) << "Title" << setw(14) << "Amount" << endl;
    }

    void displayExpenses()
    {
        if (expenses.empty())
        {
            cout << "No expense to display" << endl;
            return;
        }
        displayHeader();
        for (int i = 0; i < expenses.size(); i++)
        {
            displayExpense(i, expenses[i]);
        }
    }

    void updateExpense()
    {
        int index;
        cout << "Enter expense id: ";
        cin >> index;
        if (index > 0 && index <= expenses.size())
        {
            index--;

            Expense &expense = expenses[index];
            string title, date;
            int amount;
            cout << "Enter new title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter new date: ";
            cin >> date;
            cout << "Enter new amount: ";
            cin >> amount;
            expense.title = title;
            expense.date = date;
            expense.amount = amount;
            saveExpense();
        }
        else
        {
            cout << "Invalid index id!!" << endl;
        }
    }

    void deleteExpense()
    {
        int index;
        cout << "Enter expense id: ";
        cin >> index;

        if (index > 0 && index <= expenses.size())
        {
            index--;
            expenses.erase(expenses.begin() + index);
            saveExpense();
        }
        else
        {
            cout << "Invalid expense id" << endl;
        }
    }

    void searchExpense()
    {
        string date;
        bool flag = true;
        cout << "Enter date in this format(DD-MM-YYYY): ";
        cin >> date;
        displayHeader();
        for (int i = 0; i < expenses.size(); i++)
        {
            if (expenses[i].date == date)
            {
                displayExpense(i, expenses[i]);
                flag = false;
            }
        }
        if (flag)
            cout << "No Expense found on " << date << endl;
    }
};

int main()
{
    ExpenseTracker app = ExpenseTracker("expenses.csv");
    int choice;
    cout << endl;
    cout << "#### Expense Tracker Menu####" << endl
         << endl;
    cout << "Choose an Option" << endl;
    cout << "1. Add New Expense" << endl;
    cout << "2. Update Existing Expense" << endl;
    cout << "3. Search Expense By Date" << endl;
    cout << "4. Delete An Expenses" << endl;
    cout << "5. View all Expenses" << endl;
    cout << "0. Exit App" << endl;
    do
    {
        cout << endl;
        cout << "Your Option: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            app.addExpense();
            break;
        case 2:
            app.updateExpense();
            break;
        case 3:
            app.searchExpense();
            break;
        case 4:
            app.deleteExpense();
            break;
        case 5:
            app.displayExpenses();
            break;
        case 0:
            cout << "Exited Successfully" << endl;
            break;

        default:
            cout << "Wrong Choice!! Try Again" << endl;
        }
    } while (choice != 0);
}