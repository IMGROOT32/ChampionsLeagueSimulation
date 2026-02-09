#include "Match.h"
#include "Art.h"
#include "GameUtils.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Match::Match(Team& hometeam, Team& awayteam, bool isPlayerMatch)
	: HomeTeam(hometeam), AwayTeam(awayteam), bIsPlayerMatch(isPlayerMatch)
{
	HomeScore = 0;
	AwayScore = 0;
	CurrentMinute = 0;

}

void Match::PrintScoreboard()
{
	GameUtils::ClearScreen();
	cout << "\n========================================" << endl;
	cout << "  " << HomeTeam.GetName() << "  " << HomeScore
		<< " : " << AwayScore << "  " << AwayTeam.GetName() << endl;
	cout << "  (시간: " << CurrentMinute << "분)" << endl;
	cout << "========================================\n" << endl;
	GameUtils::WaitMs(1000);
}

void Match::PlayTurn(int CurrentTime)
{
	CurrentMinute = CurrentTime;

	PrintScoreboard();

	Team* Attacker = DecideAttackTeam() ? &HomeTeam : &AwayTeam;
	Team* Defender = (Attacker == &HomeTeam) ? &AwayTeam : &HomeTeam;

	cout << "공격 팀 : " << Attacker->GetName() << endl;
	cout << "수비 팀 : " << Defender->GetName() << endl;
	GameUtils::WaitMs(1000);

	int EventRoll = rand() % 100;

	if (EventRoll < 45)
	{
		cout << ">> " << Attacker->GetName() << "이(가) 돌파를 시도합니다!" << endl;
		GameUtils::WaitMs(1000);
		Attack(*Attacker, *Defender);
	}
	else if (EventRoll < 75)
	{
		GameUtils::ClearScreen();
		cout << ">> " << Defender->GetName() << "의 정확한 태클! 깔끔하게 클리어링 합니다." << endl;
		Art::DefenceArt();
		GameUtils::WaitMs(1000);
	}

	else {
		GameUtils::ClearScreen();
		cout << ">> 중원에서 치열한 볼 다툼이 이어집니다..." << endl;
		GameUtils::WaitMs(1000);
	}

	HomeTeam.StaminaLoss();
	AwayTeam.StaminaLoss();

	if (bIsPlayerMatch)
	{
		GameUtils::NextScreen();
	}
}
void Match::Commentary(string message, int WaitTime = 800) {
	if (bIsPlayerMatch) {
		cout << message << endl;
		GameUtils::WaitMs(WaitTime);
	}
}

bool Match::DecideAttackTeam()
{
	float HomeMF = (HomeTeam.Stat.Pass * HomeTeam.GetFormation().MF) + (HomeTeam.Stat.Speed * 0.3f);
	float AwayMF = (AwayTeam.Stat.Pass * AwayTeam.GetFormation().MF) + (AwayTeam.Stat.Speed * 0.3f);

	float total = HomeMF + AwayMF;
	if (total <= 0) return rand() % 2 == 0;

	float roll = (float)rand() / RAND_MAX;
	return (roll < (HomeMF / total));
}

void Match::Attack(Team& FW, Team& DF)
{
	PrintScoreboard();

	cout << ">> " << FW.GetName() << " 하프 스페이스 침투!" << endl;
	GameUtils::WaitMs(1000);

	float FWPower = (FW.Stat.Shoot * FW.GetFormation().FW) + (FW.Stat.Speed * 0.5f);
	float DFPower = (DF.Stat.Defend * DF.GetFormation().DF) + (DF.Stat.Speed * 0.5f);
	float roll = (float)rand() / RAND_MAX * (FWPower + DFPower);

	if (!bIsPlayerMatch)
	{
		if (roll < FWPower)
		{
			TryShoot(&FW == &HomeTeam);
		}
			return;
	}
	if (roll < FWPower)
	{
		GameUtils::ClearScreen();
		cout << CurrentMinute << "분" << endl;
		cout << ">> " << FW.GetName() << "의 " << FW.GetFormation().FW
			<< "공격진이 수비라인을 허뭅니다!" << endl;

		Art::ShootArt();
		GameUtils::WaitMs(1000);
		cout << FW.GetName() << " 상대 골키퍼와 1대1 찬스 슛!!!" << endl;
		TryShoot(&FW == &HomeTeam);
	}
	else
	{
		cout << DF.GetName() << "의 " << DF.GetFormation().DF
			<< " 슈퍼태클!!!" << endl;
		Art::DefenceArt();
		GameUtils::WaitMs(1000);
	}
}

