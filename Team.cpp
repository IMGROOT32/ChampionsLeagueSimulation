#include "Team.h"
#include <algorithm>

Team::Team(string name, Position formation)
{
	Name = name;
	Formation = formation;

	StartStat = PlayerStat();
	Stat = StartStat;

	CurrentStamina = Stat.Stamina;


	cout << Name << " 구단 창단 완료!" << endl;
}


void Team::StaminaLoss()
{
	float Loss = CurrentStamina * 0.1f;
	CurrentStamina -= Loss;
	float FatigueRate = CurrentStamina / StartStat.Stamina;

	Stat.Shoot = Stat.Shoot * FatigueRate;
	Stat.Pass = Stat.Pass * FatigueRate;
	Stat.Defend = Stat.Defend * FatigueRate;

	if (CurrentStamina < 5) 
	{ 
		CurrentStamina = 5; 
	}
}

void Team::StatUp()
{
	Stat.Shoot *= 1.35;
	Stat.Pass *= 1.35;
	Stat.Defend *= 1.15;
	
	StartStat = Stat;
}

void Team::PlayerBoost()
{
	Stat.Speed *= 1.5f;
	Stat.Stamina *= 1.5f;
	Stat.Shoot *= 1.5f;
	Stat.Pass *= 1.5f;
	Stat.Defend *= 1.5f;

	StartStat = Stat;
}
