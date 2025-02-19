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

	// '\n' �ŕ�������
	size_t start = 0;
	while (start < text.size()) {
		size_t pos = text.find('\n', start);
		std::string rawLine = (pos == std::string::npos) ? text.substr(start) : text.substr(start, pos - start);

		std::string line;
		// Shift_JIS��1�����P�ʂŏ�������
		for (size_t i = 0; i < rawLine.size(); ) {
			int charLen = 1;
			unsigned char c = static_cast<unsigned char>(rawLine[i]);
			// ���[�h�o�C�g(0x81...0x9F�C0xE0...0xEF)����
			if ((c >= 0x81 && c <= 0x9F) || (c >= 0xE0 && c <= 0xEF)) {
				charLen = 2;
			}

			// 1���������o��
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

		// �c�����������s�Ƃ��Ēǉ�
		if (!line.empty()) cachedWrappedLines.push_back(line);

		// ���s����������Ă����ꍇ�͎��̍s��
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
