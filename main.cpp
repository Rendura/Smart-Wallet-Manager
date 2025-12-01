#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void login();
void registration();
void forgot();

class BudgetManager
{
private:
    double budget, allowance, savings, others;
    double Atotalbudget, Stotalbudget, Ototalbudget, totalBudget;
    const double totalpercentage = 100;
    double prcntallowance, prcntsavings, prcntothers;
    double total;
    string currentUser;
    string currentPass;

public:
    // Constructor
    BudgetManager() : budget(0.0), allowance(0.0), savings(0.0), others(0.0),
                      Atotalbudget(0.0), Stotalbudget(0.0), Ototalbudget(0.0), totalBudget(0.0),
                      prcntallowance(50.0), prcntsavings(30.0), prcntothers(20.0),
                      total(0.0) {}

    // Setters to access private
    void setBudgets(double a, double s, double o, double tb, double pa, double ps, double po, string uname, string pass) {
        Atotalbudget = a;
        Stotalbudget = s;
        Ototalbudget = o;
        totalBudget = tb;
        prcntallowance = pa;
        prcntsavings = ps;
        prcntothers = po;
        currentUser = uname;
        currentPass = pass;
        total = pa + ps + po;
    }
    //save data to txt file
    void saveData() {
        vector<string> lines;
        ifstream input("Record.txt");
        if (!input) {
            cout << "Error: Cannot open Record.txt for reading." << endl;
            return;
        }
        string line;
        while (getline(input, line)) {
            lines.push_back(line);
        }
        input.close();

        // updating every time per new user
        for (size_t i = 0; i < lines.size(); ++i) {
            if (lines[i].substr(0, currentUser.length() + 1) == currentUser + " ") {
                lines[i] = currentUser + " " + currentPass + " " + to_string(Atotalbudget) + " " + to_string(Stotalbudget) + " " + to_string(Ototalbudget) + " " + to_string(totalBudget) + " " + to_string(prcntallowance) + " " + to_string(prcntsavings) + " " + to_string(prcntothers);
                break;
            }
        }

        // user input to file txt
        ofstream output("Record.txt");
        if (!output) {
            cout << "Error: Cannot open Record.txt for writing." << endl;
            return;
        }
        for (const auto& l : lines) {
            output << l << endl;
        }
        output.close();
    }

    void Balance(){
        cout << "--------------\n";
        cout << "Total Budget: Php " << totalBudget << endl;
        cout << "Allowance: Php " << Atotalbudget << endl;
        cout << "Savings: Php " << Stotalbudget << endl;
        cout << "Other Expenses: Php " << Ototalbudget << endl;
        cout << "--------------\n";
        Main_Menu();
    }

    void Set_WeeklyBudget(){
        cout << "Enter the amount to add to your allowance/budget: ";
        cin >> budget;
        
        if (budget > 0) {
            totalBudget += budget;  // Add to total budget
            if (total == 100) {
                Atotalbudget = (prcntallowance / 100) * totalBudget;
                Stotalbudget = (prcntsavings / 100) * totalBudget;
                Ototalbudget = (prcntothers / 100) * totalBudget;
                cout << "Allowance added and allocations updated!" << endl;
                cout << "Allowance: Php " << Atotalbudget << endl;
                cout << "Savings: Php " << Stotalbudget << endl;
                cout << "Other Expenses: Php " << Ototalbudget << endl;
                saveData();
            } else {
                cout << "Please set budget percentages first." << endl;
            }
        } else {
            cout << "Invalid amount. Please enter a positive value." << endl;
        }
        Main_Menu();
    }

    void Set_Expenses(){
        double expenses;
        char c;
        cout << "Add your expenses: ";
        cin >> expenses;
        cout << "Where should we deduct your expenses?" << endl;
        cout << "[1] Allowance" << endl;
        cout << "[2] Other Expenses" << endl;
        cout << "[3] Exit" << endl;
        cin >> c;
        switch (c)
        {
        case '1':
            if (Atotalbudget >= expenses) {
                Atotalbudget -= expenses;
                cout << "You now have an allowance of: " << Atotalbudget << endl;
                saveData();
            } else {
                cout << "Insufficient funds in Allowance." << endl;
            }
            Main_Menu();
            break;
        case '2':
            if (Ototalbudget >= expenses) {
                Ototalbudget -= expenses;
                cout << "You now have other expenses of: " << Ototalbudget << endl;
                saveData();
            } else {
                cout << "Insufficient funds in Other Expenses." << endl;
            }
            Main_Menu();
            break;
        case '3':
            Main_Menu();
            break;
        default:
            cout << "Input a valid function" << endl;
            Main_Menu();
            break;
        }
    }

