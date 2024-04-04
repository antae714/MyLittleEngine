#include "Engine.h"
#include "timer.h"
#include "GameFramework/World.h"
#include "Module/ModuleBase.h"
#include "ConsoleRendererExample.h"
#include "ConsoleRenderer.h"
#include "IInputProcessor.h"
#include "GameFramework/WorldSettings.h"


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

Engine::Engine() : 
	timer(nullptr), 
	mainWorld(nullptr),
	renderer(nullptr), 
	inputProcessor(nullptr),
	isEngineRunning(false),
	fixedTimeStep(0.0), 
	accumulatedFixedTime(0.0)
{
	_ASSERT(!GEngine);
	GEngine = this;
}

Engine::~Engine()
{
	if (timer) delete timer;
	if (mainWorld) delete mainWorld;
	if (renderer) delete renderer;
	if (inputProcessor) delete inputProcessor;


}

void Engine::Run()
{
	Initialize();
	isEngineRunning = true;
	EngineLoop();
}

bool Engine::IsEngineRun()
{
	return isEngineRunning;
}

void Engine::Initialize()
{
	timer = new Timer();
	mainWorld = new World();
	renderer = new ConsoleRenderer();
	inputProcessor = InputProcessorFactory::Get("window");


	engineStartTime = timer->_GetCurrentTime();
	fixedTimeStep = 1.0 / 60.0 * 1000.0;
	testTime = 0;
	fixedUpdateCount = 0;
	updateCount = 0;
	//ModuleBase* CoreModule = ModuleManager::LoadModule((L"Core.dll"));
	//ModuleBase* ContentsModule = ModuleManager::LoadModule((L"Contents.dll"));
}

InputSettings* Engine::GetInputSetting()
{
	return inputProcessor->getEngineInputArray();
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
	renderer->Init();
	ConsoleRendererExample::ScreenInit();
	timer->Init();
	inputProcessor->Init();


	mainWorld->BeginPlay();
}

void Engine::UpdateTime()
{
	timer->TimeUpdate();
}

void Engine::ProcessInput()
{
	inputProcessor->ProcessInput();
	WorldSettings* worldSetting = mainWorld->getWorldSettings();
	worldSetting->playerController->processInput(inputProcessor->getEngineInputArray());

	g_Player_MoveVec = { 0,0 };
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{ //왼쪽
		g_Player_MoveVec.X = -1;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{ //오른쪽
		g_Player_MoveVec.X = +1;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{ //위
		g_Player_MoveVec.Y = -1;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{ //아래
		g_Player_MoveVec.Y = +1;
	}
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{ //종료
		isEngineRunning = false;
	}
}

void Engine::FixedUpdate()
{

	double deltaTime = timer->GetDeltaTime();
	deltaTime += accumulatedFixedTime;

	while (deltaTime > 0.0)
	{
		mainWorld->FixedUpdate(fixedTimeStep);

		++fixedUpdateCount;
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
	mainWorld->Update(timer->GetDeltaTime());
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
}

void Engine::EndPlay()
{
	renderer->EndPlay();
	ConsoleRendererExample::ScreenRelease();
}
