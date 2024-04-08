#pragma once

#include "Containers/DynamicArray.h"
#include "Containers/String.h"
#include "Template/Factory.h"

/**
 * ���� ������Ʈ���� ������� �����Դϴ�.
 */
class ENGINEMODULEAPI Level
{
public:
	Level();
	virtual ~Level();

public:	
	/**
	 * ������ �����մϴ�.
	 * @param TickTime ƽ �ð�
	 */
	virtual void BeginPlay();

	/** ������ ���� �մϴ�. */
	void UpdateLevel(float TickTime);
	
	/** ������ �����ϴ�. */
	virtual void EndPlay();

	/**
	 * ������ �̸��� ��ȯ�մϴ�.
	 * @return ������ �̸�
	 */
	String GetName() { return name; }
	
	/**
	  * ���� ������ ��ȯ�մϴ�.
	  * @return ���� ���� ��ü ������
	  */
	class WorldSettings* GetWorldSettings();
	void SetWorldSettings(class WorldSettings* _worldSetting);

	DynamicArray<class Actor*>& GetActorArray();
	/**
	 * ���͸� �߰��մϴ�.
	 * @param actor �߰��� ���� ��ü
	 */
	void AddActor(class Actor* actor);
    
	/** 
	 * ���͸� �����մϴ�.
	 * @param actor ������ ���� ��ü
     */
	void RemoveActor(class Actor* actor);

protected:
	/** ������ �ִ� ���� �迭 */
	DynamicArray<class Actor*> actors;

	/** ���� ���� ��ü ������ */
	class WorldSettings* worldSettings;

	/** ���� �̸� */
	String name;
};

class ENGINEMODULEAPI LevelFactory : public Factory<Level, String> {};

