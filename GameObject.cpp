#include "GameObject.h"
#include "TransformComponent.h"

GameObject::GameObject(std::string _name)
	: name(_name), shouldDestroy(false)
{
}