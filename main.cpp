#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void login();
void registration();
void forgot();

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

    switch (c)
    {
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
        break;
    }
    return 0;
}

void login(){
    int count;
    string username, password, uname, pass;

    cout << "Please enter your username & password" << endl;
    cout << "USERNAME: ";
    cin >> username;
    cout << "PASSWORD: ";
    cin >> password;

        ifstream input("Record.txt");

        while (input >> uname >> pass)
        {
            if (uname == username && pass == password)
            {
                count = 1;
            }
            
        }
        input.close();

        if (count == 1)
        {
            cout << "Welcome Back " << username << "!" << endl;
            // dito ilalagay yung main menu na naka oop pag successful ang login :>
        }
        else
        {
            cout << "Login ERROR Please re-login again" << endl;
            main();
        }
}

void registration(){
    string rusername, rpassword, runame, rpass;

    cout << "Please enter your new username & password" << endl;
    cout << "USERNAME: ";
    cin >> rusername;
    cout << "PASSWORD: ";
    cin >> rpassword;

        ofstream rdata("Record.txt", ios::app);
        rdata << rusername << ' ' << rpassword << endl;
        cout << "Register Successfully!" << endl;
        main();
        

}

void forgot(){
    int option;

    cout << "You forgot your password? No worries" << endl;
    cout << "Press 1 to search you Username" << endl;
    cout << "Press 2 to go back to the home menu" << endl;
    cout << "Select from option: ";
    cin >> option;

    switch (option)
    {
    case 1:
        {
            int count = 0;
            string susername, spassword, suname, spass;

            cout << "Enter your remembered username\n";
            cout << "USERNAME: ";
            cin >> susername;

            ifstream sdata("Record.txt");
                while(sdata >> suname >> spass)
                {
                    if (suname == susername)
                    {
                        count = 1;
                    }
                }
                sdata.close();

                if (count == 1)
                {
                    cout << "Your Account have been found" << endl;
                    cout << "Your Password is: " << spass << endl;
                    main();
                }
                else
                {
                    cout << "Your Account not Found" << endl;
                }
        }
        break;
    case 2:
        main();
        break;
    default:
        cout << "Please try again\n";
        break;
    }

}