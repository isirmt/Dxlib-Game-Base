#include "Application.h"

#include "DxKeyboardProvider.h"
#include "DxLib.h"
#include "InputManager.h"
#include "MousePicker.h"
#include "Time.h"
#include "TopScene.h"

Application::Application() : running(true) {
  SetGraphMode(1280, 720, 32);
  SetWindowSize(1280, 720);
  ChangeWindowMode(TRUE);

  if (DxLib_Init() == -1) {
    exit(EXIT_FAILURE);
  }

  windowManager = std::make_shared<WindowManager>(1280, 720);
  cameraSelector = std::make_shared<MouseCameraSelector>();
  SceneManager::GetInstance().SetCameraSelector(cameraSelector);

  InputManager::GetInstance().Initialize(
      std::make_shared<DxMouseProvider>(windowManager),
      std::make_shared<DxKeyboardProvider>());

  SceneManager::GetInstance().ChangeScene<TopScene>();
}

void Application::Update() {
  Time::GetInstance().Update();
  SceneManager::GetInstance().Update();
}

void Application::Render() { SceneManager::GetInstance().Render(); }

std::shared_ptr<GameObject> Application::GetTopGameObjectAtPoint() {
  int mouseScreenX, mouseScreenY;
  auto mouseProvider = InputManager::GetInstance().GetMouseProvider();
  if (mouseProvider) {
    mouseProvider->GetMousePosition(mouseScreenX, mouseScreenY);
  } else {
    GetMousePoint(&mouseScreenX, &mouseScreenY);
  }

  MousePicker picker;
  return picker.GetTopGameObjectAtPoint(SceneManager::GetInstance().GetScenes(),
                                        mouseScreenX, mouseScreenY,
                                        cameraSelector);
}

void Application::Run() {
  while (running && !ScreenFlip() && !ProcessMessage() && !clsDx()) {
    Update();
    Render();
  }
  exit(EXIT_SUCCESS);
}
