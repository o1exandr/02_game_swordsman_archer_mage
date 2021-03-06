/*
Завдання 2.
Опишіть класи "Swordsman" (Мечник), "Archer" (Лучник) і "Mage" (Маг), кожен з яких є екземпляром базового(можна абстрактного) класу "Unit" (штука, елемент) в комп'ютерній грі, і може атакувати, ухилятись від атак і вмирати.
У мечника 15 хіт-поінтів (життів), пошкодження при атаці 5, шанс ухилятись 60%.
Лучник: 12 hp, 4 dmg, 40% dodge
Маг: 8 hp, 10 dmg, 30% dodge
-------------------------------------------------------------------------------------------------------------
Опишіть клас  "Team"(Команда), у якому є  поля
o	 назва команди
o	 масив чи вектор  по три(чи більше) юніта,
причому тип юніта (мечник, лучник чи маг) має задаватись випадково, при заповненні команди(на початку гри).

Написати методи:
o	перевірки чи у команді є не вбиті гравці
o	виводу гравців команди
-------------------------------------------------------------------------------------------------------------
Опишіть клас "Game"(Гра), що містить 2 команди ворогуючих сторін

Можливі варіанти ворогуючих сторін: три лучники проти мечника і двох магів, або - лучник, мечник і маг проти двох мечників і лучника і т.д(при кількості гравців у команді 3).

Опишіть метод бою  між КОМАНДАМИ, поки бійці однієї з сторін всі не загинуть. В консоль при цьому виводьте повідомлення хто кого атакував, чи вдалась атака, скільки життя залишилось у жертви чи вона загинула. Нехай бій відбувається поступово, по натиснення клавіші spacebar (пробіла), щоб ми могли спостерігати його атака за атакою.

В кінці бою оголосіть, яка команда перемогла (перша/друга, синя/червона, альянс/орки чи ін.).
...............................................................................................................
Правила бою : кожен боєць (Воїн, Лучник чи Маг) вишукує серед ворогів суперника свого типу і атакує його.
Скажімо, якщо маємо команди:
A11 - M21
A12 - S22
S13 - A23
...то А11 має вибрати своєї ціллю А23.

Якщо ворогів свого типу не знайдено, тоді нехай  бійці атакують довільного суперника.

Перевірити тип гравця можна за допомогою операції typeid.
if(typeid(Archer ) == typeid(*team[i])) , тут team[i] – вказівник на Unit.
*/

#include "stdafx.h"
#include <iostream> 
#include <string>
#include <vector>
#include <ctime>
#include <conio.h>
#include <iomanip>
#include <windows.h>


using namespace std;

const int teamPlayers = 3;
#define LINE cout << "----------------------------------------\n";

class Unit abstract 
{
protected:

	int hp;
	int dmg;
	int dodge;

public:
	
	// атака юнітом іншого юінта
	virtual void attack(Unit & unit)
	{
		if (unit.evading())
		{
			unit.setHp(unit.getHp() - this->getDmg());
			if (unit.getHp() < 0)
				unit.setHp(0);
			cout << " DAMAGED on " << this->getDmg() << ", his ";
			if (unit.die())
				cout << "hit-point = 0, he DIED x_x\n";
			else
				cout << "hit-point = " << unit.getHp() << endl;
		}
		else
		{
			cout << " EVADED. His hit-point = " << unit.getHp() << endl;
		}
		cout << endl;
	}

	//захист юніта при атаці
	virtual bool evading() const
	{	
		int tmp = rand() % 100;
		if (tmp < this->getDodge())
			return true;
		else
			return false;

	}

	//перевірка чи живий юніт
	virtual bool die()
	{
		if (this->getHp() <= 0)
			return 1;
		else 
			return 0;
	}

	int getHp() const
	{
		return hp;
	}

	void setHp(int hp) 
	{
		this->hp = hp;
	}

	int getDmg() const
	{
		return dmg;
	}

	int getDodge() const
	{
		return dodge;
	}

	//вивід скіллів юніта
	void showUnit()
	{
		cout << "HP: " << hp << "; Dmgs: " << dmg << "; Dodge: " << dodge << "%\n";
	}

};

//юніт мечник
class Swordsman : public Unit
{
public:

	Swordsman()
	{
		hp = 15;
		dmg = 5;
		dodge = 60;
	}
};

//юніт лучник
class Archer : public Unit
{
public:

	Archer()
	{
		hp = 12;
		dmg = 4;
		dodge = 40;
	}
};

//юніт маг
class Mage : public Unit
{
public:

	Mage()
	{
		hp = 8;
		dmg = 10;
		dodge = 30;
	}
};

class Team 
{
protected:

	string name;
	vector<Unit*> team {};

public:

	//наповнення команди випадковими типами юнітів
	Team(string name = "without name")
	{
		setName(name);

		for (size_t i = 0; i < teamPlayers; ++i)
		{
			int tmp = rand() % teamPlayers;
			switch (tmp)
			{
				case 0:
					{
						team.push_back(new Swordsman());
						break;
					}
				case 1:
					{
						team.push_back(new Archer());
						break;
					}
				case 2:
					{
						team.push_back(new Mage());
						break;
					}
				default:
				{}
			}
		}
	}

	string getName() const
	{
		return name;
	}

