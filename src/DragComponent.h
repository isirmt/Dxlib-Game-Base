#pragma once
#include "Component.h"
#include "MouseCameraSelector.h"

class DragComponent : public Component {
 public:
  bool wasLeftMouseDown = false; // 前フレームで押されていたか
  bool dragging = false; // ドラッグ中か
  int offsetX = 0; // ドラッグ開始時にオフセットを設定する
  int offsetY = 0; // ドラッグ開始時にオフセットを設定する
  /**
   * @brief レイヤー構造による重複判定を無視するか
   */
  bool ignoreLayerCheck = false;
  /**
   * @brief コンバーターがnullptr(カメラの外)の時にドラッグ判定を外すか
   */
  bool cancelDraggingOnConverterNull = false;

  /**
   * @brief 移動させるオブジェクトを変える際に指定
   */
  std::shared_ptr<class TransformComponent> targetTransform;

  /**
   * @brief カメラセレクターが無い場合は動作しない
   */
  std::shared_ptr<MouseCameraSelector> cameraSelector;

  DragComponent() = default;

  void Update() override;
};
