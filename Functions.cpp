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

int init() //This function design the relations between Menu and Option. Also set the inital menu state.
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

int nullf() //Null function
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
	string id = "Admin"; // ID of the administrator is fixed.
	string line;
	string adminPassword;
	string adminName;
	string adminDepartment;
	while (!fin.eof())
	{
		getline(fin, line);
		for (int i = 0; i < id.size(); i++)
		{
			if (line[i] != id[i]) // Detect ID of the admin in Login.txt
				break;
			if (i == id.size() - 1) // ID of the admin is found.
			{
				if (line[id.size()] != ' ') // Name of the student could include 'Admin' such as 'Admini'. From such case, find the Admin's ID.
					break;
				//Login.txt holds every information about the user. For example, 'Admin 1234 PYJ IRE '.
				//Code down below find administrator's ID, Password, Name, Department from the given information.
				for (int i = id.size() + 1; line[i] != ' '; i++) 
					adminPassword.push_back(line[i]);
				for (int i = id.size() + adminPassword.size() + 2; line[i] != ' '; i++)
					adminName.push_back(line[i]);
				for (int i = id.size() + adminPassword.size() + adminName.size() + 3; line[i] != ' '; i++)
					adminDepartment.push_back(line[i]);
				//

				//Code down below compares user entered password with password written in Login.txt. After than, Operate the nessary code.
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
				//
			}
		}
	}
	// if administrator's ID is not found until the end of the file, go to mainMenu.
	cout << "Admin doesn't exist." << endl;
	fin.close();
	mainMenu.run();
	return 0;
}
int mainMenu_studentLogin() // Code to login in for student is simular to Admin's login.
{
	ifstream fin("Login.txt");
	if (!fin.is_open())
	{
		cout << "'Login.txt'is not opened.";
		mainMenu.run();
		return 0;
	}

	// StudentID varys per number of student. So recieving ID is required to Login for student.
	cout << "ID : ";
	string id;
	cin >> id;

	// If User entered ID is same as Administrator, send warning and go to mainMenu.
	if (id == "Admin")
	{
		cout << "You cannot Login as a Admin." << endl;
		fin.close();
		mainMenu.run();
		return 0;
	}

	string line;
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
					// To appropriately search user information in further code, studentMenu should have the information about the user.
					// class SecuredMenu which inherit class Menu could have the information about user's ID and user's name.
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
int mainMenu_exit() // If the function called by the operator doesn't call the next menu, program ends.
{
	return 0;
}

int adminMenu_addStudent() // Add student to Login.txt
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

	// Recieve student information entered by user.
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
	setData = studentID + " " + studentPassword + " " + studentName + " " + studentDepartment + " "; //Merge given information in to format.
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
int adminMenu_deleteStudent() //Delete student from Login.txt
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
int adminMenu_viewTable() // Show Login.txt
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
int adminMenu_mainMenu() // Go to mainMenu;
{
	mainMenu.run();
	return 0;
}
int adminMenu_exit()
{
	return 0;
}

int studentMenu_viewTable() // Search user information from Login.txt using data given when Logged in and shows the user's information.
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
