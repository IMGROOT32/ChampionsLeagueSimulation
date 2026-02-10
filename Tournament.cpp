#include "Tournament.h"
#include <iostream>

vector<string> WinnersLog;

Tournament::Tournament(vector<Team>& teams, string playerName)
{
	Teams = teams;
	PlayerName = playerName;

}

void Tournament::StartTournament()
{
	string rounds[] = { "32강", "16강", "8강", "4강", "결승" };

	int roundIndex = 0;

	for (int r = 0; r < 5; r++)
	{
		if (Teams.size() <= 1)
		{
			break;
		}

		cout << "\n==============================" << endl;
		cout << "  " << rounds[r] << " 시작" << endl;
		cout << "==============================" << endl;
		GameUtils::NextScreen();

		PlayRound(rounds[r]);

		PrintRoundResults(rounds[r]);
	}

	if (!Teams.empty())
	{
		cout << "WINNER WINNER CHICKEN DINNER" << endl;
		cout << "============================" << endl;
		cout << "최종 우승 팀: " << Teams[0].GetName() << "!!!" << endl;
		cout << "============================" << endl;
	}
}

void Tournament::PlayRound(string roundName)
{
	vector<Team> winners;

	for (int i = 0; i + 1 < Teams.size(); i += 2)
	{
		Team& A = Teams[i];
		Team& B = Teams[i + 1];

		bool isPlayerMatch =
			(A.GetName() == PlayerName ||
				B.GetName() == PlayerName);

		Match match(A, B, isPlayerMatch);
		Team winner = match.PlayMatch(5);

		WinnersLog.push_back(
			A.GetName() + " vs " +
			B.GetName() + " → " +
			winner.GetName()
		);

		winners.push_back(winner);
	}

	Teams = winners;
}

void Tournament::PrintRoundResults(string RoundName)
{
	cout << "===== " << RoundName << " 경기 결과 =====" << endl;

	for (const string& log : WinnersLog)
	{
		cout << log << endl;
	}

	WinnersLog.clear();
	cout << "==============================" << endl;
	GameUtils::NextScreen();
}

Team Tournament::GetChampion()
{
	if (!Teams.empty())
		return Teams[0];

	return Team("없음", { 0,0,0 });
}