void Match::TryShoot(bool isHomeAttack)
{
	GameUtils::ClearScreen();
	PrintScoreboard();

	Team& atkTeam = isHomeAttack ? HomeTeam : AwayTeam;
	Team& defTeam = isHomeAttack ? AwayTeam : HomeTeam;

	int xG = (atkTeam.Stat.Shoot > defTeam.Stat.Defend) ? 50 : 30;

	if (rand() % 100 < xG)
	{
		if (isHomeAttack)
		{
			HomeScore++;
		}
		else
		{
			AwayScore++;
		}

		if (bIsPlayerMatch)
		{
			GameUtils::ClearScreen();
			cout << "골! 골! 골!!!" << endl;
			Art::GoalArt();
			GameUtils::WaitMs(1000);
		}
	}
	else
	{
		int miss = rand() % 3;

		if (miss == 0)
			cout << "골키퍼의 슈퍼 세이브!!!" << endl;
		else if (miss == 1)
			cout << "깻잎 한장 차이로 골대를 벗어납니다!!!" << endl;
		else
			cout << "골대 맞고 튕겨져 나옵니다!!!" << endl;

		Art::SaveArt();
		GameUtils::WaitMs(1000);
	}

	if (bIsPlayerMatch) GameUtils::NextScreen();
}

Team Match::PlayMatch(int StartTime)
{
	if (bIsPlayerMatch)
	{
		PrintScoreboard();
	}

	int timeline[] = { 15, 30, 45, 60, 75, 90 };

	for (int i = 0; i < 6; i++)
	{
		CurrentMinute = timeline[i];

		PlayTurn(CurrentMinute);

	}

	if (IsDraw())
	{
		Penalty();
	}

	if (bIsPlayerMatch)
	{
		PrintResult();

		bool PlayerWon = (GetWinner().GetName() == HomeTeam.GetName());

		if (PlayerWon)
		{
			Art::VictoryArt();
		}
		else
		{

			Art::DefeatArt();
			cout << "패배했습니다. 다음 대회까지 365일 남았습니다." << endl;
		}
		GameUtils::NextScreen();
	}

	HomeTeam.StatUp();
	AwayTeam.StatUp();

	return GetWinner();
}

bool Match::IsDraw()
{
	return (HomeScore == AwayScore);
}

Team Match::GetWinner()
{
	if (HomeScore > AwayScore)
	{
		return HomeTeam;
	}
	else
	{
		return AwayTeam;
	}
}

void Match::PrintResult()
{
	GameUtils::ClearScreen();
	cout << "\n===== 경기 종료 (Final Score) =====\n";
	cout << HomeTeam.GetName() << HomeScore << ":" << AwayScore << AwayTeam.GetName() << endl;

	GameUtils::NextScreen();
}

void Match::Penalty()
{
	int HomePK = 0;
	int AwayPK = 0;

	if (bIsPlayerMatch) {
		GameUtils::ClearScreen();
		cout << "===== [승 부 차 기] 시작 =====" << endl;
		GameUtils::NextScreen();
	}

	for (int i = 0; i < 5; i++)
	{
		bool HomeGoal = (rand() % 100 < 75);
		bool AwayGoal = (rand() % 100 < 70);

		if (HomeGoal) HomePK++;
		if (AwayGoal) AwayPK++;

		if (bIsPlayerMatch) {
			cout << i + 1 << "번 키커: "
				<< (HomeGoal ? "O " : "X ") << " | " << (AwayGoal ? "O" : "X") << endl;
			GameUtils::WaitMs(1000);
		}
	}

	while (HomePK == AwayPK)
	{
		bool HomeGoal = rand() % 100 < 75;
		bool AwayGoal = rand() % 100 < 70;

		cout << HomeTeam.GetName()
			<< (HomeGoal ? " 골!" : " 실축!") << endl;
		GameUtils::WaitMs(1000);

		cout << AwayTeam.GetName()
			<< (AwayGoal ? " 골!" : " 실축!") << endl;
		GameUtils::WaitMs(1000);

		if (HomeGoal != AwayGoal)
		{
			if (HomeGoal) HomePK++;
			else AwayPK++;
			break;
		}
		GameUtils::NextScreen();
	}
}

