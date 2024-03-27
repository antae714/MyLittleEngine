#pragma once

/** ���� Ŭ���� �Դϴ�. */
class ENGINEMODULEAPI Engine
{
public:
	Engine();
	~Engine();

public:
	/** ������ ���� �մϴ�. */
	void Run();
	/** 
	* ������ ���������� ��ȯ�մϴ�.
	* @return ������ �������̶�� ���Դϴ�. 
	*/
	bool IsEngineRun();
	/** ������ �ʱ�ȭ ���ݴϴ�. */
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
	/** ������ ���������� ���� �Դϴ�. */
	bool bIsEngineRun;

	/** ������ ���� �ð����� Ŭ���� �Դϴ�. */
	class Timer* timer;
	/** ������ ���۽ð� �Դϴ�. */
	double engineStartTime;
	/** ������ �ð� �����Դϴ�. */
	double fixedTimeStep;
	/** ���� ������ �ð��� �����صӴϴ�. */
	double accumulatedFixedTime;

	class World* mainWorld;
	class IRenderer* renderer;

private:

	//////////////////////// 
	//�ð� ������ �����Դϴ�.
	double testTime;
	int updateCount;
	int fixedUpdateCount;
};

