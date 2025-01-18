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
vector<string> CreatePlan(string username, char* fileName, string descrp, int typeOfAccount=0, double dailyCal=0);

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

//Get Today's Date
string GetDate()
{
	const int MAX_SIZE = 1000;
	char date[MAX_SIZE];
	time_t t = time(nullptr);
	tm timePtr[100];
	localtime_s(timePtr, &t);
	strftime(date, sizeof(date), "%d.%m.%Y", timePtr);
	return date;
}

//2 - Program Menu
void LoadMenu(vector<string>& account, vector<string>& mealPlan,vector<string>& trainingPlan);

//Find Account
vector<string> FindAccount(string username);

//Find Meal/Training Plan
vector<string> FindPlan(vector<vector<string>> plans, string username);

//  - - - Small functions about menu - - -
//Add Meal
void AddData(string username, vector<string>& plan,string descrp);

void RepeatChar(char ch, int times)
{
	while (times != 0)
	{
		cout << ch << " ";
		times--;
	}
	cout << endl;
}

//Welcome Back Words / Top Menu
void WelcomeBackWords(string username)
{
	RepeatChar('-', 25);
	cout << "Hi, " << username << " !" << endl;
	cout << "How are you doing today!" << endl;
	RepeatChar('-', 25);
}

//Display Trainings/ Meals
void DisplayPlans(vector<string> plan, string date, double& cals,string descrp)
{
	RepeatChar('-', 25);
	cout << descrp<<" Today" << endl;

	string currentRecord;
	string currentDate;

	for (int i = 0; i < plan.size(); i++)
	{
		currentRecord = plan[i];
		size_t ind = currentRecord.find(',');
		currentDate = currentRecord.substr(0, ind);
		if (currentDate == date)
		{
			ind = currentRecord.find_last_of(',');
			cals += stod(currentRecord.substr(ind + 1));
			cout << currentRecord << endl;
			
		}
	}
}

//Summary Goal/Burnt/Eaten Calories
void SummaryCals(double calGoal,double calEaten,double burntCals)
{
	RepeatChar('-', 25);
	cout << "Calories Goal: " << calGoal << endl;
	cout << "Calories eaten: " << calEaten << endl;
	cout << "Calories burnt: " << burntCals << endl;
	cout << "Remaining Calories: " << calGoal - calEaten + burntCals << endl;
}

//Bottom Menu / Choosing Option
//Validate User Input Option
int GetInputOption()
{
	int n;
	do
	{
		cin >> n;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Invalid Option!" << endl;
		}
		else if (n < 1 || n>8) cout << "Enter number between 1 and 8!"<<endl;
		else break;
	} while (true);
	return n;
}

