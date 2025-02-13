#include "IMouseCameraSelector.h"
#include "DxLib.h"
#include "UIMouseCoordinateConverter.h"
#include "CameraMouseCoordinateConverter.h"
#include "Camera2DComponent.h"

std::shared_ptr<IMouseCoordinateConverter> IMouseCameraSelector::GetCurrentMouseConverter()
{
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);
	printfDx("Mouse: %d %d\n", mouseX, mouseY);
	int i = 0;
	for (auto& camObj : cameras) {
		auto camComp = camObj->GetComponent<Camera2DComponent>();
		if (!camComp) continue;

		int dx = camComp->destX;
		int dy = camComp->destY;
		int dWidth = camComp->destWidth;
		int dHeight = camComp->destHeight;
		printfDx("Camera No.%d: (%d, %d) W%d H%d\n", i, dx, dy, dWidth, dHeight);
		if (mouseX >= dx && mouseX <= dx + dWidth &&
			mouseY >= dy && mouseY <= dy + dHeight) {
			// —Ìˆæ‚É“ü‚Á‚Ä‚¢‚éê‡
			printfDx("Target Camera: No.%d\n", i);
			return std::make_shared<CameraMouseCoordinateConverter>(camComp);
		}
		i++;
	}

	// ŠY“–‚µ‚Ä‚¢‚È‚¢ê‡‚ÍUI”Å‚ğ•Ô‚·
	return std::make_shared<UIMouseCoordinateConverter>();
}
