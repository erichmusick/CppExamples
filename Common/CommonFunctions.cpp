#include <Windows.h>

namespace Common
{

	/**
	 * Source: http://stackoverflow.com/questions/15770853/how-to-use-setconsolecursorposition-func
	 */
	void GoToXY(int column, int line)
	{
		// Create a COORD structure and fill in its members.
		// This specifies the new position of the cursor that we will set.
		COORD coord;
		coord.X = column;
		coord.Y = line;

		// Obtain a handle to the console screen buffer.
		// (You're just using the standard console, so you can use STD_OUTPUT_HANDLE
		// in conjunction with the GetStdHandle() to retrieve the handle.)
		// Note that because it is a standard handle, we don't need to close it.
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		// Finally, call the SetConsoleCursorPosition function.
		if (!SetConsoleCursorPosition(hConsole, coord))
		{
			// Uh-oh! The function call failed, so you need to handle the error.
			// You can call GetLastError() to get a more specific error code.
			// ...
		}
	}

	/**
	 * Taken from http://www.cplusplus.com/articles/4z18T05o/
	 */
	void ClearScreen()
	{
		HANDLE                     hStdOut;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		DWORD                      count;
		DWORD                      cellCount;
		COORD                      homeCoords = { 0, 0 };

		hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hStdOut == INVALID_HANDLE_VALUE) return;

		/* Get the number of cells in the current buffer */
		if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
		cellCount = csbi.dwSize.X *csbi.dwSize.Y;

		/* Fill the entire buffer with spaces */
		if (!FillConsoleOutputCharacter(
			hStdOut,
			(TCHAR) ' ',
			cellCount,
			homeCoords,
			&count
			)) return;

		/* Fill the entire buffer with the current colors and attributes */
		if (!FillConsoleOutputAttribute(
			hStdOut,
			csbi.wAttributes,
			cellCount,
			homeCoords,
			&count
			)) return;

		/* Move the cursor home */
		SetConsoleCursorPosition(hStdOut, homeCoords);
	}

}