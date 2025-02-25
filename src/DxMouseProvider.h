#pragma once
#include <memory>

#include "IMouseProvider.h"
#include "WindowManager.h"

class DxMouseProvider : public IMouseProvider {
  std::shared_ptr<WindowManager> windowManager;

 public:
  DxMouseProvider(std::shared_ptr<WindowManager> wm) : windowManager(wm) {}

  void GetMousePosition(int& x, int& y) override;
  bool IsMouseButtonDown(int buttonFlag) override;
};
