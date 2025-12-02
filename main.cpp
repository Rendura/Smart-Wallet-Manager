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
        vector<string> lines;// allowing array to chage it size during runtime
        ifstream input("Record.txt");
        if (!input) {
            cout << "Error: Cannot open Record.txt for reading." << endl;
            return;
        }
        string line;
        //Adds a new input after the last input
        while (getline(input, line)) {
            lines.push_back(line);
        }
        input.close();

        // updating every time per new user to add new line
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
        cout << "                       ===================================================================================\n";
        cout << "                       ||                                    BALANCE                                    ||\n";
        cout << "                       ===================================================================================\n";
        cout << "                                                     Allowance: Php " << Atotalbudget << endl;
        cout << "                                                     Savings: Php " << Stotalbudget << endl;
        cout << "                                                     Other Expenses: Php " << Ototalbudget << endl;
        cout << "                       ===================================================================================\n";
        Main_Menu();
    }

    void Set_WeeklyBudget(){
        cout << "                       ===================================================================================\n";
        cout << "                       ||                                  SET A ALLOWANCE                              ||\n";
        cout << "                       ===================================================================================\n";
            cout << "                         Enter amount to add: ";
            cin >> budget;  
            totalBudget += budget;  
            if (total == 100) {
            double newAllowance = (prcntallowance / 100.0) * budget;
            Atotalbudget += newAllowance;
            Stotalbudget += (prcntsavings / 100.0) * budget;
            Ototalbudget += (prcntothers / 100.0) * budget;
            cout << endl;
            cout << "                                               Allowance added and allocations updated!" << endl;
            cout << endl;
            cout << "                                                       Allowance: Php " << Atotalbudget << endl;
            cout << "                                                       Savings: Php " << Stotalbudget << endl;
            cout << "                                                       Other Expenses: Php " << Ototalbudget << endl;
            saveData();
        } else {
            cout << "                                               Please set budget percentages first." << endl;
        }
        Main_Menu();
    }

    void Set_Expenses(){
        double expenses;
        char c;
        cout << "                       ===================================================================================\n";
        cout << "                       ||                                  ADD EXPENSES                                 ||\n";
        cout << "                       ===================================================================================\n";
        cout << "                         Add your expenses: ";
        cin >> expenses;
        cout << endl;
        cout << "                         Where should we deduct your expenses?" << endl;
        cout << "                                   [1] Allowance" << endl;
        cout << "                                   [2] Other Expenses" << endl;
        cout << "                                   [3] Exit" << endl;
        cout << endl;
        cout << "                         Select from opions: ";
        cin >> c;
        cout << "                       ===================================================================================\n";
        switch (c)
        {
        case '1':
            if (Atotalbudget >= expenses) {
                Atotalbudget -= expenses;
                cout << "                                                  You now have an allowance of: " << Atotalbudget << endl;
                saveData();
            } else {
                cout << "                                                  Insufficient funds in Allowance." << endl;
            }
            Main_Menu();
            break;
        case '2':
            if (Ototalbudget >= expenses) {
                Ototalbudget -= expenses;
                cout << "                                                You now have other expenses of: " << Ototalbudget << endl;
                saveData();
            } else {
                cout << "                                                Insufficient funds in Other Expenses." << endl;
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
            cout << "                       ===================================================================================\n";
            cout << "                       ||                              SET BUDGET PERCENT %                             ||\n";
            cout << "                       ===================================================================================\n";
            cout << "                         Set your % in Allowance: "; 
            cin >> prcntallowance;
            cout << "                         Set your % in Savings: ";
            cin >> prcntsavings;
            cout << "                         Set your % in Other Expenses: ";
            cin >> prcntothers;
            total = prcntallowance + prcntsavings + prcntothers;
            cout << endl;
            if (total == 100) {
                cout << "                                                   Successfully Set-Up!" << endl;
                cout << "                       ===================================================================================\n";
                Atotalbudget = (prcntallowance / 100.0) * totalBudget;
                Stotalbudget = (prcntsavings / 100.0) * totalBudget;
                Ototalbudget = (prcntothers / 100.0) * totalBudget;
                saveData();
                Main_Menu();
            } else {
                cout << "Please make the total exactly 100%!" << endl;
            }
            cout << endl;
        } while (total != 100);
    }

    void Main_Menu(){
        char c;
        cout << "                       ===================================================================================\n";
        cout << "                       ||                              STUDENT BUDGET MANAGER                           ||\n";
        cout << "                       ||                                                                               ||\n";
        cout << "                       ||                                [1] Custom Budget                              ||\n";
        cout << "                       ||                                [2] Add Allowance                              ||\n";
        cout << "                       ||                                [3] Add Expenses                               ||\n";
        cout << "                       ||                                [4] Balance                                    ||\n";
        cout << "                       ||                                [5] Exit                                       ||\n";
        cout << "                       ===================================================================================\n";
        cout << "                         Select from option: ";
        cin >> c;
        cout << endl;
        switch (c) {
        case '1':
            Set_BudgetPercent();
            break;
        case '2':
            Set_WeeklyBudget();
            break;
        case '3':
            Set_Expenses();
            break;
        case '4':
            Balance();
            break;
        case '5':
            Main_Menu();
            break;
        default:
            cout << "Please select from the given options \n" << endl;
            Main_Menu();
            break;
        }
    }
};

