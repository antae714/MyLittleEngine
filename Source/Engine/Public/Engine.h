#pragma once

/** 엔진 클래스 입니다. */
class ENGINEMODULEAPI Engine
{
public:
	Engine();
	~Engine();

public:
	/** 엔진을 시작 합니다. */
	void Run();
	/** 
	* 엔진이 실행중인지 반환합니다.
	* @return 엔진이 실행중이라면 참입니다. 
	*/
	bool IsEngineRun();
	/** 엔진을 초기화 해줍니다. */
	void Initialize();

private:
	void EngineLoop();
	void BeginPlay();
	void UpdateTime();
	void ProcessInput();
	void FixedUpdate();
	void Update();

	void Render();

	void EndPlay();

private:
	/** 엔진이 실행중인지 여부 입니다. */
	bool bIsEngineRun;

	/** 게임을 위한 시간측정 클래스 입니다. */
	class Timer* timer;
	/** 엔진의 시작시간 입니다. */
	double engineStartTime;
	/** 고정된 시간 간격입니다. */
	double fixedTimeStep;
	/** 이전 고정된 시간을 저장해둡니다. */
	double accumulatedFixedTime;

	class World* mainWorld;
	class IRenderer* renderer;

private:

	//////////////////////// 
	//시간 측정용 변수입니다.
	double testTime;
	int updateCount;
	int fixedUpdateCount;
};

