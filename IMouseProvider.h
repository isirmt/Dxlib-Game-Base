#pragma once

class IMouseProvider {
 public:
  virtual ~IMouseProvider() = default;
  virtual void GetMousePosition(int& x, int& y) = 0;
  virtual bool IsMouseButtonDown(int buttonFlag) = 0;
};
