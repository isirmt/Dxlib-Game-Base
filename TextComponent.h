#pragma once
#include "Component.h"
#include <string>

class TextComponent : public Component {
public:
	std::string text;
	int fontHandle;
	int color;
	int wrapWidth;
	int lineHeight;

	TextComponent(const std::string& _text, int _fontHandle, int _color, int _wrapWidth = 0, int _lineHeight = 24)
		: text(_text), fontHandle(_fontHandle), color(_color), wrapWidth(_wrapWidth), lineHeight(_lineHeight) {
	}

	virtual void Render() override;
};