//Options
void GetContextMenuOptions()
{
	RepeatChar('-', 25);
	cout << "1) Add Meal\n2) Add Training.\n3) Edit Meal For Today.\n4) Edit training for today.\n";
	RepeatChar('-', 25);
	cout << "5) Get Report For Specific Date\n6) Edit profile\n7) Log Out\n8) Exit Program\n";
	cout << "You can choose one of these options.\n";
}
void BotttomMenuOptions(vector<string>& account, vector<string>& mealPlan, vector<string>& trainingPlan)
{
	GetContextMenuOptions();
	int n=GetInputOption();
	string username = account[0];
	if (n == 1) //Add Meal
	{
		AddData(username, mealPlan,"food");
	}
//Get Food/Training Name And Calories
string GetName(string descrp)
{
	string name;
	do
	{
		cout << "Enter "<<descrp<<" name: ";
		cin >> ws; //check that 
		getline(cin,name);
		if (name.size() == 0) cout << "Invalid Name!"<<endl;
	} while (name.size()==0);
	return name;
}
double GetCals()
{
	const double MIN_CALS = 0;
	const double MAX_CALS = 5000;
	const double EPSILON = 0.00000;
	double cals;
	do
	{
		cout << "Enter calories: ";
		cin >> cals;
		if (cin.fail())
		{
			cout << "Invalid Option!" << endl;
			cin.clear();
			cin.ignore(10000, '\n');
		}
		else if (cals - MIN_CALS > EPSILON && cals - MAX_CALS < EPSILON) break;
		else cout << "Enter calories between " << MIN_CALS << " and " << MAX_CALS;
	} while (true);
	return cals;
}

//Add Meal
void AddData(string username, vector<string>& plan,string descrp)
{
	string name=GetName(descrp);
	double cals = GetCals();
	string date = GetDate();

	string infoToAppend = date + "," + name + "," + to_string(cals);
	plan.push_back(infoToAppend);
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

	vector<string> account = FindAccount(username);
	vector<string> mealPlan = FindPlan(mealPlans,username);
	vector<string> trainingPlan = FindPlan(trainingPlans, username);
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

	if (!WriteInFileUsersInfo.is_open())
	{
		cout << "Error! Couldn't open file!";
		return {};
	}

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
	vector<string> plan;
	plan.push_back(username);
	if (descrp == "meal")
	{
		plan.push_back(to_string(dailyCal));
		plan.push_back(to_string(typeOfAccount));
	}

	ofstream TrackerFile(fileName, ios::app);

	if (!TrackerFile.is_open())
	{
		cout << "Error! Couldn't open file!";
		return {};
	}

	string infoToAppend = username;
	if(descrp=="meal") infoToAppend+="\n" + to_string(dailyCal) + "\n" + to_string(typeOfAccount);
	TrackerFile << infoToAppend << endl<<"*"<<endl;
	TrackerFile.close();

	cout << "- Successfully created "<<descrp<<" plan, based on your data!- " << endl;
	Sleep(1500); //
	return plan;
}

//Register Window
void RegisterWindow()
{
	cout << "- - - Registration Form - - -" << endl << endl;

	//User input and checking if username is unique to continue the register proccess
	cout << "- - - Username And Password - - -" << endl;	
	string username = GetUsername(false);
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
	char mealsFile[] = "mealsTracker.txt";
	double dailyCal = CalculateDailyCalories(age, gender, height, weight, levelOfActiveness, goal, kgToGainOrLose);	
	vector<string> mealPlan = CreatePlan(username,mealsFile,"meal", typeOfAccount, dailyCal);
	mealPlans.push_back(mealPlan);

	//Training plan
	char trainingsFile[] = "trainingsTracker.txt";
	vector<string> trainingPlan = CreatePlan(username,trainingsFile,"training");

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

//Find Meal/Training Plan
vector<string> FindPlan(vector<vector<string>> plans, string username)
{
	for (int i = 0; i < plans.size(); i++)
	{
		if (plans[i][0] == username) return plans[i];
	}
	vector<string> plan = {};
	return plan;
}

//Check If Account Is Empty
bool CheckIfAccountIsEmpty(vector<string>& account)
{
	if (account.empty())
	{
		cout << "Sorry! This account doesn't exist or a problem occured!";
		return true;
	}
	return false;
}
//Load Main Menu
void LoadMenu(vector<string>& account, vector<string>& mealPlan,vector<string>& trainingPlan)
{
	if (CheckIfAccountIsEmpty(account)) return;

	string username = account[0];

	//Top Menu / Welcome Words
	WelcomeBackWords(username);
	
	//Getting string formatted date of today.
	string date=GetDate();

	//Calories
	double calEaten = 0;
	double calGoal = stod(mealPlan[1]);
	double burntCals = 0;

	//Displaying Some Info About Meals For Today
	DisplayPlans(mealPlan, date, calEaten,"Meals");

	//Display Trainings
	DisplayPlans(trainingPlan, date, burntCals,"Trainings");

	//Summary of eaten/burnt/goal calories
	SummaryCals(calGoal, calEaten,burntCals);

	//Bottom Menu Options
	BotttomMenuOptions(account,mealPlan,trainingPlan);
}

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