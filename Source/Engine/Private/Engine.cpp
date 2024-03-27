#include "Enginepch.h"
#include "Engine.h"
#include "timer.h"
#include "GameFramework/World.h"
#include "GameFramework/Level.h"
#include "Module/ModuleBase.h"
#include "ConsoleRendererExample.h"
#include "ConsoleRenderer.h"


#include "iostream"
using namespace std;


struct Vector
{
	float x;
	float y;
};

Vector g_Player = { 0,0 };
COORD g_Player_MoveVec = { 0,0 };
float g_Speed = 0.25f;

Engine::Engine() : timer(nullptr), mainWorld(nullptr), bIsEngineRun(false), fixedTimeStep(0.0), accumulatedFixedTime(0.0)
{

}

Engine::~Engine()
{
	if (timer)
	{
		delete timer;
		timer = nullptr;
	}
	if (mainWorld)
	{
		delete mainWorld;
		mainWorld = nullptr;
	}
}

void Engine::Run()
{
	Initialize();
	bIsEngineRun = true;
	EngineLoop();
}

bool Engine::IsEngineRun()
{
	return bIsEngineRun;
}

void Engine::Initialize()
{






	timer = new Timer();
	mainWorld = new World();
	renderer = new ConsoleRenderer();
	renderer->Init();
	ConsoleRendererExample::ScreenInit();

	engineStartTime = timer->_GetCurrentTime();
	fixedTimeStep = 1.0 / 60.0 * 1000.0;
	testTime = 0;
	fixedUpdateCount = 0;
	updateCount = 0;
	//ModuleBase* CoreModule = ModuleManager::LoadModule((L"Core.dll"));
	//ModuleBase* ContentsModule = ModuleManager::LoadModule((L"Contents.dll"));
}

void Engine::EngineLoop()
{
	BeginPlay();


	while (IsEngineRun())
	{
		UpdateTime();
		ProcessInput();
		FixedUpdate();
		Update();
		Render();
	}

	EndPlay();
}

void Engine::BeginPlay()
{
	timer->Init();
}

void Engine::UpdateTime()
{
	timer->TimeUpdate();
}

void Engine::ProcessInput()
{
	g_Player_MoveVec = { 0,0 };
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{ //����
		g_Player_MoveVec.X = -1;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{ //������
		g_Player_MoveVec.X = +1;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{ //��
		g_Player_MoveVec.Y = -1;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{ //�Ʒ�
		g_Player_MoveVec.Y = +1;
	}
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{ //����
		bIsEngineRun = false;
	}
}

void Engine::FixedUpdate()
{
	double deltaTime = timer->GetDeltaTime();
	deltaTime += accumulatedFixedTime;

	while (deltaTime > 0.0)
	{
		++fixedUpdateCount;
		/*
		�Ƚ��� ������Ʈ �ϴ� ����
		*/
		deltaTime -= fixedTimeStep;


		g_Player.x += g_Player_MoveVec.X * fixedTimeStep * g_Speed;
		g_Player.y += g_Player_MoveVec.Y * fixedTimeStep * g_Speed;

		if (g_Player.x < 0) g_Player.x = 0;
		if (g_Player.x >= ConsoleRendererExample::ScreenWidth()) g_Player.x = ConsoleRendererExample::ScreenWidth() - 1;
		if (g_Player.y < 0) g_Player.y = 0;
		if (g_Player.y >= ConsoleRendererExample::ScreenHeight()) g_Player.y = ConsoleRendererExample::ScreenHeight() - 1;
	}

	accumulatedFixedTime = deltaTime;

}

void Engine::Update()
{
	updateCount++;

	//g_Player.x += g_Player_MoveVec.X * timer->GetDeltaTime() * g_Speed;
	//g_Player.y += g_Player_MoveVec.Y * timer->GetDeltaTime() * g_Speed;

	//if (g_Player.x < 0) g_Player.x = 0;
	//if (g_Player.x >= ConsoleRenderer::ScreenWidth()) g_Player.x = ConsoleRenderer::ScreenWidth() - 1;
	//if (g_Player.y < 0) g_Player.y = 0;
	//if (g_Player.y >= ConsoleRenderer::ScreenHeight()) g_Player.y = ConsoleRenderer::ScreenHeight() - 1;

}

void Engine::Render()
{
	testTime += timer->GetDeltaTime();
	if (testTime >= 1000)
	{
		cout << "updateCount : " << updateCount << "\t fixedUpdateCount : " << fixedUpdateCount << endl;
		fixedUpdateCount = 0;
		updateCount = 0;
		testTime = 0;
	}
	ConsoleRenderer* consoleRenderer = dynamic_cast<ConsoleRenderer*>(renderer);

	consoleRenderer->BufferClear();
	consoleRenderer->SetChar(g_Player.x, g_Player.y, 'P', FG_WHITE);
	consoleRenderer->BufferChange();

	return;
	ConsoleRendererExample::ScreenClear();
	ConsoleRendererExample::ScreenSetString(0, 0, "Hello �ȳ�", FG_PINK_DARK);
	ConsoleRendererExample::ScreenSetChar(g_Player.x, g_Player.y, 'P', FG_WHITE);
	ConsoleRendererExample::ScreenFlipping();
}

void Engine::EndPlay()
{
	renderer->EndPlay();
	ConsoleRendererExample::ScreenRelease();
}
