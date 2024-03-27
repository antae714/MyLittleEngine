#pragma once

/** 시간을 측정할 클래스 입니다. */
class ENGINEMODULEAPI Timer
{
public:
	Timer();

public:
	/** 성능 카운터의 빈도를 세팅해줍니다. */
	void Init();
	/** 현재시간과 시간간격을 갱신해줍니다. */
	void TimeUpdate();
	/** 시간간격을 가져옵니다. */
	double GetDeltaTime() { return deltaTime; }
	/** 현재시간을 가져옵니다. 현재시간은 TimeUpdate를 호출한 시점입니다.*/
	double _GetCurrentTime() { return currentTimeCounter.QuadPart * counterToMiliSecond; }

private:
	/** 성능 카운터의 빈도입니다. */
	LARGE_INTEGER frequency;
	/** 성능 카운터를 미리세크 단위로 바꿔주기 위해 필요한 변수입니다. */
	double counterToMiliSecond;
	/** 이전 시간 카운터 입니다. */
	LARGE_INTEGER previousTimeCounter;
	/** 현재 시간 카운터 입니다. */
	LARGE_INTEGER currentTimeCounter;
	/** 이전과 현재 시간 간격 입니다. */
	double deltaTime;
};

