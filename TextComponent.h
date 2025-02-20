#pragma once
#include <string>
#include <vector>

#include "Component.h"

class TextComponent : public Component {
 private:
  std::vector<std::string> cachedWrappedLines;
  std::string cachedText;
  int cachedWrapWidth = 0;
  bool needsWrapUpdate = true;

 public:
  std::string text;
  int fontHandle;
  int color;
  int wrapWidth;
  int lineHeight;

  TextComponent(const std::string& _text, int _fontHandle, int _color,
                int _wrapWidth = 0, int _lineHeight = 24)
      : text(_text),
        fontHandle(_fontHandle),
        color(_color),
        wrapWidth(_wrapWidth),
        lineHeight(_lineHeight) {}

  size_t GetWrappedLines() const {
    return wrapWidth > 0 ? cachedWrappedLines.size() : static_cast<size_t>(1);
  }

  void Update() override;
  void Render() override;
};
