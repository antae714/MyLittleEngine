#include "Application/WindowApplication.h"
#include "Engine.h"
#include "GameFramework/Camera.h"

Camera::Camera()
{
	SetRenderBoxExtents({ 800, 600 });
}

void Camera::BeginPlay()
{
	Base::BeginPlay();
}

void Camera::Update(float deltaTime)
{
	Base::Update(deltaTime);
}

void Camera::EndPlay()
{
	Base::EndPlay();

}

void Camera::SetRenderBoxExtents(Vector _renderBoxExtents)
{
	renderBoxExtents = _renderBoxExtents;
	Vector viewportMin = GetPosition() - renderBoxExtents;
	Vector viewportMax = GetPosition() + renderBoxExtents;
	viewportSize = viewportMax - viewportMin;
	viewportScale = { 1.0f / viewportSize.x, 1.0f / viewportSize.y };
}

Vector Camera::ViewPortToWorld(Vector viewportPosition)
{
	Vector viewportMin = GetPosition() - renderBoxExtents;
	Vector relativePosition = { viewportPosition.x * viewportScale.x ,viewportPosition.y * viewportScale.y };

	Vector worldPosition = relativePosition + viewportMin;

	return worldPosition;
}

Vector Camera::WorldToViewPort(Vector worldPosition)
{
	Vector viewportMin = GetPosition() - renderBoxExtents;
	Vector relativePosition = worldPosition - viewportMin;
	Vector viewportPosition = { viewportScale.x * relativePosition.x , viewportScale.y * relativePosition.y } ;

	return viewportPosition;
}

