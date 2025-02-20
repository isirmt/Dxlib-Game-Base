#pragma once
#include "IKeyboardProvider.h"

class DxKeyboardProvider :
    public IKeyboardProvider
{
public:
    bool IsKeyDown(int keyCode) override;
};

