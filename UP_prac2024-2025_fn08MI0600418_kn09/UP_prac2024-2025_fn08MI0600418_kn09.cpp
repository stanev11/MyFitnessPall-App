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

//Fill Vector With Users
void FillUsers(vector<vector<string>>& users)
{
	string fileText;
	string currentData;
	vector<string> currentUser;

	//Open File Stream
	ifstream UsersInfo("usersInfo.txt");
	
	//Looping through the info
	while (getline(UsersInfo, fileText))
	{
		currentUser = {};
		int startIndex = 0;
		while (true)
		{
			size_t index = fileText.find(',', startIndex);
			currentData = fileText.substr(startIndex, index - startIndex);
			startIndex = index + 1;

			currentUser.push_back(currentData);
			if (index == -1) break;
		}
		users.push_back(currentUser);
	}

	//Closing File Stream
	UsersInfo.close();
}

//1 - Register or log-in window
void RegisterOrLogIn(vector<vector<string>>& users);

//1.1 - Log-in Window
void LogInWindow(vector<vector<string>> users);

//1.2 - Register Window
void RegisterWindow(vector<vector<string>>& users);

//Create Profile
vector<string> CreateProfile(string username, string password, int age, bool gender, double height, double weight, int levelOfActiveness, int goal, double kgToGainOrLose, vector<vector<string>>& users);

//Checking if a user has profile
bool CheckIfUserExists(string username, vector<vector<string>> users, string password = "");

// - - - Small Functions To Get Parameters - - -

//Get Unique Username
string GetUsername(vector<vector<string>> users,bool checkAccount = 0)
{
	string username;
	bool exists = false;
	do
	{
		cout << "Enter username: ";
		cin >> username;
		exists = CheckIfUserExists(username,users);
		if (!exists)
		{
			if (!checkAccount) break;
			cout << "Incorrect username!"<<endl;
		}
		else if (exists)
		{
			if (checkAccount) break;
			cout << "This username is already in use! Please choose another one!" << endl;
		}

	} while (true);
	return username;
}

//Get Password
string GetPassword(bool checkAccount=0)
{
	const int MIN_SIZE = 5;
	string password;
	do
	{
		cout << "Enter password: ";
		cin >> password;
		cout << endl;
		if (password.length() < MIN_SIZE && !checkAccount) cout << "Too short password! Please try again!"<<endl;
		else break;
	} while (true);
	return password;
}

//Get Age Of User - Min Age 10
int GetAge()
{
	const int MIN_AGE = 10;
	const int MAX_AGE = 100;
	int age;
	do
	{
		cout << "Age : ";
		cin >> age;
		cout << endl;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000000,'\n');
			cout << "Invalid input!";
		}
		else if (age < MIN_AGE || age>MAX_AGE)
		{
			cout << "Please enter age in between 10 and 100!";
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
			cin.ignore(1000000, '\n');
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
	const double MAX_HEIGHT = 225;
	const double EPSILON = 0.0000000;
	double height;
	do
	{
		cout << "Height : ";
		cin >> height;
		cout << endl;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000000, '\n');
			cout << "Invalid input!";
		}
		else if (height - MIN_HEIGHT < EPSILON || height-MAX_HEIGHT > EPSILON) cout << "Invalid height!";
		else break;
	} while (true);
	return height;
}

//Get Weight
double GetWeight()
{
	const double MIN_WEIGHT = 50;
	const double MAX_WEIGHT = 250;
	const double EPSILON = 0.0000000;
	double weight;
	do
	{
		cout << "Weight : ";
		cin >> weight;
		cout << endl;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000000, '\n');
			cout << "Invalid input!";
		}
		else if (weight - MIN_WEIGHT < EPSILON || weight - MAX_WEIGHT > EPSILON) cout << "Invalid weight!";
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
		cout << "1 - Not Active" << endl;
		cout << "2 - Not very active"<<endl;
		cout << "3 - Slightly Active" << endl;
		cout << "4 - Active" << endl;
		cout << "5 - Very Active" << endl;
		cout << "What is your level of activeness? : ";
		cin >> option;
		cout << endl;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000000, '\n');
			cout << "Invalid input!";
		}
		else if (option<1 || option>5) cout << "Invalid choice!";
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
			cin.ignore(1000000, '\n');
			cout << "Invalid input!";
		}
		else if (goal<1 || goal>3) cout << "Invalid choice!";
		else break;
	} while (true);
	return goal;
}

