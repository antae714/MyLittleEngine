#pragma once

/** ���� Ŭ���� */
class ENGINEMODULEAPI Engine
{
public:
	Engine();
	virtual ~Engine();

public:
	/** ���� ���� */
	void Run();

	/** 
	* ������ ���������� ��ȯ
	* @return ������ ���� ���̸� true 
	*/
	bool IsEngineRun();

	/** ���� �ʱ�ȭ */
	void Initialize();

private:
	/** ���� ���� ���� */
	void EngineLoop();

	/** ���� ��� �ʱ�ȭ */
	void BeginPlay();

	/** �ð� ���� */
	void UpdateTime();

	/** �Է� ó�� */
	void ProcessInput();

	/** �������� ������Ʈ */
	void FixedUpdate();

	/** ������Ʈ */
	void Update();

	/** ȭ�鿡 �׷��ֱ� */
	void Render();

	/** ���� ���� */
	void EndPlay();

private:
	/** ������ ���������� ���� */
	bool isEngineRunning;

	/** ���� �ð� ���� Ŭ���� */
	class Timer* timer;

	/** ���� ���۽ð� */
	double engineStartTime;

	/** ������ �ð� ���� */
	double fixedTimeStep;

	/** ������ ������ �ð� */
	double accumulatedFixedTime;
	
	/** ���� ���� */
	class World* mainWorld;
	// ���� ��������� ���带 �ø��ϴ�.
	class IInputProcessor* inputProcessor;

	/** ������ */
	class IRenderer* renderer;
private:

	//////////////////////// 
	//�ð� ������ ������
	double testTime;
	int updateCount;
	int fixedUpdateCount;
};

