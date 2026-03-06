#pragma once
#include <vector>
#include <string>
#include "Team.h"
#include "Tournament.h"
#include "GameUtils.h"
#include "Art.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

class GameManager
{
public:
	void StartGame();

private:
	vector<string> TournamentTeams;

	void InGameTeams();
	Team SelectPlayerTeam();
	Position SetupFormation(string teamName);
	
};

