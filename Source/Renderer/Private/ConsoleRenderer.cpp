#include "ConsoleRenderer.h"
#include <stdio.h>
#include "GameFramework/World.h"
#include "GameFramework/Level.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ConsoleRenderComponent.h"

ConsoleRenderer::ConsoleRenderer() : buffer{ 0,0 }, currentBufferIndex(0), ScreenSize{ 0,0 }
{
}

void ConsoleRenderer::Init()
{
	HANDLE Console =  GetStdHandle(STD_OUTPUT_HANDLE);
	HWND consoleWindow = GetConsoleWindow();

	CONSOLE_FONT_INFOEX fontInfoEX;
	fontInfoEX.cbSize = sizeof(fontInfoEX);
	GetCurrentConsoleFontEx(Console, false, &fontInfoEX);
	fontInfoEX.dwFontSize.X = 2;
	fontInfoEX.dwFontSize.Y = 2;
	lstrcpyW(fontInfoEX.FaceName, L"Consolas");
	
	SetCurrentConsoleFontEx(Console, false, &fontInfoEX);
	
	SetConsoleCursorInfo(Console, &CONSOLE_CURSOR_INFO{ 1, false });
	MoveWindow(consoleWindow, 0, 0, 1936, 1120, true);
	ShowScrollBar(consoleWindow, SB_BOTH, false);
	
	CONSOLE_SCREEN_BUFFER_INFOEX ConsoleInfo;
	ConsoleInfo.cbSize = sizeof(ConsoleInfo);
	GetConsoleScreenBufferInfoEx(Console, &ConsoleInfo);

	buffer[0] = CreateConsoleScreenBuffer(GENERIC_WRITE | GENERIC_READ, 0, 0, CONSOLE_TEXTMODE_BUFFER, 0);
	buffer[1] = CreateConsoleScreenBuffer(GENERIC_WRITE | GENERIC_READ, 0, 0, CONSOLE_TEXTMODE_BUFFER, 0);
	ScreenSize = ConsoleInfo.dwSize;
}

void ConsoleRenderer::EndPlay()
{
	CloseHandle(buffer[0]);
	CloseHandle(buffer[1]);
}



void ConsoleRenderer::Render(World* world)
{
	BufferClear();

	for (auto& item : world->GetMainLevel()->GetActorArray())
	{
		if (item->GetComponent<ConsoleRenderComponent>());
	}
	

	
	BufferChange();
}

void ConsoleRenderer::BufferChange()
{
	SetConsoleActiveScreenBuffer(buffer[currentBufferIndex]);
	currentBufferIndex = !!!currentBufferIndex;
}

void ConsoleRenderer::BufferClear()
{
	DWORD NumberOfCharsWritten;
	FillConsoleOutputCharacter(buffer[currentBufferIndex], ' ', ScreenSize.X * ScreenSize.Y, { 0,0 }, &NumberOfCharsWritten);
}

int ConsoleRenderer::GetWidth()
{
	return ScreenSize.X;
}

int ConsoleRenderer::GetHeight()
{
	return ScreenSize.Y;
}

void ConsoleRenderer::processWindowSizeChange()
{
}

bool ConsoleRenderer::SetChar(int x, int y, char ch, WORD attr)
{
	COORD	cdPos;
	BOOL	bRval = FALSE;
	DWORD	dwCharsWritten;
	cdPos.X = x;
	cdPos.Y = y;

	bRval = FillConsoleOutputCharacter(buffer[currentBufferIndex], ch, 3, cdPos, &dwCharsWritten);
	if (bRval == false) printf("Error, FillConsoleOutputCharacter()\n");

	bRval = FillConsoleOutputAttribute(buffer[currentBufferIndex], attr, 3, cdPos, &dwCharsWritten);
	if (bRval == false) printf("Error, FillConsoleOutputAttribute()\n");
	return bRval;
}
