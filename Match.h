#pragma once
#include <iostream>
#include <string>
#include "Team.h"
#include "DirectionSystem.h"
#include "AISystem.h"

using namespace std;

class Match
{
private:

	Team HomeTeam;
	Team AwayTeam;

public:
	Match(Team hometeam, Team awayteam, bool isPlayerMatch, string playerTeam);
	Team PlayMatch(int StartTime);
	
	bool IsDraw();
	bool bIsPlayerMatch;
	bool DecideAttackTeam();

	int CurrentMinute;
	int HomeScore;
	int AwayScore;
	
	void Attack(Team& FW, Team& DF);
	void PrintResult();
	void TryShoot(bool isHome);
	void PlayTurn(int CurrentTime);
	void Penalty();
	void PrintScoreboard();
	void Commentary(string message, int WaitTime);

	string PlayerName;

	Team Winner;
	Team GetWinner();
};

