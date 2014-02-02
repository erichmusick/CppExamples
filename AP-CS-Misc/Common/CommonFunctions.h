namespace Common
{

	// Cursor positioning. 
	void GoToXY(int column, int line);	// 0-based index
	int GetCursorXPosition();
	int GetCursorYPosition();

	// Functions to clear a portion or the entire console window
	void ClearToEndOfLine();
	void ClearScreen();

	// Other
	// Determines the length of the string representation of the given integer value.
	int intLength(int val);
}