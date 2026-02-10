#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <limits>
#include <algorithm>
#include "Team.h"
#include "Tournament.h"
#include "GameUtils.h"
#include "Art.h"

using namespace std;

int main()
{
	srand((unsigned int)time(nullptr));

	Art::TitleArt();

	vector<string> TournamentTeams =
	{
	"FC 바르셀로나", "레알 마드리드", "아틀레티코 마드리드", "맨체스터 시티", "맨체스터 유나이티드",
	"아스널", "첼시", "선덜랜드", "인터밀란", "AC 밀란",
	"SSC 나폴리", "아약스", "벤피카", "AS 로마", "토트넘 핫스퍼",
	"스포르팅", "유벤투스", "코펜하겐", "포르투", "리버풀","리옹",
	"파리생제르망", "세비야", "마르세유", "라이프치히","바이에른 뮌헨",
	"도르트문트", "바이엘 레버쿠젠", "아스톤 빌라","코모 1907","AS 모나코","뉴캐슬 유나이티드"
	};

	cout << "==========================================" << endl;
	cout << "  Welcome to Champions League Simulation!   " << endl;
	cout << "==========================================" << endl;
	GameUtils::NextScreen();

	cout << "[1] 참가 팀 목록" << endl;
	cout << "당신의 팀 이름을 선택하세요 (번호를 선택하세요)" << endl;
	cout << "---------------------------------------------" << endl;
	for (int i = 0; i < TournamentTeams.size(); i++)
	{
		cout << "[" << setw(2) << i + 1 << "]"
			<< left << setw(20) << TournamentTeams[i] << endl;
		if ((i + 1) % 2 == 0)
		{
			cout << endl;
		}
	}
	cout << "-----------------------------------------------" << endl;

	int choice;
	string playerName;
	while (true)
	{
		cout << "플레이할 팀의 번호를 입력하세요 : " << endl;
		if (!(cin >> choice) || choice < 1 || choice>32)
		{
			cout << "잘못된 팀선택입니다. 다시 입력해주세요" << endl;
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			continue;
		}
		playerName = TournamentTeams[choice - 1];
		break;
	}

	Position playerFormation;

	const int TotalPlayers = 10;

	cout << "[2]" << playerName << "의 포메이션 설정 중 (GK 제외 총 10명)" << endl;

	while (true)
	{
		cout << " DF(수비수) : ";
		cin >> playerFormation.DF;
		cout << " MF(미드필더) : ";
		cin >> playerFormation.MF;
		cout << " FW (공격수) : ";
		cin >> playerFormation.FW;

		if (playerFormation.FW + playerFormation.MF + playerFormation.DF == TotalPlayers)
		{
			break;
		}
		cout << "합계가 " << TotalPlayers << " 명이 되어야합니다." << endl;
	}

	cin.ignore((numeric_limits<streamsize>::max)(), '\n');

	vector<Team> teams;
	vector<Position> AIFormations = { {3,5,2}, {4,3,3,},{4,4,2},{5,3,2} };

	teams.push_back(Team(playerName, playerFormation));

	for (int i = 0; i < TournamentTeams.size(); i++)
	{
		if (TournamentTeams[i] == playerName)
		{
			continue;
		}

		Position randomForm = AIFormations[rand() % AIFormations.size()];
		teams.push_back(Team(TournamentTeams[i], randomForm));
	}
	random_shuffle(teams.begin(), teams.end());

	GameUtils::ClearScreen();
	cout << "===== 32강 월드컵 토너먼트 대진표 확정 =====" << endl;

	cout << "\n========== 32강 대진표 ==========\n";

	for (int i = 0; i + 1 < teams.size(); i += 2)
	{
		cout << teams[i].GetName()
			<< "  VS  "
			<< teams[i + 1].GetName()
			<< endl;
	}

	cout << "=================================\n";
	Art::KickOffArt();
	GameUtils::NextScreen();

	Tournament ChampionsLeague(teams, playerName);
	ChampionsLeague.StartTournament();

	GameUtils::ClearScreen();
	Art::TrophyArt();
	Team Champion = ChampionsLeague.GetChampion();

	cout << "==========" << "Last Dance" << "==========" << endl;
	cout << "최종 우승팀 : " << Champion.GetName() << endl;
	return 0;
}
