#include "ButtonComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "Rect2DComponent.h"
#include "DxLib.h"

void ButtonComponent::AddOnHoverStartListener(Callback callback)
{
	onHoverStartFuncs.push_back(callback);
}

void ButtonComponent::AddOnHoverListener(Callback callback)
{
	onHoverFuncs.push_back(callback);
}

void ButtonComponent::AddOnHoverEndListener(Callback callback)
{
	onHoverEndFuncs.push_back(callback);
}

void ButtonComponent::AddOnClickStartListener(Callback callback)
{
	onClickStartFuncs.push_back(callback);
}

void ButtonComponent::AddOnClickListener(Callback callback)
{
	onClickFuncs.push_back(callback);
}

void ButtonComponent::AddOnClickEndListener(Callback callback)
{
	onClickEndFuncs.push_back(callback);
}

void ButtonComponent::Update(GameObject& obj)
{
	auto transform = obj.GetComponent<TransformComponent>();
	auto rect = obj.GetComponent<Rect2DComponent>();

	if (!transform && !rect) return;

	int x = static_cast<int>(transform->worldX);
	int y = static_cast<int>(transform->worldY);
	int sx = static_cast<int>(rect->sx);
	int sy = static_cast<int>(rect->sy);

	std::shared_ptr<IMouseCoordinateConverter> converter;
	if (cameraSelector) {
		converter = cameraSelector->GetCurrentMouseConverter(obj.GetLayer());
	}
	else {
		converter = std::make_shared<UIMouseCoordinateConverter>();
	}

	if (!converter) return;

	int convertedX, convertedY;
	int mouseScreenX, mouseScreenY;
	GetMousePoint(&mouseScreenX, &mouseScreenY);
	converter->Convert(mouseScreenX, mouseScreenY, convertedX, convertedY);

	printfDx("%s(%s):\n", obj.name.c_str(), GetMouseInput() & MOUSE_INPUT_LEFT ? "CLICKED" : "-");
	printfDx("(%d,%d) W%d H%d\n", x, y, sx, sy);
	printfDx("mouse_screen: %d, %d:\n", mouseScreenX, mouseScreenY);
	printfDx("converted_sc: %d, %d:\n", convertedX, convertedY);

	bool isOver = (convertedX >= x && convertedX <= x + sx &&
		convertedY >= y && convertedY <= y + sy);

	if (isHovering) {
		printfDx("HOVERED\n");
	}
	if (isClicked) {
		printfDx("CLICKED\n");
	}

	// ホバー処理
	if (isOver) {
		if (!isHovering) {
			isHovering = true;
			for (auto& func : onHoverStartFuncs) { func(); }
		}
		for (auto& func : onHoverFuncs) { func(); }
	}
	else {
		if (isHovering) {
			isHovering = false;
			for (auto& func : onHoverEndFuncs) { func(); }
		}
	}

	// クリック処理
	if (isOver && (GetMouseInput() & MOUSE_INPUT_LEFT)) {
		if (!isClicked) {
			isClicked = true;
			for (auto& func : onClickStartFuncs) { func(); }
		}
	}
	else {
		if (isClicked) {
			isClicked = false;
			for (auto& func : onClickEndFuncs) { func(); }
			if (isOver) {
				for (auto& func : onClickFuncs) { func(); }
			}
		}
	}
}
