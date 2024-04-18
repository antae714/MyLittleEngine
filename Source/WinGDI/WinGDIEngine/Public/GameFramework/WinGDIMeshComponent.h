#pragma once

#include "GameFramework/Component.h"
#include "Mesh.h"


class WINGDIENGINEMODULEAPI WinGDIMeshComponent : public Component
{

protected:
	Mesh* mesh;
};

class WINGDIENGINEMODULEAPI WinGDIBoxMeshComponent : public WinGDIMeshComponent
{

};

class WINGDIENGINEMODULEAPI WinGDISphereComponent : public WinGDIMeshComponent
{

};

