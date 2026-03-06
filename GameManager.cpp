#include "GameManager.h"
#include <iomanip>
#include <random>

void GameManager::StartGame()
{
	srand((unsigned int)time(nullptr));

	Art::TitleArt();
	InGameTeams();
	Team playerTeam = SelectPlayerTeam();
	vector<Team> teams;
	vector<Position> AIFormations =
	{
		{3,5,2},
		{4,3,3},
		{4,4,2},
		{5,3,2}
	};

	teams.push_back(playerTeam);

	for (string name : TournamentTeams)
	{
		if (name == playerTeam.GetName())
			continue;

		Position randomForm = AIFormations[rand() % AIFormations.size()];
		teams.push_back(Team(name, randomForm));
	}
	random_device rd;
	mt19937 g(rd());
	shuffle(teams.begin(), teams.end(),g);

	Tournament championsLeague(teams, playerTeam.GetName());
	championsLeague.StartTournament();
	Art::TrophyArt();

	Team Champion = championsLeague.GetChampion();
	cout << "==========" << "Last Dance" << "==========" << endl;
	cout << "최종 우승팀 : " << Champion.GetName() << endl;
}

void GameManager::InGameTeams()
{
	TournamentTeams =
	{
	"FC 바르셀로나", "레알 마드리드", "아틀레티코 마드리드", "맨체스터 시티", "맨체스터 유나이티드",
	"아스널", "첼시", "선덜랜드", "인터밀란", "AC 밀란",
	"SSC 나폴리", "아약스", "벤피카", "AS 로마", "토트넘 핫스퍼",
	"스포르팅", "유벤투스", "코펜하겐", "포르투", "리버풀","리옹",
	"파리생제르망", "세비야", "마르세유", "라이프치히","바이에른 뮌헨",
	"도르트문트", "바이엘 레버쿠젠", "아스톤 빌라","코모 1907","AS 모나코","뉴캐슬 유나이티드"
	};
}

Team GameManager::SelectPlayerTeam()
{
	cout << "[1] 참가 팀 목록" << endl;
	cout << "당신의 팀 이름을 선택하세요 (번호를 선택하세요)" << endl;
	cout << "---------------------------------------------" << endl;
	
	for (int i = 0; i < TournamentTeams.size(); i++)
	{
		cout << "["<<i + 1<<"]" << TournamentTeams[i] << endl;
	}

	int choice;
	cin >> choice;
	string playerName = TournamentTeams[choice - 1];
	Position formation = SetupFormation(playerName);
	
	return Team(playerName, formation);
}

Position GameManager::SetupFormation(string teamName)
{
	Position playerFormation;
	const int TotalPlayers = 10;
	cout << teamName << "의 포메이션을 설정하세요 (GK제외 10명)" << endl;

	while (true)
	{
		cin >> playerFormation.DF >> playerFormation.MF >> playerFormation.FW;

		if (playerFormation.DF + playerFormation.MF + playerFormation.FW == 10)
			break;

		cout << "팀원은 총 10명이어야 합니다 (GK제외)" << endl;
	}
	return playerFormation;
}