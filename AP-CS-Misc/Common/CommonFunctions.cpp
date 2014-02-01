#include <Windows.h>

namespace Common
{

	void GoToXY(int x, int y) {
		COORD c;
		c.X = x;
		c.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	}

	int GetCursorXPosition()
	{
		CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;

		// Obtain a handle to the console screen buffer.
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		// Finally, call the SetConsoleCursorPosition function.
		if (!GetConsoleScreenBufferInfo(hConsole, &screenBufferInfo))
		{
			return 0;
		}

		return screenBufferInfo.dwCursorPosition.X;
	}

	int GetCursorYPosition()
	{
		CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;

		// Obtain a handle to the console screen buffer.
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		// Finally, call the SetConsoleCursorPosition function.
		if (!GetConsoleScreenBufferInfo(hConsole, &screenBufferInfo))
		{
			return 0;
		}

		return screenBufferInfo.dwCursorPosition.Y;
	}

	void ClearToEndOfLine()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		DWORD count;

		// Obtain a handle to the console screen buffer.
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		/* Get the number of cells in the current buffer */
		if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
		int columns = csbi.dwSize.Y;

		if (!FillConsoleOutputCharacter(
			hConsole,
			(TCHAR) ' ',
			columns,
			csbi.dwCursorPosition,
			&count
			)) return;

		if (!FillConsoleOutputAttribute(
			hConsole,
			csbi.wAttributes,
			columns,
			csbi.dwCursorPosition,
			&count
			)) return;
	}

	void ClearScreen()
	{
		COORD coord;
		DWORD written;
		CONSOLE_SCREEN_BUFFER_INFO info;

		coord.X = 0;
		coord.Y = 0;

		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

		GetConsoleScreenBufferInfo(console, &info);
		FillConsoleOutputCharacter(
			console,
			' ',
			info.dwSize.X * info.dwSize.Y, 
			coord, 
			&written);

		FillConsoleOutputAttribute(
			console, 
			info.wAttributes,
			info.dwSize.X * info.dwSize.Y, 
			coord, 
			&written);

		GoToXY(0, 0);
	}
}