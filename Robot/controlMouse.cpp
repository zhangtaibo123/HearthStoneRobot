#include "ControlMouse.h"
#include "define.h"

ControlMouse *ControlMouse::self = NULL;

ControlMouse * ControlMouse::getInstance()
{
	if (self == NULL)
	{
		self = new ControlMouse();
	}
	return self;
}

void ControlMouse::touchPosition(double x, double y) //点击坐标位置
{
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, x / screenWidth * 65535, y / screenHeight * 65535, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	Sleep(1000);
}

void ControlMouse::playCard(double x, double y) //出牌
{
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, x / screenWidth * 65535, y / screenHeight * 65535, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	Sleep(1000);
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, 500.0 / screenWidth * 65535, 400.0 / screenHeight * 65535, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	Sleep(1000);
}

void ControlMouse::playCardToPlayer(double x, double y)
{
	touchPosition(x, y);
	Sleep(1000);
	double stepx = 800.0 - x;
	double stepy = 180.0 - y;
	for (int i = 0; i < 20; ++i)
	{
		x += stepx / 20;
		y += stepy / 20;
		mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, x / screenWidth * 65535, y / screenHeight * 65535, 0, 0);
		Sleep(100);
	}
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, 800.0 / screenWidth * 65535, 180.0 / screenHeight * 65535, 0, 0);
	Sleep(500);
	mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	Sleep(500);
}

void ControlMouse::moveToPosition(double x, double y) //移动到坐标位置
{
	mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, x / screenWidth * 65535, y / screenHeight * 65535, 0, 0);
	Sleep(500);
}

void ControlMouse::fightMonster(double x, double y, double x1, double y1)
{
	touchPosition(x, y);
	Sleep(500);
	touchPosition(x1, y1);
	Sleep(500);
}

ControlMouse::ControlMouse()
{
	hWnd = ::FindWindow("UnityWndClass", CARDGAME);
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);
	SetForegroundWindow(hWnd);
	::SetActiveWindow(hWnd);
	RECT rc;
	::GetWindowRect(hWnd, &rc);
	RECT rcClient;
	::GetClientRect(hWnd, &rcClient);
	POINT wnd;
	wnd.x = rcClient.left;
	wnd.y = rcClient.top;
	::ClientToScreen(hWnd, &wnd);
	::MoveWindow(hWnd, 0, 0, rc.right - rc.left, rc.bottom - rc.top, true);
	::GetWindowRect(hWnd, &rc);
}
