#include "Camera2DComponent.h"
#include "DxLib.h"

void Camera2DComponent::Render(int offscreenHandle) const
{
	DrawRectExtendGraph(
		destX, destY, destX + destWidth, destY + destHeight,
		srcX, srcY, srcX + srcWidth, srcY + srcHeight,
		offscreenHandle, TRUE
	);
}
