#include <iostream>
#include <string>		// to be able to use getline()
#include <string.h>
#include <cctype>
#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
using namespace std;

//for demonstration only. never save your password in the code!
const string server = "tcp://127.0.0.1:3306";
const string username = "root";
const string password = "ak75fu2003@";
bool isLogin = false;

class NewBook {			//new class for putting and adding books
public:

	string booktitle;		//the attributes for the book
	string booktype;
	string bookauthor;
	int bookyear;
	int bookprice;
	int bookQTY;
	bool isAvailable;

	void BookDB() {
		cout << "BookTitle?\n";
		getline(cin, booktitle);	
		cout << "bookauthor?\n";
		getline(cin, bookauthor);
		cout << "booktype?\n";
		getline(cin, booktype);
		isAvailable = 1;
		cout << "bookQTY?\n";
		cin >> bookQTY;
		cout << "bookprice?\n";
		cin >> bookprice;
		cout << "Bookyear?\n";
		cin >> bookyear;

		sql::Driver* driver;
		sql::Connection* con;
		sql::Statement* stmt;
		sql::PreparedStatement* pstmt;

		try
		{
			driver = get_driver_instance();
			con = driver->connect(server, username, password);
		}
		catch (sql::SQLException e)
		{
			cout << "Could not connect to server. Error message: " << e.what() << endl;
			system("pause");
			exit(1);
		}

		//please create database "quickstartdb" ahead of time
		con->setSchema("library");

		stmt = con->createStatement();
		/*
		stmt->execute("DROP TABLE IF EXISTS inventory");
		cout << "Finished dropping table (if existed)" << endl;
		stmt->execute("CREATE TABLE inventory (id serial PRIMARY KEY, name VARCHAR(50), quantity INTEGER);");
		cout << "Finished creating table" << endl;*/
		delete stmt;

		pstmt = con->prepareStatement("INSERT INTO libraryproject(BookTitle, BookAuthor,BookType,BookQTY,BookPrice,BookYear) VALUES(?,?,?,?,?,?)");
		pstmt->setString(1, booktitle);
		pstmt->setString(2, bookauthor);
		pstmt->setString(3, booktype);
		pstmt->setInt(4, bookQTY);
		pstmt->setInt(5, bookprice);
		pstmt->setInt(6, bookyear);
		pstmt->execute();
		cout << "One row inserted." << endl;

		delete pstmt;
		delete con;
	}
	void bookinfoDB() {

		sql::Driver* driver;
		sql::Connection* con;
		sql::Statement* stmt;
		sql::PreparedStatement* pstmt;
		sql::ResultSet* str;

		try
		{
			driver = get_driver_instance();
			con = driver->connect(server, username, password);
		}
		catch (sql::SQLException e)
		{
			cout << "Could not connect to server. Error message: " << e.what() << endl;
			system("pause");
			exit(1);
		}


		con->setSchema("library");

		stmt = con->createStatement();
		string sql = "select * from libraryproject";
		str = stmt->executeQuery(sql);
		while (str->next()) {
			booktitle = str->getString("BookTitle");
			bookauthor = str->getString("BookAuthor");
			booktype = str->getString("BookType");
			bookQTY = str->getInt("BookQTY");
			bookyear = str->getInt("BookYear");

			cout << "BookTitle: "<<booktitle << endl;
			cout << "The Author is: "<<bookauthor << endl;
			cout << "Booktype: "<<booktype << endl;
			cout << "There is "<<bookQTY <<" number of this product" << endl;
			cout << "it came out in: "<<bookyear << endl;
			cout << "It is available\n" << endl;
		}

		delete stmt;
	}
	void removebookDB() {
		sql::Driver* driver;
		sql::Connection* con;
		sql::Statement* stmt;
		sql::PreparedStatement* pstmt;
		sql::ResultSet* str;

		try
		{
			driver = get_driver_instance();
			con = driver->connect(server, username, password);
		}
		catch (sql::SQLException e)
		{
			cout << "Could not connect to server. Error message: " << e.what() << endl;
			system("pause");
			exit(1);
		}

	
		con->setSchema("library");
		
		string deletebookname;
		cout << "Name of book you want to delete?\n";
		cin >> deletebookname;
		pstmt = con->prepareStatement("delete FROM libraryproject WHERE book =" +deletebookname);
		pstmt->execute();
		cout << "One Row Deleted";
		delete pstmt;
		delete con;
		
		
	}
	void searchBookDB() {
		sql::Driver* driver;
		sql::Connection* con;
		sql::Statement* stmt;
		sql::PreparedStatement* pstmt;
		sql::ResultSet* str;

		try
		{
			driver = get_driver_instance();
			con = driver->connect(server, username, password);
		}
		catch (sql::SQLException e)
		{
			cout << "Could not connect to server. Error message: " << e.what() << endl;
			system("pause");
			exit(1);
		}

		string booktitlex;
		int counter = 0;
		cout << "Booktitle: ";
		getline(cin, booktitlex);


		con->setSchema("library");

		stmt = con->createStatement();
		string sql = "select * from libraryproject";
		str = stmt->executeQuery(sql);
		while (str->next()) {
			booktitle = str->getString("BookTitle");
			bookQTY = str->getInt("BookQTY");
			
			if (booktitlex == booktitle) {
				cout << "we found " << bookQTY << " of " << booktitle << endl;
				counter++;
			}
		
		}
		if (counter < 1) {
			cout << "we currently don't have this book available\n";
		}

		delete stmt;
	}
	void checkPriceDB() {

		sql::Driver* driver;
		sql::Connection* con;
		sql::Statement* stmt;
		sql::PreparedStatement* pstmt;
		sql::ResultSet* str;

		try
		{
			driver = get_driver_instance();
			con = driver->connect(server, username, password);
		}
		catch (sql::SQLException e)
		{
			cout << "Could not connect to server. Error message: " << e.what() << endl;
			system("pause");
			exit(1);
		}

		string booktitlex;
		int counter = 0;
		cout << "Booktitle: ";
		getline(cin, booktitlex);


		con->setSchema("library");

		stmt = con->createStatement();
		string sql = "select * from libraryproject";
		str = stmt->executeQuery(sql);
		while (str->next()) {
			booktitle = str->getString("BookTitle");
			bookprice = str->getInt("BookPrice");

			if (booktitlex == booktitle) {
				cout <<  booktitle << " is priced at "<<bookprice<<"$"<<endl;
				counter++;
			}

		}
		if (counter < 1) {
			cout << "we didn't find the book you are looking for\n";
		}

		delete stmt;
	}
};
class user {
public:
	string Usernamedb;
	string Gmail;
	string Userpassword;
	string Role;

