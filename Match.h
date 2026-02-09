#pragma once
#include <iostream>
#include "Team.h"

using namespace std;

class Match
{
public :
	Match(Team& hometeam, Team& awayteam, bool isPlayerMatch);
	Team PlayMatch(int StartTime);
	
	void Attack(Team& Attacker, Team& Defender);

	bool IsDraw();
	bool bIsPlayerMatch;
	bool DecideAttackTeam();

	int CurrentMinute;
	int HomeScore;
	int AwayScore;
	

	void PrintResult();
	void TryShoot(bool isHomeAttack);
	void PlayTurn(int CurrentTime);
	void Penalty();
	void PrintScoreboard();
	void Commentary(string message, int WaitTime);

	Team Winner;
	Team GetWinner();

private :
	Team& HomeTeam;
	Team& AwayTeam;

};

