#include "GameUtils.h"

namespace GameUtils
{
	void NextScreen()
	{
		system("pause");
		cout << endl;
	}

	void WaitMs(int ms)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	}


	void ClearScreen()
	{
		system("cls");
	}

	wstring ReadWLine()
	{
		HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
		if (hIn == INVALID_HANDLE_VALUE) return L"";

		wchar_t buffer[1024];
		DWORD read = 0;

		if (!ReadConsoleW(hIn, buffer, 1024, &read, nullptr))
			return L"";

		wstring w(buffer, read);

		while (!w.empty() && (w.back() == L'\r' || w.back() == L'\n'))
			w.pop_back();

		return w;
	}
}