#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

#include"Menu.h"
#include"Functions.h"
#include"Option.h"

Menu mainMenu;
Menu adminMenu;
SecuredMenu studentMenu;

int init()
{
	mainMenu.setReadText("Available Login operations:");
	adminMenu.setReadText(" - Logged in as Admin - ");
	studentMenu.setReadText(" - Logged in as Student - ");

	Option mainMenu_adminLogin(MainMenu_adminLogin, "Admin Login");
	Option mainMenu_studentLogin(MainMenu_studentLogin, "Student Login");
	Option mainMenu_exit(MainMenu_exit, "Exit");
	mainMenu.append(mainMenu_adminLogin);
	mainMenu.append(mainMenu_studentLogin);
	mainMenu.append(mainMenu_exit);

	Option adminMenu_addStudent(AdminMenu_addStudent, "Add Students");
	Option adminMenu_deleteStudent(AdminMenu_deleteStudent, "Delete Students");
	Option adminMenu_viewTable(AdminMenu_viewTable, "View Table");
	Option adminMenu_mainMenu(AdminMenu_mainMenu, "Main Menu");
	Option adminMenu_exit(AdminMenu_exit, "Exit");
	adminMenu.append(adminMenu_addStudent);
	adminMenu.append(adminMenu_deleteStudent);
	adminMenu.append(adminMenu_viewTable);
	adminMenu.append(adminMenu_mainMenu);
	adminMenu.append(adminMenu_exit);

	Option studentMenu_viewTable(StudentMenu_viewTable, "View Table");
	Option studentMenu_mainMenu(StudentMenu_mainMenu, "Main Menu");
	Option studentMenu_exit(StudentMenu_exit, "Exit");
	studentMenu.append(studentMenu_viewTable);
	studentMenu.append(studentMenu_mainMenu);
	studentMenu.append(studentMenu_exit);

	mainMenu.run();
	return 0;
}

int nullf()
{
	return 0;
}

int mainMenu_adminLogin()
{
	ifstream fin("Login.txt");
	if (!fin.is_open())
	{
		cout << "'Login.txt'is not opened.";
		mainMenu.run();
		return 0;
	}
	string id = "Admin";
	string line;
	bool found = false;
	string adminPassword;
	string adminName;
	string adminDepartment;
	while (!fin.eof())
	{
		getline(fin, line);
		for (int i = 0; i < id.size(); i++)
		{
			if (line[i] != id[i])
				break;
			if (i == id.size() - 1)
			{
				if (line[id.size()] != ' ')
					break;
				for (int i = id.size() + 1; line[i] != ' '; i++)
					adminPassword.push_back(line[i]);
				for (int i = id.size() + adminPassword.size() + 2; line[i] != ' '; i++)
					adminName.push_back(line[i]);
				for (int i = id.size() + adminPassword.size() + adminName.size() + 3; line[i] != ' '; i++)
					adminDepartment.push_back(line[i]);

				cout << "password: ";
				string getPassword;
				cin >> getPassword;
				if (getPassword.compare(adminPassword) == 0)
				{
					cout << "Login Complete." << endl;
					fin.close();
					adminMenu.run();
					return 1;
				}
				else
				{
					cout << "Login failed." << endl;
					fin.close();
					mainMenu.run();
					return 0;
				}
			}
		}
	}
	cout << "Admin doesn't exist." << endl;
	fin.close();
	mainMenu.run();
	return 0;
}
int mainMenu_studentLogin()
{
	ifstream fin("Login.txt");
	if (!fin.is_open())
	{
		cout << "'Login.txt'is not opened.";
		mainMenu.run();
		return 0;
	}

	cout << "ID : ";
	string id;
	cin >> id;

	if (id == "Admin")
	{
		cout << "You cannot Login as a Admin." << endl;
		fin.close();
		mainMenu.run();
		return 0;
	}

	string line;
	bool found = false;
	string password;
	string studentPassword;
	string studentName;
	string studentDepartment;
	while (!fin.eof())
	{
		getline(fin, line);
		for (int i = 0; i < id.size(); i++)
		{
			if (line[i] != id[i])
				break;
			if (i == id.size() - 1)
			{
				if (line[id.size()] != ' ')
					break;
				for (int i = id.size() + 1; line[i] != ' '; i++)
					studentPassword.push_back(line[i]);
				for (int i = id.size() + studentPassword.size() + 2; line[i] != ' '; i++)
					studentName.push_back(line[i]);
				for (int i = id.size() + studentPassword.size() + studentName.size() + 3; line[i] != ' '; i++)
					studentDepartment.push_back(line[i]);

				cout << "password: ";
				string getPassword;
				cin >> getPassword;
				if (getPassword.compare(studentPassword) == 0)
				{
					cout << "Login Complete." << endl;
					string studentMenu_readText = " - Logged in as " + studentName + " - ";
					studentMenu.setReadText(studentMenu_readText);
					fin.close();
					studentMenu.setID(id);
					studentMenu.setName(studentName);
					studentMenu.run();
					return 1;
				}
				else
				{
					cout << "Login failed." << endl;
					fin.close();
					mainMenu.run();
					return 0;
				}
			}
		}
	}
	cout << "ID doesn't exist." << endl;
	fin.close();
	mainMenu.run();
	return 0;
}
int mainMenu_exit()
{
	return 0;
}

