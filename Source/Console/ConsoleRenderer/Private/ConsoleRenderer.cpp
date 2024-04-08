#include "ConsoleRenderer.h"
#include "ConsoleConfig.h"
#include <stdio.h>
#include "GameFramework/World.h"
#include "GameFramework/Level.h"
#include "GameFramework/Actor.h"

#include "ConsoleRenderComponent.h"

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
	fontInfoEX.dwFontSize.X = 8;
	fontInfoEX.dwFontSize.Y = 16;
	lstrcpyW(fontInfoEX.FaceName, L"Consolas");
	
	SetCurrentConsoleFontEx(Console, false, &fontInfoEX);

	SetConsoleCursorInfo(Console, &CONSOLE_CURSOR_INFO{ 1, false });
	//MoveWindow(consoleWindow, 0, 0, 960, 860, true);
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

	for (Actor* item : world->GetMainLevel()->GetActorArray())
	{
		ConsoleRenderComponent* renderComponent = item->GetComponent<ConsoleRenderComponent>();
		if (renderComponent)
		{
			RenderData& renderdata = renderComponent->renderData; 
			Vector pos = item->GetPosition();
			for (size_t i = pos.x; i < pos.x + renderdata.row; i++)
			{
				for (size_t j = pos.y; j < pos.y + renderdata.colum; j++)
				{
					SetChar(i, j, ' ', BG_WHITE);
				}
			}
		}
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
	SetAttribute(BG_BLACK);
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
bool ConsoleRenderer::SetAttribute(WORD attr)
{
	COORD	cdPos;
	bool	bRval = FALSE;
	DWORD	dwCharsWritten;
	//	int x,y;	

	cdPos.X = 0;
	cdPos.Y = 0;
	bRval = FillConsoleOutputAttribute(buffer[currentBufferIndex], attr, ScreenSize.X * ScreenSize.Y, cdPos, &dwCharsWritten);
	if (bRval == false)
	{
		printf("Error, FillConsoleOutputCharacter()\n");
		return bRval;
	}

	return bRval;
}