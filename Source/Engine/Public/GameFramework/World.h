#pragma once

#include "Containers/DynamicArray.h"
#include "Containers/List.h"
#include "Containers/String.h"

class Level;

/**
 * �������� ������ �����Դϴ�.
 * ����) PlayWorld, EditWorld, SimpleViewWorld
 */
class ENGINEMODULEAPI World
{
public:
	World();
	virtual  ~World();

public:
	/** ���带 �ʱ�ȭ �մϴ�. */
	void BeginPlay();
	
	/**
	  * ������ �������� ���带 �����մϴ�.
	  * @param fixedTickTime ������ ���� �ð�
	  */
	void FixedUpdate(float fixedTickTime);

	/**
	   * ���带 �����մϴ�.
	   * @param tickTime ������ �ð� ����
	   */
	void Update(float tickTime);
	
	/** ���带 �����ϴ�. */
	void EndPlay();

	/**
	 * ���� ������ �����մϴ�.
	 * @param mainLevel ���� ���� ��ü
	 */
	void SetMainLevel(Level* mainLevel);
	
	/**
	 * ���� ������ �����ɴϴ�.
	 * @return ���� ���� ��ü ������
	 */
	Level* GetMainLevel();

	DynamicArray<Level*>& GetSubLevel();

	/**
	 * ���� ���� ��ü�� �����ɴϴ�.
	 * @return ���� ���� ��ü ������
	 */
	class WorldSettings* getWorldSettings();

	/**
	 * ������ �߰��մϴ�.
	 * @param level �߰��� ���� ��ü
	 */
	void AddLevel(Level* level);

	/**
	 * ������ �����մϴ�.
	 * @param level ������ ���� ��ü
	 */
	void RemoveLevel(Level* level);

	/** ������ �߰��մϴ�. (�̸�����) */
	[[deprecated("This function has not been implemented yet")]]
	void AddLevelByName(String LevelName);
	
	/**
	 * ������ �����մϴ�. (�̸�����)
	 * @param LevelName ������ ������ �̸�
	 */
	void RemoveLevelByName(String LevelName);

	void SetMainCamera(class Camera* _camera) { mainCamera = _camera; };
	class Camera* GetMainCamera() { return mainCamera; };

	DynamicArray<List<class Actor*>*> GetAllActor();
	class Actor* FindActor(String _name);


private:
	/** ���� �̸� */
	String name;

	/** ���� ���� ��ü ������ */
	Level* mainLevel;

	/** ���� ���� �迭 */
	DynamicArray<Level*> subLevels;


	class Camera* mainCamera;
};