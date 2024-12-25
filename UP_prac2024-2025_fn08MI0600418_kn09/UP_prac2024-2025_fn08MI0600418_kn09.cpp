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

int main()
{
	//����������� ��� ���� �� ����������
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
		char option;
		cin >> option;
		if (option-'0' == 1)
		{
			LogInWindow();
			break;
		}
		else if(option- '0' == 2)
		{
			RegisterWindow();
			break;
		}
		else
		{
			cout << "! Invalid choice !"<<endl;
		}
	} while (true);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
