#include "DirectionSystem.h"
#include <cstdlib>

using namespace std;

Direction DirectionSystem::PlayerShootDirection()
{
	int input;
	cout << "슈팅 방향을 선택하세요" << endl;
	cout << "[1] 왼쪽" << "[2] 중앙" << "[3] 오른쪽" << endl;
	cin >> input;

	if (input == 1)
		return LEFT;
	if (input == 2)
		return CENTER;
	return RIGHT;

}

Direction DirectionSystem::PlayerDefenceDirection()
{
	int input;
	cout << "수비 방향을 선택하세요" << endl;
	cout << "[1] 왼쪽" << "[2] 중앙" << "[3] 오른쪽" << endl;
	cin >> input;

	if (input == 1)
		return LEFT;
	if (input == 2)
		return CENTER;
	return RIGHT;
}