#pragma once
#include "IMouseCoordinateConverter.h"
class UIMouseCoordinateConverter :
    public IMouseCoordinateConverter
{
public:
    void Convert(int screenX, int screenY, int& outX, int& outY) {
        outX = screenX;
        outY = screenY;
    }
};

