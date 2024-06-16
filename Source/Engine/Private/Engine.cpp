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

Engine* Engine::GEngine = nullptr;

Engine::Engine() : 
	timer(nullptr), 
	mainWorld(nullptr),
	renderer(nullptr), 
	inputProcessor(nullptr),
	isEngineRunning(false),
	accumulatedFixedTime(0.0),
	fixedTimeStep(0.0)
{
	_ASSERT(!GEngine);
	GEngine = this;
}

Engine::~Engine()
{
	if (timer) delete timer;
	if (mainWorld) delete mainWorld;
	//if (renderer) delete renderer;
	//if (inputProcessor) delete inputProcessor;


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


	fixedTimeStep = 1.0 / 60.0 * 1000.0;
}

InputSettings* Engine::GetInputSetting()
{
	return inputProcessor->GetEngineInputArray();
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
	WorldSettings* worldSetting = mainWorld->GetWorldSettings();
	worldSetting->playerController->ProcessInput(inputProcessor->GetEngineInputArray());
}

void Engine::FixedUpdate()
{
	double deltaTime = timer->GetDeltaTime();
	deltaTime += accumulatedFixedTime;

	while (deltaTime > 0.0)
	{
		mainWorld->FixedUpdate(fixedTimeStep);


		deltaTime -= fixedTimeStep;
	}

	accumulatedFixedTime = deltaTime;
}

void Engine::Update()
{
	mainWorld->Update(timer->GetDeltaTime());
}

void Engine::Render()
{
	renderer->BeginRender();
	renderer->EndRender();
}

void Engine::EndPlay()
{
	mainWorld->EndPlay();
	renderer->EndPlay();
	inputProcessor->EndPlay();
}
