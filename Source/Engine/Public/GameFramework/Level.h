#pragma once

#include "Containers/DynamicArray.h"
#include "Containers/String.h"
#include "Template/Factory.h"

/**
 * 게임 오브젝트들을 들고있을 레벨입니다.
 */
class ENGINEMODULEAPI Level
{
public:
	Level();
	virtual ~Level();

public:	
	/**
	 * 레벨을 갱신합니다.
	 * @param TickTime 틱 시간
	 */
	virtual void BeginPlay();

	/** 레벨을 갱신 합니다. */
	void UpdateLevel(float TickTime);
	
	/** 레벨을 끝냅니다. */
	virtual void EndPlay();

	/**
	 * 레벨의 이름을 반환합니다.
	 * @return 레벨의 이름
	 */
	String GetName() { return name; }
	
	/**
	  * 월드 설정을 반환합니다.
	  * @return 월드 설정 객체 포인터
	  */
	class WorldSettings* GetWorldSettings();
	void SetWorldSettings(class WorldSettings* _worldSetting);

	DynamicArray<class Actor*>& GetActorArray();
	/**
	 * 액터를 추가합니다.
	 * @param actor 추가할 액터 객체
	 */
	void AddActor(class Actor* actor);
    
	/** 
	 * 액터를 제거합니다.
	 * @param actor 제거할 액터 객체
     */
	void RemoveActor(class Actor* actor);

protected:
	/** 레벨에 있는 액터 배열 */
	DynamicArray<class Actor*> actors;

	/** 월드 설정 객체 포인터 */
	class WorldSettings* worldSettings;

	/** 월드 이름 */
	String name;
};

class ENGINEMODULEAPI LevelFactory : public Factory<Level, String> {};

