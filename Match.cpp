#include "Match.h"
#include "Art.h"
#include "GameUtils.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Match::Match(Team hometeam, Team awayteam, bool isPlayerMatch)
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
	if (!bIsPlayerMatch)
	{
		if (rand() % 100 < 20) HomeScore++;
		if (rand() % 100 < 20) AwayScore++;
		return;
	}

	PrintScoreboard();

	bool homeAttack = DecideAttackTeam();
	Team& Attacker = homeAttack ? HomeTeam : AwayTeam;
	Team& Defender = homeAttack ? AwayTeam : HomeTeam;

	int EventRoll = rand() % 100;

	if (EventRoll < 45)
	{
		cout << ">> " << Attacker.GetName() << "이(가) 돌파를 시도합니다!" << endl;
		GameUtils::WaitMs(1000);
		Attack(Attacker, Defender);
		return;
	}

	if (EventRoll < 60)
	{
		GameUtils::ClearScreen();
		cout << ">> " << Defender.GetName() << "의 정확한 태클! 깔끔하게 클리어링 합니다." << endl;
		Art::DefenceArt();
		GameUtils::WaitMs(1000);
		return;
	}

	if (EventRoll < 80)
	{
		GameUtils::ClearScreen();
		cout << Attacker.GetName() << " 패스 미스..." << endl;
		GameUtils::WaitMs(1000);
		return;
	}

	GameUtils::ClearScreen();
	cout << ">> 중원에서 치열한 볼 다툼이 이어집니다..." << endl;
	GameUtils::WaitMs(1000);

	HomeTeam.StaminaLoss();
	AwayTeam.StaminaLoss();

}
void Match::Commentary(string message, int WaitTime = 1000)
{
	if (bIsPlayerMatch) {
		cout << message << endl;
		GameUtils::WaitMs(WaitTime);
	}
}

bool Match::DecideAttackTeam()
{
	float HomePass = HomeTeam.Stat.Pass * (1.0f + HomeTeam.GetFormation().MF * 0.05f);
	float AwayPass = AwayTeam.Stat.Pass * (1.0f + AwayTeam.GetFormation().MF * 0.05f);

	float total = HomePass + AwayPass;

	if (total <= 0)
		return rand() % 2 == 0;

	float roll = (float)rand() / RAND_MAX * total;
	return roll < HomePass;
}

void Match::Attack(Team& FW, Team& DF)
{
	PrintScoreboard();

	cout << ">> " << FW.GetName() << " 하프 스페이스 침투!" << endl;
	GameUtils::WaitMs(1000);

	float atk = (FW.Stat.Shoot * FW.GetFormation().FW * 1.2f
		+ FW.Stat.Speed * FW.GetFormation().FW);
	float def = (DF.Stat.Defend * DF.GetFormation().DF);
	float roll = (float)rand() / RAND_MAX * (atk + def);

	if (!bIsPlayerMatch)
	{
		if (roll < atk)
			TryShoot(&FW == &HomeTeam);
		return;
	}

	if (roll < atk)
	{
		GameUtils::ClearScreen();
		cout << CurrentMinute << "분" << endl;
		cout << ">> " << FW.GetName() << "의 " << "공격진이 수비라인을 허뭅니다!" << endl;

		Art::ShootArt();
		GameUtils::WaitMs(1000);
		cout << FW.GetName() << " 상대 골키퍼와 1대1 찬스 슛!!!" << endl;
		TryShoot(&FW == &HomeTeam);

		return;
	}
	cout << DF.GetName() << "의 " << " 슈퍼태클!!!" << endl;
	Art::DefenceArt();
	GameUtils::WaitMs(1000);
}


void Match::TryShoot(bool isHome)
{

	GameUtils::ClearScreen();
	PrintScoreboard();

	float atk = isHome 
		? (HomeTeam.Stat.Shoot * HomeTeam.GetFormation().FW )
		: (AwayTeam.Stat.Shoot * AwayTeam.GetFormation().FW );
	float def = isHome 
		? (AwayTeam.Stat.Defend * AwayTeam.GetFormation().DF) 
		: (HomeTeam.Stat.Defend * HomeTeam.GetFormation().DF);

	int ratio = atk / (atk + def);

	float boosted = pow(ratio, 1.3f);

	boosted += (isHome
		? HomeTeam.GetFormation().FW
		: AwayTeam.GetFormation().FW) * 0.01f;

	boosted -= (isHome
		? AwayTeam.GetFormation().DF
		: HomeTeam.GetFormation().DF) * 0.008f;

	int xG = (int)(boosted * 100);

	xG = max(20, min(90, xG));

	if (!bIsPlayerMatch)
	{
		if (rand() % 100 < xG)
		{
			if (isHome) HomeScore++;
			else AwayScore++;
		}
		return;
	}

	GameUtils::ClearScreen();
	cout << CurrentMinute << "분" << endl;

	if (rand() % 100 < xG)
	{
		if (isHome)
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
	}
	GameUtils::WaitMs(1000);
}

Team Match::PlayMatch(int StartTime)
{
	CurrentMinute = StartTime;

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
	return HomeScore == AwayScore;
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
	cout << HomeTeam.GetName() << " " << HomeScore << " : " << AwayScore << " " << AwayTeam.GetName() << endl;

	GameUtils::NextScreen();
}

void Match::Penalty()
{
	int HomePK = 0;
	int AwayPK = 0;

	if (!bIsPlayerMatch)
	{
		if (rand() % 2 == 0) HomeScore++;
		else AwayScore++;
		return;
	}

	if (bIsPlayerMatch) {
		GameUtils::ClearScreen();
		cout << "===== [승 부 차 기] 시작 =====" << endl;
		GameUtils::NextScreen();
	}

	for (int i = 0; i < 5; i++)
	{
		cout << "[승부차기 " << i + 1 << "번]" << endl;

		bool homeGoal = rand() % 100 < 75;
		bool awayGoal = rand() % 100 < 70;

		cout << HomeTeam.GetName()
			<< (homeGoal ? " 골 성공!" : " 실축...") << endl;
		GameUtils::WaitMs(1000);

		cout << AwayTeam.GetName()
			<< (awayGoal ? " 골 성공!" : " 실축...") << endl;
		GameUtils::WaitMs(1000);

		if (homeGoal) HomePK++;
		if (awayGoal) AwayPK++;

		cout << "현재 PK 스코어: "
			<< HomePK << " - " << AwayPK << endl;
		GameUtils::WaitMs(1000);
	}

	while (HomePK == AwayPK)
	{
		bool homeGoal = rand() % 100 < 75;
		bool awayGoal = rand() % 100 < 70;

		cout << HomeTeam.GetName()
			<< (homeGoal ? " 골!" : " 실축!") << endl;
		GameUtils::WaitMs(1000);

		cout << AwayTeam.GetName()
			<< (awayGoal ? " 골!" : " 실축!") << endl;
		GameUtils::WaitMs(1000);

		if (homeGoal) HomePK++;
		if (awayGoal) AwayPK++;

		cout << "현재 PK 스코어: "
			<< HomePK << " - " << AwayPK << endl;
		GameUtils::WaitMs(1000);

	}

	cout << "===== 승부차기 종료 =====" << endl;

	if (HomePK > AwayPK)
	{
		cout << "승부차기 승자: " << HomeTeam.GetName() << endl;
		HomeScore++;
	}
	else
	{
		cout << "승부차기 승자: " << AwayTeam.GetName() << endl;
		AwayScore++;
	}
	GameUtils::NextScreen();
}