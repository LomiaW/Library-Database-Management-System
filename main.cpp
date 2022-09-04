/******************************************************************************
                          Group #3 Project - Milestone 2
Full Name  : Lomia Wu, Zhonghui Liu, Zijun Li
Date       : 2022-08-10
Module	   : User Module, Login Module, Book Report Module, Loan Report Module,
             Fine Report Module
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
const string username = "";  // Lomia Wu
const string password = "";       // Lomia Wu
const string srv = "myoracle12c.senecacollege.ca:1521/oracle12c";

// const string username = ""; // Zhonghui Liu 
// const string password = ""; // Zhonghui Liu
// const string srv = "";

// const string username = ""; // Zijun Li 
// const string password = ""; // Zijun Li
// const string srv = "";

// Prototypes
void printHeader();   // Print the header
void menu();          // Run the menu

void getUserInfo();   // Get Library User Data - done by Lomia Wu
void getLoginInfo();  // Get Library Login Data - done by Lomia Wu
void getBookReport(); // Get Library Book Report Data - done by Zhonghui Liu
void getLoanReport(); // Get Library Loan Report Data - done by Zhonghui Liu
void getFineReport(); // Get Library Fine Report Data - done by Zijun Li
void display(int repetitions, char c);


int main() {
    printHeader();
    menu();
    return 0;
}



// Definitions
void printHeader() {
    cout << "---------- Seneca Library Database Management System ----------" << endl;
    cout << "           DBS211 Group #3 Project DEMO        Date: 2022-08-10" << endl;
    cout << endl;
}

void menu() {
    int selection = -1;
    bool invalid = false;
    do {
        // print the menu items
        cout << " 1 - Login Report" << endl;
        cout << " 2 - User Report" << endl;
        cout << " 3 - Book Report" << endl;
        cout << " 4 - Loan Report" << endl;
        cout << " 5 - Fine Report" << endl;
        cout << " 0 - Exit" << endl;

        // get the client' selection
        do {
            invalid = false;
            cout << "Enter your selection:";
            cin >> selection;
            if (!cin.good()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input, try again." << endl;
                invalid = true;
            }
            else if (selection < 0 || selection > 5) {
                cout << "Invalid number, try again." << endl;
                invalid = true;
            }
            cout << endl;
        } while (invalid);

        // call the get() fucntion based on the selection
        switch (selection) {
        case 1:
            getUserInfo();
            break;
        case 2:
            getLoginInfo();
            break;
        case 3:
            getBookReport();
            break;
        case 4:
            getLoanReport();
            break;
        case 5:
            getFineReport();
            break;
        }
        cout << endl;
    } while (selection != 0);
}

void getUserInfo() {
    string str;
    try {
        env = Environment::createEnvironment(Environment::DEFAULT);
        conn = env->createConnection(username, password, srv);

        // Report #1 User Report
        Statement* stmt = conn->createStatement();
        ResultSet* rs = stmt->executeQuery("SELECT user_id, first_name, last_name, email, login_id, type_id FROM libraryuser ORDER BY first_name");

        cout << "------------------------ Report 1 (Library User Report) ---------------------" << '\n' << endl;
        cout << "User ID      First Name    Last Name   Email                 Login ID    Type" << endl;
        cout << "----------   -----------   ---------   -------------------   ---------   ----" << endl;
        while (rs->next()) {
            cout << setw(10) << left << rs->getInt(1) << "   " << setw(11) << rs->getString(2) << "   "
                << setw(9) << rs->getString(3) << "   " << setw(19) << rs->getString(4) << "   " << setw(9)
                << rs->getInt(5) << "   " << rs->getInt(6) << endl;
        }
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

        // Report #2 Login Report
        Statement* stmt = conn->createStatement();
        ResultSet* rs = stmt->executeQuery("SELECT login_id, last_access_date, active, username, password FROM login ORDER BY login_id");

        cout << "------------------ Report 2 (Library Login Report) ------------------" << '\n' << endl;
        cout << "Login ID   Login Date         Active   Username           Password" << endl;
        cout << "--------   ----------------   ------   ----------------   -----------" << endl;
        while (rs->next()) {
            cout << setw(8) << left << rs->getInt(1) << "   " << setw(16) << rs->getString(2) << "   "
                << setw(6) << rs->getString(3) << "   " << setw(16) << rs->getString(4) << "   "
                << rs->getString(5) << endl;
        }
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

void getBookReport() {
    string str;
    try {
        env = Environment::createEnvironment(Environment::DEFAULT);
        conn = env->createConnection(username, password, srv);

        // Report #3 Book Report
        const string query = "SELECT isbn_no, title, first_name || ' ' || last_name AS author_name, edition, category, name AS publisher_name, copies_owned, shelf_no FROM book JOIN book_author USING(isbn_no) JOIN author USING(author_id) JOIN publisher USING(publisher_id) JOIN location USING(location_id) ORDER BY copies_owned, shelf_no";


        Statement* stmt = conn->createStatement(query);
        ResultSet* rs = stmt->executeQuery();

        display(74, '-');
        cout << " Report 3 (Library Book Report) ";
        display(74, '-');
        cout << "\n" << endl;

        cout << left << setw(10) << "Isbn_no" << "   ";
        cout << left << setw(40) << "Title" << "   ";
        cout << left << setw(35) << "Author" << "   ";
        cout << left << setw(7) << "Edition" << "   ";
        cout << left << setw(30) << "Category" << "   ";
        cout << left << setw(20) << "Publisher_name" << "   ";
        cout << left << setw(12) << "Copies_owned" << "   ";
        cout << "Shelf_no" << endl;

        display(10, '-'); // isbn_no
        display(3, ' ');
        display(40, '-'); // title
        display(3, ' ');
        display(30, '-'); // author name
        display(3, ' ');
        display(7, '-'); // edition
        display(3, ' ');
        display(30, '-'); // category
        display(3, ' ');
        display(20, '-'); // publisher name
        display(3, ' ');
        display(12, '-'); // copies owned
        display(3, ' ');
        display(10, '-'); // shelf no
        cout << endl;

        while (rs->next()) {
            cout << setw(10) << left << rs->getInt(1) << "   "; // isbn_no
            cout << setw(40) << left << rs->getString(2) << "   "; // title
            cout << setw(30) << rs->getString(3) << "   "; // author_name
            cout << setw(7) << rs->getInt(4) << "   "; // edition
            cout << setw(30) << left << rs->getString(5) << "   "; // category
            cout << setw(20) << left << rs->getString(6) << "   "; // publisher name
            cout << setw(12) << rs->getInt(7) << "   "; // copies_owned
            cout << rs->getString(8) << endl; // shelf no
        }
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

void getLoanReport() {
    string str;
    try {
        env = Environment::createEnvironment(Environment::DEFAULT);
        conn = env->createConnection(username, password, srv);

        // Report #4 Library Loan Report
        const string query = "SELECT user_id, first_name || ' ' || last_name AS user_name, type_desc, isbn_no, title, checkout_date FROM LIBRARYUSER JOIN USERTYPE ON LIBRARYUSER.type_id = USERTYPE.usertype_id JOIN RECORD USING (user_id) JOIN BOOK USING (isbn_no) ORDER BY checkout_date desc";

        Statement* stmt = conn->createStatement(query);
        ResultSet* rs = stmt->executeQuery();

        display(41, '-');
        cout << " Report 4 (Library Loan Report) ";
        display(41, '-');
        cout << "\n" << endl;

        cout << left << setw(10) << "User_id" << "   ";
        cout << left << setw(15) << "User_name" << "   ";
        cout << left << setw(10) << "Type_desc" << "   ";
        cout << left << setw(10) << "Isbn_no" << "   ";
        cout << left << setw(45) << "Title" << "   ";
        cout << "Checkout" << endl;

        display(10, '-'); // user_id
        display(3, ' ');
        display(15, '-'); // user_name
        display(3, ' ');
        display(10, '-'); // type_desc
        display(3, ' ');
        display(10, '-'); // isbn_no
        display(3, ' ');
        display(45, '-'); // title
        display(3, ' ');
        display(8, '-'); // checkout
        cout << endl;

        while (rs->next()) {
            cout << setw(10) << left << rs->getInt(1) << "   "; // user_id
            cout << setw(15) << left << rs->getString(2) << "   "; // user_name
            cout << setw(10) << rs->getString(3) << "   "; // type_desc
            cout << setw(10) << rs->getInt(4) << "   "; // isbn_no
            cout << setw(45) << left << rs->getString(5) << "   "; // title
            cout << setw(20) << left << rs->getString(6) << "   "; // checkout
            cout << endl;
        }
        conn->terminateStatement(stmt); // Terminate statement
    }
    catch (SQLException& sqlExcp) {
        cout << sqlExcp.getErrorCode() << "; "
            << sqlExcp.getMessage() << endl;
    }
}

void getFineReport() {
    string str;
    try {
        env = Environment::createEnvironment(Environment::DEFAULT);
        conn = env->createConnection(username, password, srv);

        // Report #5 Fine Report
        const string query = "SELECT BOOK.title, RECORD.isbn_no, fine_id, RECORD.user_id, FINE.record_no, fine_date, fine_amount FROM FINE JOIN RECORD ON FINE.record_no = RECORD.record_no JOIN BOOK ON RECORD.isbn_no = BOOK.isbn_no ORDER BY fine_date, fine_amount";


        Statement* stmt = conn->createStatement(query);
        ResultSet* rs = stmt->executeQuery();

        display(30, '-');
        cout << " Report 5 (Fine Report) ";
        display(30, '-');
        cout << "\n" << endl;

        cout << left << setw(40) << "Title" << "   ";
        cout << left << setw(10) << "isbn_no" << "   ";
        cout << left << setw(7) << "Fine_id" << "   ";
        cout << left << setw(9) << "User_id" << "   ";
        cout << left << setw(9) << "Record_no" << "   ";
        cout << left << setw(11) << "Fine_date" << "   ";
        cout << "Fine_amount" << endl;


        display(40, '-'); // title
        display(3, ' ');
        display(10, '-'); // isbn_no
        display(3, ' ');
        display(7, '-'); // fine_id
        display(3, ' ');
        display(9, '-'); // user_id
        display(3, ' ');
        display(9, '-'); // record_no
        display(3, ' ');
        display(11, '-'); // fine_date
        display(3, ' ');
        display(8, '-'); // fine_amount
        display(3, ' ');
        cout << endl;

        while (rs->next()) {

            cout << setw(40) << left << rs->getString(1) << "   "; // title
            cout << setw(10) << left << rs->getInt(2) << "   "; // isbn_no
            cout << setw(7) << left << rs->getInt(3) << "   "; // fine_id
            cout << setw(9) << left << rs->getInt(4) << "   "; // user_id
            cout << setw(9) << rs->getInt(5) << "   "; // record_no
            cout << setw(11) << rs->getString(6) << "   "; // fine_date
            cout << setw(10) << left << rs->getDouble(7) << "   "; // fine_amount
            cout << endl;
        }
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

void display(int repetitions, char c) {
    int i;

    for (i = 0; i < repetitions; i++) {
        cout << c;
    }

}
