#include "ConsoleGamePlayerCharacter.h"
#include "ConsoleMovementComponent.h"
#include "GameFramework/Controller.h"
#include "ConsoleRenderComponent.h"
#include "ConsoleConfig.h"
#include "ConsoleWorldSetting.h"

void ConsoleGamePlayerCharacter::BeginPlay()
{
	Base::BeginPlay();	
	AddComponent(new ConsoleMovementComponent());
	ConsoleRenderComponent* renderComponent = new ConsoleRenderComponent();
	renderComponent->renderData = RenderData{ 8,4, BG_GREEN };
	AddComponent(renderComponent);
	speed = 0.005f;


	position = consoleWorldSetting->GetStartPoint();
	//goalPoint = consoleWorldSetting->GetGoalPoint();
}

void ConsoleGamePlayerCharacter::Update(float deltaTime)
{
	Base::Update(deltaTime);
	Vector targetPosition = position + direction * deltaTime * speed;

	/*if ((consoleWorldSetting->GetMapElement(targetPosition + Vector(0.0f, 0.0f)) == (int)EObject::Wall ||
		consoleWorldSetting->GetMapElement(targetPosition + Vector(0.8f, 0.0f)) == (int)EObject::Wall ||
		consoleWorldSetting->GetMapElement(targetPosition + Vector(0.0f, 0.8f)) == (int)EObject::Wall ||
		consoleWorldSetting->GetMapElement(targetPosition + Vector(0.8f, 0.8f)) == (int)EObject::Wall))
	{
		targetPosition = position;
	}*/

	CheckWall(targetPosition, Vector(0.01f, 0.01f));
	CheckWall(targetPosition, Vector(0.99f, 0.01f));
	CheckWall(targetPosition, Vector(0.01f, 0.99f));
	CheckWall(targetPosition, Vector(0.99f, 0.99f));

	position = targetPosition;

	direction = Vector();
}

void ConsoleGamePlayerCharacter::EndPlay()
{
	Base::EndPlay();
}

void ConsoleGamePlayerCharacter::BindInput(Controller* controller)
{
	Base::BindInput(controller);


	controller->BindInput("UP", &ConsoleGamePlayerCharacter::MoveUP, this);
	controller->BindInput("Down", &ConsoleGamePlayerCharacter::MoveDown, this);
	controller->BindInput("Left", &ConsoleGamePlayerCharacter::MoveLeft, this);
	controller->BindInput("Right", &ConsoleGamePlayerCharacter::MoveRight, this);
}

void ConsoleGamePlayerCharacter::CheckWall(Vector& _pos, Vector _direction)
{
	Vector targetPos = _pos + _direction;

	if (consoleWorldSetting->GetMapElement(targetPos) == (int)EObject::Wall)
	{
		//targetPosition = position;
		if (direction.x > 0 && _direction.x >= 0.5f)
		{
			_pos.x = (int)targetPos.x - 1;
		}
		else if (direction.x < 0 && _direction.x <= 0.5f)
		{
			_pos.x = (int)targetPos.x + 1;
		}
		if (direction.y > 0 && _direction.y >= 0.5f)
		{
			_pos.y = (int)targetPos.y - 1;
		}
		else if (direction.y < 0 && _direction.y <= 0.5f)
		{
			_pos.y = (int)targetPos.y + 1;
		}
	}
}

void ConsoleGamePlayerCharacter::MoveUP()
{
	direction.y -= 1.0f;
}

void ConsoleGamePlayerCharacter::MoveDown()
{
	direction.y += 1.0f;
}

void ConsoleGamePlayerCharacter::MoveLeft()
{
	direction.x -= 1.0f;
}

void ConsoleGamePlayerCharacter::MoveRight()
{
	direction.x += 1.0f;
}