//Get Kilos To Gain Or Lose
double GetKgToGainOrLose(int goal)
{
	const double MAX = 10;
	const double MIN = 0;
	const double EPSILON = 0.0000000;
	double kg;
	do
	{
		cout << "How much kg you want to ";
		(goal == 1) ? cout<<"lose": cout<<"gain";
		cout <<" per week?"<< endl;
		cin >> kg;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000000, '\n');
			cout << "Invalid input!";
		}
		else if (kg-MIN<EPSILON|| kg-MAX>EPSILON) cout << "Please enter kilos between 0 and 10!"<<endl;
		else break;
	} while (true);
	return kg;
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
			cin.ignore(1000000, '\n');
			cout << "Invalid input!";
		}
		else if (type != 1 && type != 2) cout << "Invalid choice!";
		else break;
	} while (true);
	return type;
}

//Find Account
vector<string> FindAccount(vector<vector<string>> users, string username);
//0 Control Function
void StartProgram()
{
	vector<vector<string>> users;
	FillUsers(users);
	//1 - Register or log-in window
	RegisterOrLogIn(users);
	//2 - Program Menu

}
//Exit Program
void ExitProgram()
{
	cout << "Have a nice day!";
	exit(1);
}

int main()
{
	StartProgram();
}
//Register or log-in window
void RegisterOrLogIn(vector<vector<string>>& users)
{
	cout << "- - - Welcome to myfitnesspal! - - -" << endl << endl;
	do
	{
		cout << "Please choose option" << endl;
		cout << "1. Log in"<<endl;
		cout << "2. Sign up"<<endl;
		cout << "3. Exit" << endl;
		cout << "Choice: ";
		int option;
		cin >> option;
		if (cin.fail() || (option != 1 && option != 2 && option != 3))
		{
			cin.clear();
			cin.ignore(100000,'\n');
			cout << "Invalid choice!" << endl;
		}

		else if (option == 1)
		{
			LogInWindow(users);
			break;
		}
		else if (option == 2)
		{
			RegisterWindow(users);
			break;
		}
	} while (true);
}

//Log In Window
void LogInWindow(vector<vector<string>> users)
{
	cout << "- - - Log In Form - - -" << endl;
	string username, password;
	bool exists;
	do
	{
		username = GetUsername(users,true);
		password = GetPassword();
		exists = CheckIfUserExists(username, users,password);
		if (!exists) cout << "Invalid password!"<<endl;
	} while (!exists);
	vector<string> account = FindAccount(users, username);
}

//Create profile
vector<string> CreateProfile(string username,string password,int age,bool gender,double height,double weight,int levelOfActiveness,int goal,vector<vector<string>>& users)
vector<string> CreateProfile(string username,string password,int age,bool gender,double height,double weight,int levelOfActiveness,int goal,double kgToGainOrLose,vector<vector<string>>& users)
{
	vector<string> account;
	account.push_back(username);
	account.push_back(password);
	account.push_back(to_string(age));
	account.push_back(to_string(gender));
	account.push_back(to_string(height));
	account.push_back(to_string(weight));
	account.push_back(to_string(levelOfActiveness));
	account.push_back(to_string(goal));

	ofstream WriteInFile("usersInfo.txt",ios::app);
	string user = username + " " + password + " " + to_string(age) + " " + to_string(gender)
		+ " " + to_string(height) + " " + to_string(weight) + " " + to_string(levelOfActiveness) + " " + to_string(goal)+" "+to_string(kgToGainOrLose);
	WriteInFile << user << endl;
	WriteInFile.close();

	cout << "- Successfully created a profile! -"<<endl;
	return account;
}

//Register Window
void RegisterWindow(vector<vector<string>>& users)
{
	cout << "- - - Registration Form - - -" << endl << endl;

	//User input and checking if username is unique to continue the register proccess
	cout << "- - - Username And Password - - -" << endl;	
	string username = GetUsername(users,false);
	string password = GetPassword();
	//User input about physical parameters
	cout << "- - - Parameters - - -"<<endl;
	unsigned int age = GetAge();
	bool gender = GetGender();
	double height = GetHeight();
	double weight = GetWeight();
	int levelOfActiveness = GetActiveness();
	int goal = GetGoal();
	double kgToGainOrLose = (goal==2)? 0 : GetKgToGainOrLose(goal);
	
	//Type Of Account
	int typeOfAccount = GetTypeOfAccount();

	vector<string> account=CreateProfile(username, password, age, gender, height, weight, levelOfActiveness, goal,kgToGainOrLose,users);
	users.push_back(account);
	LoadMenu(account);
}

//Check If User Already Exists
bool CheckIfUserExists(string username, vector<vector<string>> users, string password)
{
	bool existMessage=0;
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i][0] == username)
		{
			existMessage = 1;
			if (password.empty()) break;
			if (users[i][1] != password)
			{
				existMessage = 0;
			}
		}
	}
	return existMessage;
}

//Find Account
vector<string> FindAccount(vector<vector<string>> users, string username)
{
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i][0] == username) return users[i];
	}
	vector<string> user = {};
	return user;
}