	void setName(string name)
	{
		this->name = name;
	}

	Unit* getUnit(int i)
	{
		return team[i];
	}

	//вивід сформованої команди
	void showTeam()
	{
		cout << "-=-=-=-=-=-=-=-\nTeam: " << name << endl << "-=-=-=-=-=-=-=-\n";
		for (size_t i = 0; i < team.size(); ++i)
		{
			if (typeid(Archer) == typeid(*team[i]))
				cout << "Archer";
			if (typeid(Swordsman) == typeid(*team[i]))
				cout << "Swordsman";
			if (typeid(Mage) == typeid(*team[i]))
				cout << "Mage";
			cout << i + 1 << "   \t";
			team[i]->showUnit();
		}
		cout << "- - - - - - - -\n";
	}

	//перевірка команди на наявність живих юнітів
	bool auditDie()
	{
		int count = 0;
		for (size_t i = 0; i < team.size(); ++i)
			if (!team[i]->die())
				++count;
		if (count == 0)
			return 1;
		else 
			return 0;
	}

};

class Game
{

protected:
	Team first, second;

public:

	//перебіг бою
	void fight()
	{
		bool game = true;
		first.setName("Red");
		second.setName("Blue");
		first.showTeam();
		second.showTeam();
		cout << "Press 'Space' for continue\n\n";
		do
		{
			if (_kbhit())
			{
				switch (_getch())
				{
					case 32:
					{
						{
							for (size_t i = 0; i < teamPlayers; ++i)
							{
								//атака юніта першої команди
								if (!first.getUnit(i)->die())
								{
									bool type = 0;
									for (size_t j = 0; j < teamPlayers; ++j)
										if (getType(first, i) == getType(second, j) && !second.getUnit(j)->die())
										{
											showAttack(first, second, i, j);
											type = 1;
											break;
										}
									if (!type)
										for (size_t j = 0; j < teamPlayers; ++j)
											if (!second.getUnit(j)->die())
											{
												showAttack(first, second, i, j);
												break;
											}

								}
								//атака юніта другої команди
								if (!second.getUnit(i)->die())
								{
									bool type = 0;
									for (size_t j = 0; j < teamPlayers; ++j)
										if (getType(second, i) == getType(first, j) && !first.getUnit(j)->die())
										{
											showAttack(second, first, i, j);
											type = 1;
											break;
										}
									if (!type)
										for (size_t j = 0; j < teamPlayers; ++j)
											if (!first.getUnit(j)->die())
											{
												showAttack(second, first, i, j);
												break;
											}
								}
								
							}
							//перевірка чи є команда в якій повністю усі юніти загинули
							// якщо так - вивід результатів і оголошення переможця
							if (first.auditDie() || second.auditDie())
							{
								cout << "\n\n- = END of GAME = -\n\n";
								showResult();
								if (first.auditDie())
								{
									setColor(11);
									cout << "\nTeam \"" << second.getName() << "\" Win!\n";
									setColor();
								}
								else
								{
									setColor(12); 
									cout << "\nTeam \"" << first.getName() << "\" Win!\n";
									setColor();
								}
								game = false;
							}
							else
								showResult();
						};
						break;
					}

					case 27:
					{
						game = false;
						break;
					}

					default:
					{
					}
				}
			}
			
			
		} while (game);
	}

	//вивід інфо по юніту
	string unitHP(Team team, int i, bool hp = 1, bool name = 1)
	{
		string tmpHp = "";
		string tmpName = "";

		if (hp)
			tmpHp = "(" + to_string(team.getUnit(i)->getHp()) + ")";

		if (name)
			tmpName = team.getName() + ":";

		return tmpName + (typeid(*team.getUnit(i)).name() + 6) + to_string(i + 1) + tmpHp;
	}

	//визначення типу юніта
	string getType(Team team, int i)
	{
		return (typeid(*team.getUnit(i)).name() + 6);
	}

	//текстове відображення бою, хто кого атакує і які наслідки
	void showAttack(Team first, Team second, int i, int j)
	{ 
		int red = 12;
		int blue = 11;

		if (first.getName() == "Red")
		{
			red = 12;
			blue = 11;
		}
		else
		{
			red = 11;
			blue = 12;
		}
		setColor(red);
		cout << unitHP(first, i);
		setColor();
		cout << " attack ";
		setColor(blue);
		cout << unitHP(second, j) << endl;
		cout << unitHP(second, j, 0);
		setColor();
		first.getUnit(i)->attack(*second.getUnit(j));
		(_getch());
	}

	//вивід результатів по завершенні раудну бою
	void showResult()
	{
		LINE
		cout << "Team \"" << first.getName() << "\"\t\tTeam \"" << second.getName() << "\"\n";
		cout << "----------\t\t---------\n";
		for (int i = 0; i < teamPlayers; ++i)
			cout << unitHP(first, i, 1, 0) << "\t\t" << unitHP(second, i, 1, 0) << endl;
		LINE
		cout << "Press 'Space' for continue or 'Esc' for exit\n\n";
		
	}

	//колір тексту
	void setColor(int color = 7)
	{
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut, color);
	}
};

int main()
{
	srand(unsigned(time(0)));

	Game g;
	g.fight();

	cout << endl;
	system("pause");
	return 0;
}