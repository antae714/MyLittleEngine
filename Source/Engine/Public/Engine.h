#pragma once

/** 엔진 클래스 */
class ENGINEMODULEAPI Engine
{
public:
	Engine();
	virtual ~Engine();

public:
	/** 엔진 시작 */
	void Run();

	/** 
	* 엔진이 실행중인지 반환
	* @return 엔진이 실행 중이면 true 
	*/
	bool IsEngineRun();

	/** 엔진 초기화 */
	void Initialize();

private:
	/** 엔진 메인 루프 */
	void EngineLoop();

	/** 엔진 요소 초기화 */
	void BeginPlay();

	/** 시간 갱신 */
	void UpdateTime();

	/** 입력 처리 */
	void ProcessInput();

	/** 고정간격 업데이트 */
	void FixedUpdate();

	/** 업데이트 */
	void Update();

	/** 화면에 그려주기 */
	void Render();

	/** 엔진 종료 */
	void EndPlay();

private:
	/** 엔진이 실행중인지 여부 */
	bool isEngineRunning;

	/** 게임 시간 측정 클래스 */
	class Timer* timer;

	/** 엔진 시작시간 */
	double engineStartTime;

	/** 고정된 시간 간격 */
	double fixedTimeStep;

	/** 누적된 고정된 시간 */
	double accumulatedFixedTime;
	
	/** 메인 월드 */
	class World* mainWorld;
	// 툴이 만들어질때 월드를 늘립니다.
	class IInputProcessor* inputProcessor;

	/** 렌더러 */
	class IRenderer* renderer;
private:

	//////////////////////// 
	//시간 측정용 변수들
	double testTime;
	int updateCount;
	int fixedUpdateCount;
};

