#pragma once

class IMouseCoordinateConverter {
 public:
  virtual ~IMouseCoordinateConverter() = default;

  virtual void Convert(int screenX, int screenY, int& outX, int& outY) = 0;
};
