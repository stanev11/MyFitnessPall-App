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
//This project is designed for everyone who wants to track his / her daily calories and trainings.


#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

//Global Variables
vector<vector<string>> users;
vector<vector<string>> trainingPlans;
vector<vector<string>> mealPlans;

//Fill Vectors With Data
void FillPlans(vector<vector<string>>& plans,string filename)
{
	ifstream MyFile(filename);
	string currentData;
	vector<string> currentPlan;

	if (!MyFile.is_open())
	{
		cout << "Error! Couldn't open file!";
		return;
	}

	while (getline(MyFile, currentData))
	{
		if (currentData == "") break;
		currentPlan = {};
		while (!MyFile.eof() && currentData!="*")
		{
			if(currentData!="*") currentPlan.push_back(currentData);
			getline(MyFile, currentData);
		}
		if (!currentPlan.empty())
		{
			plans.push_back(currentPlan);
		}
	}
	MyFile.close();
}
void FillUsers(vector<vector<string>>& users)
{
	string fileText;
	string currentData;
	vector<string> currentUser;

	//Open File Stream
	ifstream UsersInfo("usersInfo.txt");

	if (!UsersInfo.is_open())
	{
		cout << "Error! Couldn't open file!";
		return;
	}
	
	//Looping through the info
	while (getline(UsersInfo, fileText))
	{
		currentUser = {};
		size_t startIndex = 0;
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
void RegisterOrLogIn();

//1.1 - Log-in Window
void LogInWindow();

//1.2 - Register Window
void RegisterWindow();

//Create Profile
vector<string> CreateProfile(string username, string password, int age, bool gender, double height, double weight, int levelOfActiveness, int goal, double kgToGainOrLose,int typeOfAccount);

//Calculate Recommended Calorie Intake A Day
double CalculateDailyCalories(int age, bool gender, double height, double weight, int levelOfActiveness, int goal,double kgToGainOrLose);
double CaloriesForMaintenance(bool gender,int age,double weight,double height,int levelOfActiveness);
double CalorieDeficitOrSurplus(int goal,double kgToGainOrLose);

//Calculate Macronutrients
void CalculateMacros(int goal,double dailyCal,double macros[3]);

//Create Food Plan
vector<string> CreateMealPlan(string username, int typeOfAccount, double dailyCal);

//Create Training Plan
vector<string> CreateTrainingPlan(string username);

//Checking if a user has profile
bool CheckIfUserExists(string username, string password = "");

// - - - Small Functions To Get Parameters - - -

//Get Unique Username
string GetUsername(bool checkAccount = 0)
{
	string username;
	bool exists = false;
	do
	{
		cout << "Enter username: ";
		cin >> username;
		exists = CheckIfUserExists(username);
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

//2 - Program Menu
void LoadMenu(vector<string>& account, vector<string>& mealPlan,vector<string>& trainingPlan);

//Find Account
vector<string> FindAccount(string username);

//Find Food Plan
vector<string> FindMealPlan(vector<vector<string>> meals,string username);

//  - - - Small functions about menu - - -
void RepeatChar(char ch, int times)
{
	while (times != 0)
	{
		cout << ch << " ";
		times--;
	}
	cout << endl;
}

//0 Control Function
void StartProgram()
{
	//Fill Both Vectors With Data
	FillUsers(users);
	FillPlans(mealPlans,"mealsTracker.txt");
	FillPlans(trainingPlans, "trainingsTracker.txt");

	//1 - Register or log-in window
	RegisterOrLogIn();

	//2 -Load Menu

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
void RegisterOrLogIn()
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
			LogInWindow();
			break;
		}
		else if (option == 2)
		{
			RegisterWindow();
			break;
		}
		else ExitProgram();
	} while (true);
}

//Log In Window
void LogInWindow()
{
	cout << "- - - Log In Form - - -" << endl;
	string username, password;
	bool exists;
	do
	{
		username = GetUsername(true);
		password = GetPassword();
		exists = CheckIfUserExists(username,password);
		if (!exists) cout << "Invalid password!"<<endl;
	} while (!exists);
	vector<string> account = FindAccount(users, username);
	vector<string> mealPlan = FindMealPlan(meals,username);
	LoadMenu(account,mealPlan);
}

//Create profile
vector<string> CreateProfile(string username,string password,int age,bool gender,double height,double weight,int levelOfActiveness,int goal,double kgToGainOrLose,int typeOfAccount)
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

	ofstream WriteInFileUsersInfo("usersInfo.txt",ios::app);
	string user = username + "," + password + "," + to_string(age) + "," + to_string(gender)
		+ "," + to_string(height) + "," + to_string(weight) + "," + to_string(levelOfActiveness) + "," + to_string(goal)+","+to_string(kgToGainOrLose);
	WriteInFileUsersInfo << user << endl;
	WriteInFileUsersInfo.close();

	cout << "- Successfully created a profile! -"<<endl;
	return account;
}

//Create Meal
vector<string> CreatePlan(string username,char* fileName,string descrp, int typeOfAccount, double dailyCal)
{
	vector<string> mealPlan;
	mealPlan.push_back(username);
	mealPlan.push_back(to_string(dailyCal));
	mealPlan.push_back(to_string(typeOfAccount));

	ofstream TrackerFile("mealsTracker.txt", ios::app);
	string infoToAppend = username + "\n" + to_string(dailyCal) + "\n" + to_string(typeOfAccount);
	TrackerFile << infoToAppend << endl<<"*"<<endl;
	TrackerFile.close();

	cout << "- Successfully created meal plan, based on your data! -" << endl;
	return mealPlan;
}

//Create Training Plan
vector<string> CreateTrainingPlan(string username)
{
	vector<string> trainingPlan;
	trainingPlan.push_back(username);

	ofstream TrackerFile("trainingsTracker.txt", ios::app);
	string infoToAppend = username;
	TrackerFile << infoToAppend << endl << "*" << endl;
	TrackerFile.close();

	cout << "- Successfully created training plan, based on your data! -" << endl;
	Sleep(1500); //
	return trainingPlan;
}

//Register Window
void RegisterWindow()
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

	//Creating the account
	vector<string> account=CreateProfile(username, password, age, gender, height, weight, levelOfActiveness, goal,kgToGainOrLose,typeOfAccount);
	users.push_back(account);

	//Meal plan
	double dailyCal = CalculateDailyCalories(age, gender, height, weight, levelOfActiveness, goal, kgToGainOrLose);	
	vector<string> mealPlan = CreateMealPlan(username, typeOfAccount, dailyCal);
	meals.push_back(mealPlan);

	//Training plan
	vector<string> trainingPlan = CreateTrainingPlan(username);

	system("cls"); //Not sure if it's allowed to be used
	LoadMenu(account,mealPlan,trainingPlan);
}

