#pragma once

#include "Containers/List.h"
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

	List<class Actor*>& GetActorList();
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

public:
	class World* ownedWorld;

protected:

	/** ������ �ִ� ���� �迭 */
	List<class Actor*> actorList;

	/** ���� ���� ��ü ������ */
	class WorldSettings* worldSettings;

	/** ���� �̸� */
	String name;
};

class ENGINEMODULEAPI LevelFactory : public Factory<Level, String> {};

