#pragma once

class IKeyboardProvider
{
public:
	virtual ~IKeyboardProvider() = default;
	virtual bool IsKeyDown(int keyCode) = 0;
};

