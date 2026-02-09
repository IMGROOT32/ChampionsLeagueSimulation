#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <Windows.h>
#include <string>
#include <limits>

using namespace std;

namespace GameUtils
{
	void ClearScreen();
	void NextScreen();
	void WaitMs(int ms);
}