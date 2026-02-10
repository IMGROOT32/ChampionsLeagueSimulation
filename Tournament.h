#pragma once
#include "Match.h"
#include "GameUtils.h"
#include <iostream>
#include <vector>

using namespace std;

class Tournament
{
public :
	Tournament(vector<Team>& teams, string playerName);
	
	void StartTournament();
	void PlayRound(string RoundName);
	void PrintRoundResults(string RoundName);

	Team GetChampion();

private :
	vector<Team> Teams;
	string PlayerName;

};

