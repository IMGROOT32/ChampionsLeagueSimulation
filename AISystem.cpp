#include "AISystem.h"

Direction AISystem::RandomDirection()
{
	int r = rand() % 3;
	if (r == 0)
		return LEFT;
	if (r == 1)
		return CENTER;
	return RIGHT;
}