#ifndef OPTION
#define OPTION

#ifndef FUNCTIONCODE
#define FUNCTIONCODE

typedef enum
{
	Nullf,
	MainMenu_adminLogin,
	MainMenu_studentLogin,
	MainMenu_exit,
	AdminMenu_addStudent,
	AdminMenu_deleteStudent,
	AdminMenu_viewTable,
	AdminMenu_mainMenu,
	AdminMenu_exit,
	StudentMenu_viewTable,
	StudentMenu_mainMenu,
	StudentMenu_exit
} Functions;

#endif

#include<string>

class Option
{
private:
	string name;
	int _runCode;
public:
	Option();
	Option(int runCode);
	Option(int runCode, string name);
	void run();
	void setRun(int runCode);
	string getName();
	void setName(string name);
};

#endif