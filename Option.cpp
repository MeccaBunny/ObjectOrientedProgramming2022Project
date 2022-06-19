#include<iostream>
#include<string>
using namespace std;

#include"Functions.h"
#include"Option.h"

Option::Option()
{
	name = " ";
	_runCode = Nullf;
}

Option::Option(int runCode)
{
	name = " ";
	_runCode = runCode;
}

Option::Option(int runCode, string name)
{
	_runCode = runCode;
	this->name = name;
}

void Option::run() // Run the function distinguished by the identifier.
{
	switch (_runCode)
	{
	case MainMenu_adminLogin:
		mainMenu_adminLogin();
		break;
	case MainMenu_studentLogin:
		mainMenu_studentLogin();
		break;
	case MainMenu_exit:
		mainMenu_exit();
		break;
	case AdminMenu_addStudent:
		adminMenu_addStudent();
		break;
	case AdminMenu_deleteStudent:
		adminMenu_deleteStudent();
		break;
	case AdminMenu_viewTable:
		adminMenu_viewTable();
		break;
	case AdminMenu_mainMenu:
		adminMenu_mainMenu();
		break;
	case AdminMenu_exit:
		adminMenu_exit();
		break;
	case StudentMenu_viewTable:
		studentMenu_viewTable();
		break;
	case StudentMenu_mainMenu:
		studentMenu_mainMenu();
		break;
	case StudentMenu_exit:
		studentMenu_exit();
		break;
	default:
		cout << "wrong runCode error" << endl;
	}
}

void Option::setRun(int runCode)
{
	_runCode = runCode;
}

string Option::getName()
{
	return name;
}
void Option::setName(string name)
{
	this->name = name;
}