#include "TextComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "DxLib.h"
#include <sstream>

void TextComponent::Update() {
	if (cachedText != text || cachedWrapWidth != wrapWidth) {
		needsWrapUpdate = true;
		cachedText = text;
		cachedWrapWidth = wrapWidth;
	}

	if (!needsWrapUpdate) {
		return;
	}

	cachedWrappedLines.clear();

	// '\n' で分割する
	size_t start = 0;
	while (start < text.size()) {
		size_t pos = text.find('\n', start);
		std::string rawLine = (pos == std::string::npos) ? text.substr(start) : text.substr(start, pos - start);

		std::string line;
		// Shift_JISを1文字単位で処理する
		for (size_t i = 0; i < rawLine.size(); ) {
			int charLen = 1;
			unsigned char c = static_cast<unsigned char>(rawLine[i]);
			// リードバイト(0x81...0x9F，0xE0...0xEF)判定
			if ((c >= 0x81 && c <= 0x9F) || (c >= 0xE0 && c <= 0xEF)) {
				charLen = 2;
			}

			// 1文字分取り出す
			std::string mbChar = rawLine.substr(i, charLen);
			std::string temp = line + mbChar;
			int textWidth = GetDrawStringWidthToHandle(temp.c_str(), static_cast<int>(temp.size()), fontHandle);


			if (textWidth > wrapWidth && !line.empty()) {
				cachedWrappedLines.push_back(line);
				line = mbChar;
			}
			else {
				line = temp;
			}
			i += charLen;
		}

		// 残った部分を行として追加
		if (!line.empty()) cachedWrappedLines.push_back(line);

		// 改行が明示されていた場合は次の行へ
		if (pos != std::string::npos) {
			start = pos + 1;
		}
		else break;
	}

	needsWrapUpdate = false;
}

void TextComponent::Render() {
	auto transform = GetGameObject()->GetComponent<TransformComponent>();
	if (!transform) return;
	int x = static_cast<int>(transform->worldX);
	int y = static_cast<int>(transform->worldY);

	if (wrapWidth > 0) {
		int currentY = y;
		for (const auto& line : cachedWrappedLines) {
			DrawStringToHandle(x, currentY, line.c_str(), color, fontHandle);
			currentY += lineHeight;
		}
	}
	else {
		DrawStringToHandle(x, y, text.c_str(), color, fontHandle);
	}
}
