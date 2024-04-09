#include "ConsolePathFinder.h"
#include "GameFramework/Actor.h"
#include "ConsoleWorldSetting.h"


void ConsolePathFinder::Update(float deltaTime)
{
	Base::Update(deltaTime);
	Vector playerPos = GetOwner()->GetPosition();
	if (CalculatedPos != playerPos)
	{
		CalculatePath(playerPos, worldSettings->GetGoalPoint());
	}
}

enum EMAZETYPE { PATH, WALL, VISIT, BACK }; // 0,1,2,3
struct PathFindPos
{
	Vector pos;
	int Direct;
	PathFindPos() : pos(0), Direct(0) {}
	PathFindPos(Vector _pos, int _Direct) : pos(_pos), Direct(_Direct) {}

	PathFindPos Sum(Vector moveDirection)
	{
		PathFindPos resultPosition;
		resultPosition.pos = pos + moveDirection;
		return resultPosition;
	}

	static bool Compare(PathFindPos fisrt, PathFindPos second)
	{
		return fisrt.pos == second.pos;
	}
	
	PathFindPos GetDirectPosition()
	{
		static const Vector DirectArray[] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 }, };
		return Sum(DirectArray[Direct]);
	}
};

void ConsolePathFinder::CalculatePath(Vector pos, Vector targetPos)
{
	CalculatedPos = pos;
	PathFindPos startpos{ 0, 0 };
	PathFindPos GoalPosition{ targetPos - Vector(1,1), 0};

	DynamicArray<PathFindPos> stack;
	startpos.pos.x = (int)CalculatedPos.y;
	startpos.pos.y = (int)CalculatedPos.x;
	stack.Add(startpos);

	int tempMap[10][10];
	memcpy(tempMap, worldSettings->Map, sizeof(int) * 100);
	auto GetMazeData = [&tempMap](PathFindPos position) -> int& { return tempMap[(int)position.pos.x][(int)position.pos.y ]; };

	GetMazeData(startpos) = VISIT;

	while (!PathFindPos::Compare(*stack.Back(), GoalPosition) && !stack.IsEmpty())
	{
		PathFindPos& currentPosition = *stack.Back();
		
		if (currentPosition.Direct >= 4)
		{
			stack.RemoveIndex(stack.GetCount() - 1);
			GetMazeData(currentPosition) = BACK;
			continue;
		}

		PathFindPos movePosition = currentPosition.GetDirectPosition();
		++currentPosition.Direct;


		int& visitData = GetMazeData(movePosition);
		if (visitData == 0)
		{
			stack.Add(movePosition);
			visitData = VISIT;
		}
	}

	Path.Clear();
	for (auto& item : stack)
	{
		Path.Add(item.pos);
	}
}
