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
  bool running; // 実行継続フラグ(falseで終了
  std::shared_ptr<WindowManager> windowManager;
  std::shared_ptr<MouseCameraSelector> cameraSelector;
  std::shared_ptr<SceneManager> sceneManager;

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
   * @brief 画面遷移を実行する
   * @param newScene 遷移先シーン(std::make_shared)
   */
  void ChangeScene(std::shared_ptr<Scene> newScene);

  /**
   * @brief 画面遷移せず上にシーンを重ねる
   * @param additiveScene 追加シーン(std::make_shared)
   */
  void AdditiveScene(std::shared_ptr<Scene> additiveScene);

  /**
   * @brief シーンを取り除く(additive等)
   * @param scene 対象のシーン
   */
  void UnloadScene(std::shared_ptr<Scene> scene);

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
