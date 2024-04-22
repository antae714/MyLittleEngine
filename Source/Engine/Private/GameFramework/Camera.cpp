#include "GameFramework/Camera.h"
#include "Application/WindowApplication.h"
#include "Engine.h"
#include "IRenderer.h"

void Camera::BeginPlay()
{
	IRenderer* renderer = Engine::GEngine->GetRenderer();
	renderer->GetHeight();
}

void Camera::Update(float deltaTime)
{
}

void Camera::EndPlay()
{

}

Vector Camera::ScreenToWorld()
{

	return Vector();
}
