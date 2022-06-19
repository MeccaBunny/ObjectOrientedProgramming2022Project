#ifndef FUNCTIONS
#define FUNCTIONS

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

int init();
int nullf();
int mainMenu_adminLogin();
int mainMenu_studentLogin();
int mainMenu_exit();
int adminMenu_addStudent();
int adminMenu_deleteStudent();
int adminMenu_viewTable();
int adminMenu_mainMenu();
int adminMenu_exit();
int studentMenu_viewTable();
int studentMenu_mainMenu();
int studentMenu_exit();

#endif