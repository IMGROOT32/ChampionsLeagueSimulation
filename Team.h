#pragma once
#include <iostream>

using namespace std;

struct PlayerStat
{
int Shoot = 80;
int Pass = 80;
int Defend = 80;

int Speed = 80;
int Stamina = 80;
};

struct Position
{
	int FW;
	int MF;
	int DF;
};

class Team
{
public :
	Team(string name, Position formation);
	Team() : Name(""), Formation({ 0, 0, 0 }) {}
	
	int CurrentStamina;

	void PlayerBoost();
	void StaminaLoss();
	void StatUp();

	PlayerStat StartStat;
	PlayerStat Stat;
	string GetName() { return Name; }
	Position GetFormation() { return Formation; }

private :
	string Name;
	Position Formation;
};

