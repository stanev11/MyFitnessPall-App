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

//0 Control Function
void StartProgram()
{
	//1 - Register or log-in window
	RegisterOrLogIn();

}

//1 - Register or log-in window
void RegisterOrLogIn();

//1.1 - Log-in Window
void LogInWindow();

//1.2 - Register Window
void RegisterWindow();

//Create Profile
void CreateProfile(string username, string password, int age, bool gender, double height, double weight, int levelOfActiveness, int goal);
//Checking if a user has profile
bool CheckIfUserExists(string username, string password);

// - - - Small Functions To Get Parameters - - -
//Get Age Of User - Min Age 10
int GetAge()
{
	const int MIN_AGE = 10;
	int age;
	do
	{
		cout << "Age : ";
		cin >> age;
		cout << endl;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid input!";
		}
		else if (age < MIN_AGE)
		{
			cout << "Not old enough!";
		}
		else break;
		cout << endl;
	} while (true);
	return age;
}

//Get Gender Of User
bool GetGender()
{
	bool gender;
	do
	{
		cout << "Gender (\"0\" for man / \"1\" for woman): ";
		cin >> gender;
		cout << endl;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid gender choice!";
		}
		else if (gender == 0) return 0;
		else if (gender == 1) return 1;
	} while (true);
}

//Get Height Of User
double GetHeight()
{
	const double MIN_HEIGHT = 50;
	double height;
	do
	{
		cout << "Height : ";
		cin >> height;
		cout << endl;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid input!";
		}
		else if (height - MIN_HEIGHT < 0.0000) cout << "Invalid height!";
		else break;
	} while (true);
	return height;
}

//Get Weight
double GetWeight()
{
	const double MIN_WEIGHT = 50;
	double weight;
	do
	{
		cout << "Weight : ";
		cin >> weight;
		cout << endl;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid input!";
		}
		else if (weight - MIN_WEIGHT < 0.0000) cout << "Invalid weight!";
		else break;
	} while (true);
	return weight;
}

//Get Level Of Activeness
int GetActiveness()
{
	int option;
	do
	{
		cout << "- Level of activeness -" << endl;
		cout << "1 - Not very active"<<endl;
		cout << "2 - Slightly Active" << endl;
		cout << "3 - Active" << endl;
		cout << "4 - Very Active" << endl;
		cout << "What is your level of activeness? : ";
		cin >> option;
		cout << endl;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid input!";
		}
		else if (option != 1 && option != 2 && option != 3 && option != 4) cout << "Invalid choice!";
		else break;
	} while (true);
	return option;
}

//Get Goals Of User
int GetGoal()
{
	int goal;
	do
	{
		cout << "- Choose Goal -" << endl;
		cout << "1 - Lose Weight" << endl;
		cout << "2 - Maintain Weight" << endl;
		cout << "3 - Gain Weight" << endl;
		cout << "Choose your goal : ";
		cin >> goal;
		cout << endl;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid input!";
		}
		else if (goal != 1 && goal != 2 && goal != 3) cout << "Invalid choice!";
		else break;
	} while (true);
	return goal;
}

//Get Type Of Account
int GetTypeOfAccount()
{
	int type;
	do
	{
		cout << "- Type Of Account -" << endl;
		cout << "1 - Standard" << endl;
		cout << "2 - Premium" << endl;
		cout << "Choose type of account : ";
		cin >> type;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid input!";
		}
		else if (type != 1 && type != 2) cout << "Invalid choice!";
		else break;
	} while (true);
	return type;
}

int main()
{
	StartProgram();
}
//Register or log-in window
void RegisterOrLogIn()
{
	cout << "- - - Welcome to myfitnesspal! - - -" << endl << endl;
	do
	{
		cout << "Please choose option" << endl;
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
	} while (true);
}

//Log In Window
void LogInWindow()
{
	cout << "- - - Log In Form - - -" << endl;
	string username, password;
	cout << "Username: ";
	cin >> username;
	cout << endl << "Password: ";
	cin >> password;
	bool exists = CheckIfUserExists(username);
	if (exists)
	{

	}
}

//Create profile
void CreateProfile(string username,string password,int age,bool gender,double height,double weight,int levelOfActiveness,int goal)
{
	ofstream WriteInFile("usersInfo.txt",ios::app);
	string user = username + " " + password + " " + to_string(age) + " " + to_string(gender)
		+ " " + to_string(height) + " " + to_string(weight) + " " + to_string(levelOfActiveness) + " " + to_string(goal);
	WriteInFile << user << endl;
	WriteInFile.close();
	cout << "- Successfully created a profile! -";
}

//Register Window
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

	//User input about physical parameters
	cout << "- - - Parameters - - -"<<endl;
	unsigned int age = GetAge();
	bool gender = GetGender();
	double height = GetHeight();
	double weight = GetWeight();
	int levelOfActiveness = GetActiveness();
	int goal = GetGoal();

	//Type Of Account
	int typeOfAccount = GetTypeOfAccount();

	CreateProfile(username, password, age, gender, height, weight, levelOfActiveness, goal);
}

//Check If User Already Exists
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
		int lenOfPassword = fileText.find(' ', lenOfUsername + 1)-lenOfUsername-1;
		filePassword = fileText.substr(lenOfUsername + 1,lenOfPassword);
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