//Check If User Already Exists
bool CheckIfUserExists(string username, string password)
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
vector<string> FindAccount(string username)
{
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i][0] == username) return users[i];
	}
	vector<string> user = {};
	return user;
}

//Find Meal Plan
vector<string> FindMealPlan(vector<vector<string>> meals,string username)
{
	for (int i = 0; i < meals.size(); i++)
	{
		if (meals[i][0]== username) return meals[i];
	}
	vector<string> mealPlan = {};
	return mealPlan;
}

//Load Main Menu
void LoadMenu(vector<string>& account,vector<string>& meal)
{
	if (account.empty())
	{
		cout << "Sorry! This account doesn't exist!";
		return;
	}
	string username = account[0];
	RepeatChar('-', 25);
	cout << "Hi, " << username << " !" << endl;
	cout << "How are you doing today!" << endl;
	RepeatChar('-',25);

	int calGoal=stoi(meal[1]);
	cout << "Calories Goal: " << calGoal<<endl;
	RepeatChar('-', 25);
//Calculate Recommended Calorie Intake A Day
double CalculateDailyCalories(int age, bool gender, double height, double weight, int levelOfActiveness, int goal,double kgToGainOrLose)
{
	double calForMaintenance = CaloriesForMaintenance(gender, age, weight, height, levelOfActiveness);
	double calDeficitOrSurplus = CalorieDeficitOrSurplus(goal, kgToGainOrLose);
	double dailyCalories = calForMaintenance + calDeficitOrSurplus;

	return dailyCalories;
}

double CaloriesForMaintenance(bool gender,int age, double weight, double height,int levelOfActiveness)
{
	double BMR;
	if (!gender)
	{
		const double coeff = 88.362;
		const double coeffForWeight = 13.397;
		const double coeffForHeight = 4.799;
		const double coeffForAge = 5.677;
		BMR = coeff + coeffForWeight * weight + coeffForHeight * height - coeffForAge * age;
	}
	else if (gender) 
	{
		const double coeff = 447.593;
		const double coeffForWeight = 9.247;
		const double coeffForHeight = 3.098;
		const double coeffForAge = 4.330;
		BMR = coeff + coeffForWeight * weight + coeffForHeight * height - coeffForAge * age;
	}
	if (levelOfActiveness == 1)  BMR *= 1.2;
	else if (levelOfActiveness == 2) BMR *= 1.375;
	else if (levelOfActiveness == 3) BMR *= 1.55;
	else if (levelOfActiveness == 4) BMR *= 1.725;
	else BMR *= 1.9;

	return BMR;
}
double CalorieDeficitOrSurplus(int goal, double kgToGainOrLose)
{
	const double MIN_GOAL = 0.25;
	const int MIN_CALORIES = 275;

	if (goal == 2) return 0;
	double calDefOrSur = (kgToGainOrLose / MIN_GOAL) * MIN_CALORIES;
	return (goal == 1) ? -calDefOrSur : calDefOrSur;
}

//Calculate Macros
void CalculateMacros(int goal, double dailyCal,double macros[3])
{
	double protein, fat, carbohydrates;
	//Calculate Macro Ratio
	if (goal == 1)
	{
		protein = 35 * dailyCal / 100;
		fat = 30 * dailyCal / 100;
		carbohydrates = 35 * dailyCal / 100;
	}
	else if (goal == 2)
	{
		protein = 25 * dailyCal / 100;
		fat = 30 * dailyCal / 100;
		carbohydrates = 45 * dailyCal / 100;
	}
	else
	{
		protein = 40 * dailyCal / 100;
		fat = 25 * dailyCal / 100;
		carbohydrates = 35 * dailyCal / 100;
	}
	//Into grams - CPG means calories per gram
	const int CPGFat = 9;
	const int CPGother = 4;

	protein /= CPGother;
	carbohydrates /= CPGother;
	fat /= CPGFat;

	macros[0] = protein;
	macros[1] = fat;
	macros[2] = carbohydrates;
}