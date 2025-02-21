#include "DxMouseProvider.h"

#include "DxLib.h"

void DxMouseProvider::GetMousePosition(int& x, int& y) {
  int rawX, rawY;
  GetMousePoint(&rawX, &rawY);

  windowManager->ConvertMousePosition(rawX, rawY, x, y);
}

bool DxMouseProvider::IsMouseButtonDown(int buttonFlag) {
  return (GetMouseInput() & buttonFlag) != 0;
}
