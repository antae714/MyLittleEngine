#pragma once

/** �ð��� ������ Ŭ���� �Դϴ�. */
class ENGINEMODULEAPI Timer
{
public:
	Timer();

public:
	/** ���� ī������ �󵵸� �������ݴϴ�. */
	void Init();
	/** ����ð��� �ð������� �������ݴϴ�. */
	void TimeUpdate();
	/** �ð������� �����ɴϴ�. */
	double GetDeltaTime() { return deltaTime; }
	/** ����ð��� �����ɴϴ�. ����ð��� TimeUpdate�� ȣ���� �����Դϴ�.*/
	double _GetCurrentTime() { return currentTimeCounter.QuadPart * counterToMiliSecond; }

private:
	/** ���� ī������ ���Դϴ�. */
	LARGE_INTEGER frequency;
	/** ���� ī���͸� �̸���ũ ������ �ٲ��ֱ� ���� �ʿ��� �����Դϴ�. */
	double counterToMiliSecond;
	/** ���� �ð� ī���� �Դϴ�. */
	LARGE_INTEGER previousTimeCounter;
	/** ���� �ð� ī���� �Դϴ�. */
	LARGE_INTEGER currentTimeCounter;
	/** ������ ���� �ð� ���� �Դϴ�. */
	double deltaTime;
};