int main(){
    char c;
    cout << "                       ===================================================================================\n";
    cout << "                       ||                              STUDENT BUDGET MANAGER                           ||\n";
    cout << "                       ===================================================================================\n";
    cout << "                       ||                                  [1] Login                                    ||\n";
    cout << "                       ||                                  [2] Register                                 ||\n";
    cout << "                       ||                                  [3] Recover your Password                    ||\n";
    cout << "                       ||                                  [4] Exit Program                             ||\n";
    cout << "                       ===================================================================================\n";
    cout << "                         Select from option: ";
    cin >> c;
    cout << endl;
    switch (c) {
    case '1':
        login();
        break;
    case '2':
        registration();
        break;
    case '3':
        forgot();
        break;
    case '4':
        exit(0);
        break;
    default:
        cout << "                                            Please select from the given options \n" << endl;
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
    cout << "                       ===================================================================================\n";
    cout << "                       ||                              STUDENT BUDGET MANAGER                           ||\n";
    cout << "                       ||                                      LOGIN                                    ||\n";
    cout << "                       ===================================================================================\n";
    cout << "                                                 Please enter your username & password" << endl;
    cout << endl;
    cout << "                         USERNAME: ";
    cin >> username;
    cout << "                         PASSWORD: ";
    cin >> password;
    //if file is broken this will show
    ifstream input("Record.txt");
    if (!input) {
        cout << "                                               Error: Cannot open Record.txt." << endl;
        main();
        return;
    }
    //read .txt file to login
    while (input >> uname >> pass >> a >> s >> o >> tb >> pa >> ps >> po) {
        if (uname == username && pass == password) {
            count = 1;
            wallet.setBudgets(a, s, o, tb, pa, ps, po, uname, pass);
            break;
        }
    }
    input.close();
    if (count == 1) {
        cout << "                                                         Welcome Back " << username << "!" << endl;
        wallet.Main_Menu();
    } else {
        cout << "                                                  Login ERROR Please re-login again" << endl;
        main();
    }
}

void registration(){
    string rusername, rpassword;
    cout << "                       ===================================================================================\n";
    cout << "                       ||                              STUDENT BUDGET MANAGER                           ||\n";
    cout << "                       ||                                   REGISTRATION                                ||\n";
    cout << "                       ===================================================================================\n";
    cout << "                                             Please enter your new username & password" << endl;
    cout << endl;
    cout << "                         USERNAME: ";
    cin >> rusername;
    cout << "                         PASSWORD: ";
    cin >> rpassword;
    ofstream rdata("Record.txt", ios::app);
    if (!rdata) {
        cout << "                                      Error: Cannot open Record.txt for registration." << endl;
        main();
        return;
    }
    //inputs new data into txt file to save
    rdata << rusername << ' ' << rpassword << ' ' << 0.0 << ' ' << 0.0 << ' ' << 0.0 << ' ' << 0.0 << ' ' << 50.0 << ' ' << 30.0 << ' ' << 20.0 << endl;
    rdata.close();
    cout << "                                                     Register Successfully!" << endl;
    main();
}

void forgot(){
    char option;
    cout << "                       ===================================================================================\n";
    cout << "                       ||                              STUDENT BUDGET MANAGER                           ||\n";
    cout << "                       ||                                RECOVERY PASSWORD                              ||\n";
    cout << "                       ===================================================================================\n";
    cout << "                                               You forgot your password? No worries" << endl;
    cout << endl;
    cout << "                                                Press [1] to search your Username" << endl;
    cout << "                                                Press [2] to go back to the home menu" << endl;
    cout << "                         Select from option: ";
    cin >> option;
    switch (option) {
    case '1': {
        int count = 0;
        string susername, suname, spass;
        cout << "                       ===================================================================================\n";
        cout << "                       ||                         ENTER YOUR REMEMBERED USERNAME                        ||\n";
        cout << "                       ===================================================================================\n";
        cout << "                         USERNAME: ";
        cin >> susername;
        ifstream sdata("Record.txt");
        if (!sdata) {
            cout << "                                            Error: Cannot open Record.txt." << endl;
            forgot();
            return;
        }
        while (sdata >> suname >> spass) {
            if (suname == susername) {
                count = 1;
                break;
            }
        }
        sdata.close();
        if (count == 1) {
            cout << "                                              Your Account has been found" << endl;
            cout << "                                              Your Password is: " << spass << endl;
            main();
        } else {
            cout << "                                              Your Account not Found" << endl;
            forgot();
        }
        break;
    }
    case '2':
        main();
        break;
    default:
        cout << "                                                      Please try again\n";
        forgot();
        break;
    }
}