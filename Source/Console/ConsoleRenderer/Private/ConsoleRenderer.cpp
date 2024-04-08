#include "ConsoleRenderer.h"
#include "ConsoleConfig.h"
#include <stdio.h>
#include "GameFramework/World.h"
#include "GameFramework/Level.h"
#include "GameFramework/Actor.h"

#include "ConsoleWorldSetting.h"


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
	fontInfoEX.dwFontSize.Y = 8;
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

	ConsoleWorldSetting* worldSetting = dynamic_cast<ConsoleWorldSetting*>(world->getWorldSettings());
	
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			RenderData renderdata{ 10, 7, BG_BLACK };
			Vector pos;
			pos.x = j * 12;
			pos.y = i * 7;

			switch ((EObject)worldSetting->Map[i * 10 + j])
			{
			case EObject::Empty:
				renderdata.attribute = BG_GRAY;
				break;
			case EObject::Wall:
				renderdata.attribute = BG_RED;
				break;
			case EObject::Start:
				break;
			case EObject::Goal:
				break;

			default:
				break;
			}
			RenderObject(pos, renderdata);
		}
	}

	for (Actor* item : world->GetMainLevel()->GetActorArray())
	{
		ConsoleRenderComponent* renderComponent = item->GetComponent<ConsoleRenderComponent>();
		if (renderComponent)
		{
			RenderData& renderdata = renderComponent->renderData;
			Vector pos = item->GetPosition();

			RenderObject(pos, renderdata);
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

void ConsoleRenderer::RenderObject(Vector position, RenderData data)
{
	for (size_t i = position.x; i < position.x + data.row; i++)
	{
		for (size_t j = position.y; j < position.y + data.colum; j++)
		{
			SetChar(i, j, ' ', data.attribute);
		}
	}

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