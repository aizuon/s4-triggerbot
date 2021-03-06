﻿#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <string>

using namespace std;

HWND hWnd = FindWindowA(NULL, "S4 Client");
HDC DC = GetWindowDC(hWnd);
COLORREF color;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

enum Console_Color
{
	Black,
	Dark_Blue,
	Green,
	Blue_Grey,
	Brown,
	Purple,
	Khaki,
	Light_Grey,
	Grey,
	Light_Blue,
	Light_Green,
	Cyan,
	Red,
	Pink,
	Yellow,
	White
};

void sendInput(void)
{
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	Sleep(300);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	return;
}

void trigger()
{
	int rTotal = 0;
	int gTotal = 0;
	int bTotal = 0;
	int rAv, gAv, bAv;
	for (int j = 479; j <= 480; j++)
	{
		for (int i = 913; i <= 915; i++)
		{
			color = GetPixel(DC, i, j);
			rTotal += GetRValue(color);
			gTotal += GetGValue(color);
			bTotal += GetBValue(color);
		}
	}
	rAv = rTotal / 6;
	gAv = gTotal / 6;
	bAv = bTotal / 6;
	SetConsoleTextAttribute(hConsole, Console_Color::Red);
	cout << rAv << endl;
	SetConsoleTextAttribute(hConsole, Console_Color::Green);
	cout << gAv << endl;
	SetConsoleTextAttribute(hConsole, Console_Color::Light_Blue);
	cout << bAv << endl;
	SetConsoleTextAttribute(hConsole, Console_Color::White);
	if (rAv >= 200 && gAv <= 30 && bAv <= 30)
	{
		sendInput();
		SetConsoleTextAttribute(hConsole, Console_Color::Cyan);
		cout << "triggered" << endl;
		SetConsoleTextAttribute(hConsole, Console_Color::White);
	}
	SetConsoleTextAttribute(hConsole, Console_Color::Pink);
	cout << "________________________________________" << endl;
	SetConsoleTextAttribute(hConsole, Console_Color::White);
	return;
}

int main(void)
{
	bool isOn = false;
	SetConsoleTitle(_T("triggerbot"));
	if (hWnd == NULL)
	{
		SetConsoleTextAttribute(hConsole, Console_Color::Red);
		cout << "cannot find s4 client\n";
		SetConsoleTextAttribute(hConsole, Console_Color::White);
		system("PAUSE");
		return 0;
	}

	SetConsoleTextAttribute(hConsole, Console_Color::Yellow);
	cout << "press lshift to enable, rshift to disable the triggerbot\n";
	cout << "hold right click to use the triggerbot\n";
	cout << "press end to exit\n";
	SetConsoleTextAttribute(hConsole, Console_Color::White);
	for (;;)
	{
		if (GetAsyncKeyState(VK_END))
			return 1;

		else if (GetAsyncKeyState(VK_RBUTTON))
			trigger();

		else if (GetAsyncKeyState(VK_LSHIFT))
		{
			isOn = true;
			SetConsoleTitle(_T("triggerbot on"));
		}

		else if (GetAsyncKeyState(VK_RSHIFT))
		{
			isOn = false;
			SetConsoleTitle(_T("triggerbot off"));
		}

		if (isOn)
			trigger();
		Sleep(13);
	}
	return 0;
}
