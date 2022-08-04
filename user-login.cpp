/******************************************************************************
						  Group #3 Project - Milestone 2
Full Name  : Lomia Wu
Student ID : 116492182
Email      : rwu30@myseneca.ca
Section    : DBS_211_NHH
Date       : 2022-08-04
Module	   : User Module, Login Module
Declaration: I have implemented all by myself and only copied the code that
             my professor provided to complete my project milestones.
******************************************************************************/
#include <iostream>
#include <iomanip>
#include <occi.h>

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;


// OCCI Variables - Global
Environment* env = nullptr;
Connection* conn = nullptr;

// User Variables - Global
const string username = "dbs211_222h18";  // Lomia Wu
const string password = "29128324";       // Lomia Wu
const string srv = "myoracle12c.senecacollege.ca:1521/oracle12c";

// Prototypes
void printHeader();   // Print the header
void menu();          // Run the menu

void getUserInfo();   // Get Library User Data - done by Lomia Wu
void getLoginInfo();  // Get Library Login Data - done by Lomia Wu


int main() {
    printHeader();
    menu();  
    return 0;
}



// Definitions
void printHeader() {
    cout << "---------- Seneca Library Database Management System ----------" << endl;
    cout << "                  DBS211 Group #3 Project DEMO" << endl;
    cout << endl;
}

void menu() {
    int selection = -1;
    do {
        // print the menu items
        cout << " 1 - Login Report" << endl;
        cout << " 2 - User Report" << endl;
        cout << " 0 - Exit" << endl;
    
        // get the client' selection
        cout << " >";
        cin >> selection;
    
        // call the get() fucntion based on the selection
        switch (selection) {
            case 1:
                getUserInfo();
                break;
            case 2:
                getLoginInfo();
        }
        
    } while (selection != 0);
}

void getUserInfo() {
    string str;
    try {
        env = Environment::createEnvironment(Environment::DEFAULT);
        conn = env->createConnection(username, password, srv);

        // Report #1 User Report
        Statement* stmt = conn->createStatement();
        ResultSet* rs = stmt->executeQuery("SELECT user_id, first_name, last_name, email, system_id, type_id FROM libraryuser ORDER BY first_name");

        cout << "------------------------ Report 1 (Library User Report) ---------------------" << endl;
        cout << "User ID      First Name    Last Name   Email                 Login ID    Type" << endl;
        cout << "----------   -----------   ---------   -------------------   ---------   ----" << endl;
        while (rs->next()) {
            cout << setw(10) << left << rs->getInt(1) << "   " << setw(11) << rs->getString(2) << "   "
                << setw(9) << rs->getString(3) << "   " << setw(19) << rs->getString(4) << "   " << setw(9)
                << rs->getInt(5) << "   " << rs->getInt(6) << endl;
        }
        cout << endl;
        conn->terminateStatement(stmt); // Terminate statement

        // Terminate the connections
        env->terminateConnection(conn);
        Environment::terminateEnvironment(env);
    }
    catch (SQLException& sqlExcp) {
        cout << sqlExcp.getErrorCode() << "; "
            << sqlExcp.getMessage() << endl;
    }
}

void getLoginInfo() {
    string str;
    try {
        env = Environment::createEnvironment(Environment::DEFAULT);
        conn = env->createConnection(username, password, srv);

        // Report #1 User Report
        Statement* stmt = conn->createStatement();
        ResultSet* rs = stmt->executeQuery("SELECT login_id, last_access_date, active, username, password FROM login ORDER BY login_id");

        cout << "------------------------ Report 2 (Library Lgoin Report) ---------------------" << endl;
        cout << "Login ID   Login Date         Active   Username           Password" << endl;
        cout << "--------   ----------------   ------   ----------------   --------------------" << endl;
        while (rs->next()) {
            cout << setw(8) << left << rs->getInt(1) << "   " << setw(16) << rs->getString(2) << "   "
                << setw(6) << rs->getString(3) << "   " << setw(16) << rs->getString(4) << "   "
                << rs->getString(5) << endl;
        }
        cout << endl;
        conn->terminateStatement(stmt); // Terminate statement

        // Terminate the connections
        env->terminateConnection(conn);
        Environment::terminateEnvironment(env);
    }
    catch (SQLException& sqlExcp) {
        cout << sqlExcp.getErrorCode() << "; "
            << sqlExcp.getMessage() << endl;
    }
}