int adminMenu_addStudent()
{
	ifstream fin("Login.txt");
	if (!fin.is_open())
	{
		cout << "'Login.txt'is not opened.";
		mainMenu.run();
		return 0;
	}
	string line;
	vector<string> infoList;
	while (!fin.eof())
	{
		getline(fin, line);
		infoList.push_back(line);
	}
	infoList.pop_back();

	cout << "Student ID : ";
	string studentID;
	cin >> studentID;
	cout << "Student password : ";
	string studentPassword;
	cin >> studentPassword;
	cout << "Student name : ";
	string studentName;
	cin >> studentName;
	cout << "Student department : ";
	string studentDepartment;
	cin >> studentDepartment;
	string setData;
	setData = studentID + " " + studentPassword + " " + studentName + " " + studentDepartment + " ";
	infoList.push_back(setData);

	fstream fout("Login.txt");
	if (fout.is_open())
	{
		for (int i = 0; i < infoList.size(); i++)
			fout << infoList[i] << endl;
	}
	fin.close();
	fout.close();
	adminMenu.run();
	return 0;
}
int adminMenu_deleteStudent()
{
	ifstream fin("Login.txt");
	if (!fin.is_open())
	{
		cout << "'Login.txt'is not opened.";
		mainMenu.run();
		return 0;
	}
	string line;
	vector<string> infoList;
	while (!fin.eof())
	{
		getline(fin, line);
		infoList.push_back(line);
	}
	infoList.pop_back();
	infoList.pop_back();
	fin.close();
	remove("Login.txt");

	ofstream fout("Login.txt");
	if (fout.is_open())
	{
		for (int i = 0; i < infoList.size(); i++)
			fout << infoList[i] << endl;
	}
	fout.close();
	adminMenu.run();
	return 0;

}
int adminMenu_viewTable()
{
	ifstream fin("Login.txt");
	if (!fin.is_open())
	{
		cout << "'Login.txt'is not opened.";
		mainMenu.run();
		return 0;
	}
	string line;
	vector<string> infoList;
	while (!fin.eof())
	{
		getline(fin, line);
		infoList.push_back(line);
	}
	for (int i = 0; i < infoList.size(); i++)
	{
		cout << infoList[i] << endl;
	}
	fin.close();
	adminMenu.run();
	return 0;
}
int adminMenu_mainMenu()
{
	mainMenu.run();
	return 0;
}
int adminMenu_exit()
{
	return 0;
}

int studentMenu_viewTable()
{
	ifstream fin("Login.txt");
	if (!fin.is_open())
	{
		cout << "'Login.txt'is not opened.";
		mainMenu.run();
		return 0;
	}
	string menuID = studentMenu.getID();
	string menuName = studentMenu.getName();
	string line = " ";
	string studentID;
	string studentPassword;
	string studentName;
	while (!fin.eof())
	{
		getline(fin, line);
		studentID = "";
		studentPassword = "";
		studentName = "";
		for (int i = 0; line[i] != ' '; i++)
			studentID.push_back(line[i]);
		for (int i = studentID.size() + 1; line[i] != ' '; i++)
			studentPassword.push_back(line[i]);
		for (int i = studentID.size() + studentPassword.size() + 2; line[i] != ' '; i++)
			studentName.push_back(line[i]);
		if ((studentID == studentMenu.getID()) && (studentName == studentMenu.getName()))
		{
			cout << line << endl;
			break;
		}
	}
	fin.close();
	studentMenu.run();
	return 0;
}
int studentMenu_mainMenu()
{
	studentMenu.setID(" ");
	studentMenu.setName(" ");
	mainMenu.run();
	return 0;
}
int studentMenu_exit()
{
	return 0;
}
