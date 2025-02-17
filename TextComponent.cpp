#include "TextComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "DxLib.h"
#include <sstream>

void TextComponent::Render() {
	auto transform = GetGameObject()->GetComponent<TransformComponent>();
	if (!transform) return;
	int x = static_cast<int>(transform->worldX);
	int y = static_cast<int>(transform->worldY);

	if (wrapWidth > 0) {
		std::istringstream iss(text);
		std::string word, line;

		int currentY = y;
		while (iss >> word) {
			std::string testLine = line.empty() ? word : line + " " + word;
			int textWidth = GetDrawStringWidthToHandle(testLine.c_str(), (int)testLine.size(), fontHandle);
			if (textWidth > wrapWidth) {
				DrawStringToHandle(x, currentY, line.c_str(), color, fontHandle);
				currentY += lineHeight;
				line = word;
			}
			else {
				line = testLine;
			}
		}
		if (!line.empty()) {
			DrawStringToHandle(x, currentY, line.c_str(), color, fontHandle);
		}
	}
	else {
		DrawStringToHandle(x, y, text.c_str(), color, fontHandle);
	}
}
