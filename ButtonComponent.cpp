#include "ButtonComponent.h"

#include "Application.h"
#include "ColliderComponent.h"
#include "DxLib.h"
#include "GameObject.h"
#include "InputManager.h"
#include "TransformComponent.h"

void ButtonComponent::AddOnHoverStartListener(Callback callback) {
  onHoverStartFuncs.push_back(callback);
}

void ButtonComponent::AddOnHoverListener(Callback callback) {
  onHoverFuncs.push_back(callback);
}

void ButtonComponent::AddOnHoverEndListener(Callback callback) {
  onHoverEndFuncs.push_back(callback);
}

void ButtonComponent::AddOnClickStartListener(Callback callback) {
  onClickStartFuncs.push_back(callback);
}

void ButtonComponent::AddOnClickListener(Callback callback) {
  onClickFuncs.push_back(callback);
}

void ButtonComponent::AddOnClickEndListener(Callback callback) {
  onClickEndFuncs.push_back(callback);
}

void ButtonComponent::Update() {
  auto transform = GetGameObject()->GetComponent<TransformComponent>();
  auto collider = GetGameObject()->GetComponent<ColliderComponent>();
  if (!transform || !collider) return;

  int mouseScreenX, mouseScreenY;
  if (auto mouseProvider = InputManager::GetInstance().GetMouseProvider()) {
    mouseProvider->GetMousePosition(mouseScreenX, mouseScreenY);
  } else {
    GetMousePoint(&mouseScreenX, &mouseScreenY);
    OutputDebugString(
        (GetGameObject()->name +
         std::string(
             " [Warning] mouseProvider is not provided in ButtonComponent.\n"))
            .c_str());
  }

  std::shared_ptr<IMouseCoordinateConverter> converter;
  if (cameraSelector) {
    converter =
        cameraSelector->GetCurrentMouseConverter(GetGameObject()->GetLayer());
  } else {
    converter = std::make_shared<UIMouseCoordinateConverter>();
  }

  if (!converter) return;

  int convertedX, convertedY;
  converter->Convert(mouseScreenX, mouseScreenY, convertedX, convertedY);

#ifdef _DEBUG
  printfDx("%s(%s):\n", GetGameObject()->name.c_str(),
           GetMouseInput() & MOUSE_INPUT_LEFT ? "CLICKED" : "-");
  printfDx("mouse_screen: %d, %d:\n", mouseScreenX, mouseScreenY);
  printfDx("converted_sc: %d, %d:\n", convertedX, convertedY);
#endif

  bool isOver = collider->Contains(static_cast<float>(convertedX),
                                   static_cast<float>(convertedY));

#ifdef _DEBUG
  if (isHovering) {
    printfDx("HOVERED\n");
  }
  if (isClicked) {
    printfDx("CLICKED\n");
  }
#endif

  // ホバー処理
  if (isOver) {
    if (!isHovering) {
      isHovering = true;
      for (auto& func : onHoverStartFuncs) {
        func();
      }
    }
    for (auto& func : onHoverFuncs) {
      func();
    }
  } else {
    if (isHovering) {
      isHovering = false;
      for (auto& func : onHoverEndFuncs) {
        func();
      }
    }
  }

  // クリック処理
  if (isOver && (GetMouseInput() & MOUSE_INPUT_LEFT)) {
    if (!ignoreLayerCheck) {
      auto topObj = Application::GetInstance().GetTopGameObjectAtPoint();

      if (!topObj || topObj.get() != GetGameObject().get()) {
        return;
      }
    }

    if (!isClicked) {
      isClicked = true;
      for (auto& func : onClickStartFuncs) {
        func();
      }
    }
  } else {
    if (isClicked) {
      isClicked = false;
      for (auto& func : onClickEndFuncs) {
        func();
      }
      if (isOver) {
        for (auto& func : onClickFuncs) {
          func();
        }
      }
    }
  }
}
