#pragma once
#include <iostream>
#include "Team.h"

using namespace std;

class Match
{
public :
	Match(Team hometeam, Team awayteam, bool isPlayerMatch);
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

	Team Winner;
	Team GetWinner();

private :
	Team HomeTeam;
	Team AwayTeam;

};

