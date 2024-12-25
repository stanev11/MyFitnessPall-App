// UP_prac2024-2025_fn08MI0600418_kn09.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//Solution to course project #9
//Introduction to programming course
//Faculty of Mathematics and Informatics of Sofia University
//Winter Semester 2024 / 2025
//
//@author Yasen Stanev
//@idnumber 08MI0600418
//@compiler VC
//
//This project is designed for everyone who wants to track his / her daily calories and stuff.


#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

//1 - Register or log-in window
void RegisterOrLogIn();

//1.2 - Register Window
void RegisterWindow();

//Checking if a user has profile
bool CheckIfUserExists(string username, string password);
int main()
{
	//1 - Register or log-in window
	RegisterOrLogIn();
}
//Register or log-in window
void RegisterOrLogIn()
{
	cout << "- - - Welcome to myfitnesspal! - - -" << endl << endl;
	do
	{
		cout << "Please choose 1 or 2" << endl;
		cout << "1. Log in"<<endl;
		cout << "2. Sign up"<<endl;
		cout << "Choice: ";
		int option;
		cin >> option;
		if (cin.fail() || (option!=1 && option!=2))
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid choice!" << endl;
		}
		else if (option == 1)
		{
			LogInWindow();
			break;
		}
		else
		{
			RegisterWindow();
			break;
		}
		else
void RegisterWindow()
{
	cout << "- - - Registration Form - - -" << endl << endl;

	//User input and checking if username and password are unique to continue the register proccess
	cout << "- - - Username And Password - - -" << endl;
	string username, password;
	do
	{
		cout << "Enter username: ";
		cin >> username;
		cout << "Enter password: ";
		cin >> password;
		cout << endl;
		bool exists = CheckIfUserExists(username, password);
		if(exists == 0)
		{
			break;
		}

	} while (true);

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

bool CheckIfUserExists(string username, string password)
{
	bool exists = false;
	string fileText;
	string fileUsername, filePassword;
	//Read From The Users Info File
	ifstream ReadUserInfo("usersInfo.txt");
	//Looping through the info
	while (getline(ReadUserInfo, fileText))
	{
		int lenOfUsername = fileText.find(' ');
		fileUsername = fileText.substr(0, lenOfUsername);
		filePassword = fileText.substr(lenOfUsername + 1);
		if (username == fileUsername)
		{
			cout << "This username is already in use! Please choose another one!"<<endl;
			exists = true;
			break;
		}
		else if (password == filePassword)
		{
			cout << "This password is already taken! Please choose another password!"<<endl;
			exists = true;
			break;
		}
	}
	ReadUserInfo.close();
	return exists;
}