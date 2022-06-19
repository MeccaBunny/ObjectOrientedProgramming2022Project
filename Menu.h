#ifndef MENU
#define MENU

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
#include<vector>
class Option;

class Menu
{
private:
	string readText;
	vector<Option> optionList;
public:
	Menu(string readText = " ") :
		readText(readText) {}
	void append(Option op);
	void setReadText(string readText);
	void run();
};

class SecuredMenu:public Menu
{
private:
	string ID;
	string name;
public:
	SecuredMenu(string readText = " ") :
		Menu(readText), ID(" "), name(" ") {};
	void setID(string id);
	void setName(string name);
	string getID();
	string getName();
};

#endif