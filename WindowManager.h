#pragma once

class WindowManager {
public:
    int designWidth, designHeight;
    int windowWidth, windowHeight;
    float scaleX, scaleY;

    WindowManager(int dWidth, int dHeight)
        : designWidth(dWidth), designHeight(dHeight),
        windowWidth(dWidth), windowHeight(dHeight),
        scaleX(1.0f), scaleY(1.0f)
    {
    }

    void UpdateWindowSize(int newWidth, int newHeight) {
        windowWidth = newWidth;
        windowHeight = newHeight;
        scaleX = static_cast<float>(designWidth) / newWidth;
        scaleY = static_cast<float>(designHeight) / newHeight;
    }

    void ConvertMousePosition(int windowX, int windowY, int& gameX, int& gameY) {
        gameX = static_cast<int>(windowX * scaleX);
        gameY = static_cast<int>(windowY * scaleY);
    }
};
