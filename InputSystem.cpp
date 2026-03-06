#include "InputSystem.h"

Direction InputSystem::GetPlayerDirection()
{
	int choice;
	
	cout << "방향을 선택하세요" << endl;
	cout << "1. 왼쪽" << endl;
	cout << "2. 중앙" << endl;
	cout << "3.오른쪽" << endl;
	
	cin >> choice;
	
	return (Direction)(choice - 1);
}