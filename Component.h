#pragma once

class GameObject;

class Component {
public:
	virtual ~Component() = default;
	virtual void Update(GameObject& obj) {};
	virtual void Render(GameObject& obj) {};
};
