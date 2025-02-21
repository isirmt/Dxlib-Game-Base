#pragma once
#include <list>
#include <memory>
#include <unordered_map>
#include <vector>

#include "DxMouseProvider.h"
#include "GameObject.h"
#include "MouseCameraSelector.h"
#include "RenderTarget.h"

/**
 * @brief シーンの抽象クラス
 */
class Scene : public std::enable_shared_from_this<Scene> {
 protected:
  std::list<GameObjectPtr> gameObjects;
  std::shared_ptr<MouseCameraSelector> cameraSelector;
  std::unordered_map<int, std::shared_ptr<RenderTarget>> renderTargets;

  bool isAdditive = false;

 public:
  Scene() = default;
  virtual ~Scene() = default;

  virtual void Update();
  virtual void Render();

  virtual void Start() = 0;
  virtual void Reset();

  /**
   * @brief オブジェクトをシーンに追加する(宣言されない場合追加されない)
   * @param obj 
   */
  void AddObject(GameObjectPtr obj);
  /**
   * @brief レンダリング用のスクリーンを作成する
   * @param layer レイヤー番号(任意)
   * @param width 幅
   * @param height 高さ
   */
  void RegisterRenderTarget(int layer, int width, int height);
  /**
   * @brief 追加シーンとして設定する
   * 追加シーンとして設定されると，更新時にターゲットを不用意に白紙化しない
   * @param additive フラグ
   */
  void SetAdditive(bool additive) { isAdditive = additive; }
  /**
   * @brief 追加シーンとして設定されているか
   * @return 
   */
  bool IsAdditive() const { return isAdditive; }
  /**
   * @brief カメラセレクターを登録する(カメラセレクターをシーンへ渡す)
   * @param _cameraSelector 登録するカメラセレクター
   */
  void SetCameraSelector(
      std::shared_ptr<MouseCameraSelector> _cameraSelector) {
    cameraSelector = _cameraSelector;
  }
  /**
   * @brief ゲームオブジェクトを取得する
   * @return ゲームオブジェクの配列
   */
  const std::list<GameObjectPtr>& GetGameObjects() const { return gameObjects; }

 private:
  /**
   * @brief 削除待機のオブジェクトを削除する
   */
  void ProcessPending();
};
