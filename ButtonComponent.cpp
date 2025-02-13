#include "ButtonComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "Rect2DComponent.h"
#include "DxLib.h"

void ButtonComponent::AddOnClickListener(Callback callback)
{
	onClickFuncs.push_back(callback);
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
		converter = cameraSelector->GetCurrentMouseConverter();
	}
	else {
		converter = std::make_shared<UIMouseCoordinateConverter>();
	}

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

	if (isOver) {
		printfDx("HOVERED\n");
	}

	if (isOver && (GetMouseInput() & MOUSE_INPUT_LEFT)) {
		printfDx("CLICKING\n");
		for (auto& event : onClickFuncs) {
			event();
		}
	}
}
