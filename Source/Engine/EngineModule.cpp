#include "Module/ModuleBase.h"
#include "GameFramework/Level.h"

class EngineModule : public ModuleBase
{
	virtual void StartUpModule() override;
	virtual void ShotDownModule() override;
};
//IMPLEMENT_MODULE(Engine)
DEFINE_MODULE(Engine);

void EngineModule::StartUpModule()
{
	LevelFactory::Add("Deafault", new Level());
}

void EngineModule::ShotDownModule()
{
	LevelFactory::Remove("Deafault");
}
