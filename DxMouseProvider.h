#pragma once
#include <memory>

#include "DxLib.h"
#include "IMouseProvider.h"
#include "WindowManager.h"

class DxMouseProvider : public IMouseProvider {
  std::shared_ptr<WindowManager> windowManager;

 public:
  DxMouseProvider(std::shared_ptr<WindowManager> wm) : windowManager(wm) {}

  void GetMousePosition(int& x, int& y) override {
    int rawX, rawY;
    GetMousePoint(&rawX, &rawY);

    windowManager->ConvertMousePosition(rawX, rawY, x, y);
  }
  bool IsMouseButtonDown(int buttonFlag) override {
    return (GetMouseInput() & buttonFlag) != 0;
  }
};
