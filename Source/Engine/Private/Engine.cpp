#include "Engine.h"
#include "timer.h"
#include "GameFramework/World.h"
#include "Module/ModuleBase.h"
#include "IInputProcessor.h"
#include "IRenderer.h"
#include "GameFramework/WorldSettings.h"
#include "Application/Application.h"


#include "iostream"


using namespace std;



//Vector g_Player = { 0,0 };
COORD g_Player_MoveVec = { 0,0 };
float g_Speed = 0.25f;

Engine* Engine::GEngine = nullptr;

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
	return isEngineRunning && !IApplication::GetSingletonInstance()->IsTerminated();
}

void Engine::Initialize()
{
	timer = new Timer();
	mainWorld = new World();
	renderer = RendererFactory::Get("WinGDIRenderer");
	inputProcessor = InputProcessorFactory::Get("window");


	engineStartTime = timer->_GetCurrentTime();
	fixedTimeStep = 1.0 / 60.0 * 1000.0;
	testTime = 0;
	fixedUpdateCount = 0;
	updateCount = 0;
}

InputSettings* Engine::GetInputSetting()
{
	return inputProcessor->getEngineInputArray();
}

void Engine::Terminate()
{
	isEngineRunning = false;
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
	worldSetting->playerController->ProcessInput(inputProcessor->getEngineInputArray());
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
	renderer->Render(mainWorld);
}

void Engine::EndPlay()
{
	renderer->EndPlay();
}
