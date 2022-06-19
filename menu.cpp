#include<iostream>
#include<vector>
#include<string>
using namespace std;

#include"Menu.h"
#include"Option.h"

void Menu::append(Option op)
{
	optionList.push_back(op);
}
void Menu::setReadText(string readText)
{
	this->readText = readText;
}
void Menu::run()
{
	cout << readText << endl;
	for (int i = 0; i < optionList.size(); i++)
	{
		cout << i + 1 << ". " << optionList[i].getName() << endl;
	}
	cout << "\nEnter menu : ";

	int select = -1;
	cin >> select;
	if (0 < select && select <= optionList.size())
	{
		optionList[select - 1].run();
	}
	else
	{
		cout << "Invalid option. Try again." << endl;
		this->run();
	}
}
void SecuredMenu::setID(string id)
{
	ID = id;
}
void SecuredMenu::setName(string name)
{
	this->name = name;
}
string SecuredMenu::getID()
{
	return ID;
}
string SecuredMenu::getName()
{
	return name;
}
