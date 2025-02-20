#include "DxKeyboardProvider.h"
#include "DxLib.h"

bool DxKeyboardProvider::IsKeyDown(int keyCode)
{
    char keys[256] = { 0 };
    GetHitKeyStateAll(keys);
    return keys[keyCode] != 0;
}
