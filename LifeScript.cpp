

#include <iostream>
#include <windows.h> 
#include <stdio.h>
#include <conio.h>
#include <array>

void CursorVisible(HANDLE Handle,bool visible) {
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(Handle, &cursorInfo);
	cursorInfo.bVisible = visible;
	SetConsoleCursorInfo(Handle, &cursorInfo);
}
struct Field
{
	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	static constexpr size_t width = 20;
	static constexpr size_t height = 20;
	char map[height][width] = {};
	size_t yblock = width / 2;
	size_t xblock = height / 2;

	void draw()
	{
		
		
		
		SetConsoleCursorPosition(Handle, { 0,0 });
		for (short i = 1; i < height; i++) {
			std::cout << std::endl;
			for (size_t f = 1; f < width; f++) {
				if (map[i][f] == 1 or i == yblock && f == xblock) {
					std::cout << u8"\u25FC ";
				}
				else {
					std::cout << u8"\u25FB ";

				}

			}
		}
	}
	bool read()
	{
		char keys = _getch();
		if (keys == 'w') {
			yblock -= 1;
		}
		else if (keys == 's') {
			yblock += 1;
		}
		else if (keys == 'a') {
			xblock -= 1;
		}
		else if (keys == 'd') {
			xblock += 1;
		}
		else if (keys == '\r') {
			return false;
		}
		else if (keys == ' ') {
			map[yblock][xblock] = 1;
		}
		return true;
	}

	size_t getNeborsCount(size_t i, size_t f)
	{
		size_t s = 0;
		if (map[i - 1][f + 1] == 1) {
			s += 1;
		}
		if (map[i + 1][f - 1] == 1) {
			s += 1;
		}
		if (map[i - 1][f - 1] == 1) {
			s += 1;
		}
		if (map[i + 1][f + 1] == 1) {
			s += 1;
		}
		if (map[i - 1][f] == 1) {
			s += 1;
		}
		if (map[i + 1][f] == 1) {
			s += 1;
		}
		if (map[i][f - 1] == 1) {
			s += 1;
		}
		if (map[i][f + 1] == 1) {
			s += 1;
		}
		return s;
	}
	Field& operator=(const Field& other)
	{
		for (size_t i = 1; i < width; i++) {
			for (size_t f = 1; f < height; f++) {
				map[i][f] = other.map[i][f];
			}
		}
		yblock = other.yblock;
		xblock = other.xblock;
		return *this;
	}
};

int main()
{
	CursorVisible(GetStdHandle(STD_OUTPUT_HANDLE), false);

	SetConsoleOutputCP(CP_UTF8);

	Field field;

	bool var = true;
	while (var == true) {
		field.draw();
		var = field.read();
	}


	Field fieldNext;
	while (true)
	{
		for (int i = 1; i < field.height; i++) {
			for (int f = 1; f < field.width; f++) {
				size_t s = field.getNeborsCount(i, f);
				

				if (field.map[i][f] == 1 && s == 2 or field.map[i][f] == 1 && s == 3) {
					fieldNext.map[i][f] = 1;
				}
				else if (field.map[i][f] == 1 && s > 3 or field.map[i][f] == 1 && s < 2)
				{
					fieldNext.map[i][f] = 0;
				}
				else if (field.map[i][f] == 0 && s == 3) {
					fieldNext.map[i][f] = 1;
				}
				else
					fieldNext.map[i][f] = field.map[i][f];
			}
		}
		field = fieldNext;
		field.draw();
		Sleep(20);
	}

}

