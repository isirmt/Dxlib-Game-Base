#pragma once
#include <memory>
#include <vector>

#include "Scene.h"
#include "SceneManager.h"
#include "Singleton.h"
#include "WindowManager.h"

/**
 * @brief アプリケーション実行クラス
 */
class Application : public Singleton<Application> {
  friend class Singleton<Application>;
  bool running;  // 実行継続フラグ(falseで終了)
  std::shared_ptr<WindowManager> windowManager;
  std::shared_ptr<MouseCameraSelector> cameraSelector;

 protected:
  /**
   * @brief アプリケーションのセットアップ
   */
  Application();

  /**
   * @brief シーンの更新
   */
  void Update();
  /**
   * @brief シーンの更新
   */
  void Render();

 public:
  /**
   * @brief 現在のマウス座標で一番上にあるオブジェクトを取得する
   * @return 一番上のポインタ(またはnullptr)
   */
  std::shared_ptr<GameObject> GetTopGameObjectAtPoint();

  /**
   * @brief アプリの実行(whileループ)
   */
  void Run();
};