	void UserDB() {
		cout << "To register, please type your Gmail, then create your username and password\n";
		cout << "Gmail: ";
		getline(cin,Gmail);
		cout << endl;
		cout << "Username: ";
		cout << endl;
		getline(cin,Usernamedb);
		cout << endl;
		cout << "Password: ";
		getline(cin,Userpassword);
		cout << endl;
		Role = "employee";

		sql::Driver* driver;
		sql::Connection* con;
		sql::Statement* stmt;
		sql::PreparedStatement* pstmt;

		try
		{
			driver = get_driver_instance();
			con = driver->connect(server, username, password);
		}
		catch (sql::SQLException e)
		{
			cout << "Could not connect to server. Error message: " << e.what() << endl;
			system("pause");
			exit(1);
		}

		
		con->setSchema("library");

		stmt = con->createStatement();
		
		delete stmt;

		pstmt = con->prepareStatement("INSERT INTO user(Username,Gmail,Password,Role) VALUES(?,?,?,?)");
		pstmt->setString(1, Usernamedb);
		pstmt->setString(2,Gmail);
		pstmt->setString(3,Userpassword);
		pstmt->setString(4, Role);
		pstmt->execute();
		cout << "One row inserted." << endl;

		delete pstmt;
		delete con;

	}
	void Login() {
		

		sql::Driver* driver;
		sql::Connection* con;
		sql::Statement* stmt;
		sql::PreparedStatement* pstmt;
		sql::ResultSet* str;

		try
		{
			driver = get_driver_instance();
			con = driver->connect(server, username, password);
		}
		catch (sql::SQLException e)
		{
			cout << "Could not connect to server. Error message: " << e.what() << endl;
			system("pause");
			exit(1);
		}


		con->setSchema("library");

		stmt = con->createStatement();
		string sql = "select Username,password from user";
		str = stmt->executeQuery(sql);
		string usernm;
		string psswrd;
	
			cout << "username?\n";
			getline(cin, Usernamedb);
			cout << "password?\n";
			getline(cin, Userpassword);
			system("CLS");

			int counter=0;
			int counter1 = 0;
	
			do {
				while (str->next()) {

					
					counter = str->getRow();
					//cout << counter;

					usernm = str->getString("Username");
					psswrd = str->getString("password");

					if (Usernamedb == usernm && Userpassword == psswrd) {
						isLogin = true;
						break;
					}
					else if(counter==8) {
						cout << "login failed! restart program...";
						exit(0);
					}
					else
						isLogin = false;
					continue;
				}
			} while (isLogin == false);
			cout << "welcome to our library\n";
	
		delete stmt;

	}
};
int main()
{

	int i;
	int ii;

	do {
		cout << "-------------------Welcome to our Library-------------------\n";
		cout << "1.To Register\n";
		cout << "2.To Login\n";
		cin >> ii;
		cin.ignore();
		if (ii > 2 || ii < 1) {								//prints out that there is an error before asking the user again
			cout << "invalid input! try again." << endl;
		}
		system("CLS");
		switch (ii) {
		case 1: {
			user User1;
			User1.UserDB();
			system("CLS");
			break;
		}
		case 2: {
			user User2;
			User2.Login();
			
			break;
		}
		}
	} while (ii==1|| ii < 1 || ii > 3);


	do {

		cout << "1.check our available books here." << endl;		//print out the menu options
		cout << "2.add new book." << endl;
		//cout << "3.remove old book." << endl;
		cout << "3.search for a book." << endl;
		cout << "4.check price of book." << endl;
		cout << "5.exit system" << endl;

		cin >> i;
		cin.ignore();							// if i dont use this after a cin that is before a getline function than getline wont work

		if (i > 5 || i < 1) {								//prints out that there is an error before asking the user again
			cout << "invalid input! try again." << endl;
		}

		cout << "-----------------------------------------------------------------------------" << endl;
		system("CLS");
		NewBook newbook;
		switch (i)
		{
		case 1:
			cout << "we currently have the following books: \n\n";
			newbook.bookinfoDB();


			break;

		case 2: {
			NewBook Libraryinsert;
			Libraryinsert.BookDB();
			break;

		}
		case 3:
		{
			NewBook LibrarySearch;
			LibrarySearch.searchBookDB();
			break;
		}
		case 4:
		{
			NewBook LibraryPrice;
			LibraryPrice.checkPriceDB();
			break;
		}
		case 5:
		{
			
			break;
		}
		
		}
	} while (i != 5 || i < 1 || i > 5);				//if anything else inputed in menu, the program will ask again
	return 0;
}
