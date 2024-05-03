#pragma once

#include "Containers/DynamicArray.h"
#include "Containers/List.h"
#include "Containers/String.h"

class Level;

/**
 * 엔진에서 실행할 월드입니다.
 * 예시) PlayWorld, EditWorld, SimpleViewWorld
 */
class ENGINEMODULEAPI World
{
public:
	World();
	virtual  ~World();

public:
	/** 월드를 초기화 합니다. */
	void BeginPlay();
	
	/**
	  * 고정된 간격으로 월드를 갱신합니다.
	  * @param fixedTickTime 고정된 간격 시간
	  */
	void FixedUpdate(float fixedTickTime);

	/**
	   * 월드를 갱신합니다.
	   * @param tickTime 갱신할 시간 간격
	   */
	void Update(float tickTime);
	
	/** 월드를 끝냅니다. */
	void EndPlay();

	/**
	 * 메인 레벨을 설정합니다.
	 * @param mainLevel 메인 레벨 객체
	 */
	void SetMainLevel(Level* mainLevel);
	
	/**
	 * 메인 레벨을 가져옵니다.
	 * @return 메인 레벨 객체 포인터
	 */
	Level* GetMainLevel();

	DynamicArray<Level*>& GetSubLevel();

	/**
	 * 월드 설정 객체를 가져옵니다.
	 * @return 월드 설정 객체 포인터
	 */
	class WorldSettings* getWorldSettings();

	/**
	 * 레벨을 추가합니다.
	 * @param level 추가할 레벨 객체
	 */
	void AddLevel(Level* level);

	/**
	 * 레벨을 제거합니다.
	 * @param level 제거할 레벨 객체
	 */
	void RemoveLevel(Level* level);

	/** 레벨을 추가합니다. (이름으로) */
	[[deprecated("This function has not been implemented yet")]]
	void AddLevelByName(String LevelName);
	
	/**
	 * 레벨을 제거합니다. (이름으로)
	 * @param LevelName 제거할 레벨의 이름
	 */
	void RemoveLevelByName(String LevelName);

	void SetMainCamera(class Camera* _camera) { mainCamera = _camera; };
	class Camera* GetMainCamera() { return mainCamera; };

	DynamicArray<List<class Actor*>*> GetAllActor();
	class Actor* FindActor(String _name);


private:
	/** 월드 이름 */
	String name;

	/** 메인 레벨 객체 포인터 */
	Level* mainLevel;

	/** 서브 레벨 배열 */
	DynamicArray<Level*> subLevels;


	class Camera* mainCamera;
};