    void Set_BudgetPercent(){
        do {
            cout << "Set your % in Allowance: ";
            cin >> prcntallowance;
            cout << "Set your % in Savings: ";
            cin >> prcntsavings;
            cout << "Set your % in Other Expenses: ";
            cin >> prcntothers;
            total = prcntallowance + prcntsavings + prcntothers;
            cout << endl;
            if (total == 100) {
                cout << "Successfully Set-Up!" << endl;
                // Okay na to
                Atotalbudget = (prcntallowance / 100) * totalBudget;
                Stotalbudget = (prcntsavings / 100) * totalBudget;
                Ototalbudget = (prcntothers / 100) * totalBudget;
                saveData();
                Main_Menu();
            } else {
                cout << "Please make the total exactly 100%!" << endl;
            }
            cout << endl;
        } while (total != 100);
    }

    void Main_Menu(){
        int c;
        cout << "--------------\n";
        cout << "1. Custom Budget\n";
        cout << "2. Add Allowance\n";
        cout << "3. Add Expenses\n";
        cout << "4. Balance\n";
        cout << "--------------\n";
        cout << "Select from option: ";
        cin >> c;
        cout << endl;
        switch (c) {
        case 1:
            Set_BudgetPercent();
            break;
        case 2:
            Set_WeeklyBudget();
            break;
        case 3:
            Set_Expenses();
            break;
        case 4:
            Balance();
            break;
        default:
            cout << "Please select from the given options \n" << endl;
            Main_Menu();
            break;
        }
    }
};

int main(){
    int c;
    cout << "--------------\n";
    cout << "1. Login\n";
    cout << "2. Register\n";
    cout << "3. Recover your Password\n";
    cout << "--------------\n";
    cout << "Select from option: ";
    cin >> c;
    cout << endl;
    switch (c) {
    case 1:
        login();
        break;
    case 2:
        registration();
        break;
    case 3:
        forgot();
        break;
    default:
        cout << "Please select from the given options \n" << endl;
        main();
        break;
    }
    return 0;
}

void login(){
    int count = 0;
    string username, password, uname, pass;
    double a, s, o, tb, pa, ps, po;
    BudgetManager wallet;
    cout << "Please enter your username & password" << endl;
    cout << "USERNAME: ";
    cin >> username;
    cout << "PASSWORD: ";
    cin >> password;
    ifstream input("Record.txt");
    if (!input) {
        cout << "Error: Cannot open Record.txt." << endl;
        main();
        return;
    }
    while (input >> uname >> pass >> a >> s >> o >> tb >> pa >> ps >> po) {
        if (uname == username && pass == password) {
            count = 1;
            // Eto pag login binabasa nya
            wallet.setBudgets(a, s, o, tb, pa, ps, po, uname, pass);
            break;
        }
    }
    input.close();
    if (count == 1) {
        cout << "Welcome Back " << username << "!" << endl;
        wallet.Main_Menu();
    } else {
        cout << "Login ERROR Please re-login again" << endl;
        main();
    }
}

void registration(){
    string rusername, rpassword;
    cout << "Please enter your new username & password" << endl;
    cout << "USERNAME: ";
    cin >> rusername;
    cout << "PASSWORD: ";
    cin >> rpassword;
    ofstream rdata("Record.txt", ios::app);
    if (!rdata) {
        cout << "Error: Cannot open Record.txt for registration." << endl;
        main();
        return;
    }
    //input ng new user r=register
    rdata << rusername << ' ' << rpassword << ' ' << 0.0 << ' ' << 0.0 << ' ' << 0.0 << ' ' << 0.0 << ' ' << 50.0 << ' ' << 30.0 << ' ' << 20.0 << endl;
    rdata.close();
    cout << "Register Successfully!" << endl;
    main();
}

void forgot(){
    int option;
    cout << "You forgot your password? No worries" << endl;
    cout << "Press 1 to search your Username" << endl;
    cout << "Press 2 to go back to the home menu" << endl;
    cout << "Select from option: ";
    cin >> option;
    switch (option) {
    case 1: {
        int count = 0;
        string susername, suname, spass;
        cout << "Enter your remembered username\n";
        cout << "USERNAME: ";
        cin >> susername;
        ifstream sdata("Record.txt");
        if (!sdata) {
            cout << "Error: Cannot open Record.txt." << endl;
            forgot();
            return;
        }
        while (sdata >> suname >> spass) {
            if (suname == susername) {
                count = 1;
                break; //hahanapin kung may user na
            }
        }
        sdata.close();
        if (count == 1) {
            cout << "Your Account has been found" << endl;
            cout << "Your Password is: " << spass << endl;
            main();
        } else {
            cout << "Your Account not Found" << endl;
            forgot();
        }
        break;
    }
    case 2:
        main();
        break;
    default:
        cout << "Please try again\n";
        forgot();
        break;
    }
}
