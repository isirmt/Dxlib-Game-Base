#pragma once
#include <functional>
#include <memory>
#include <vector>

#include "Component.h"
#include "MouseCameraSelector.h"
#include "IMouseCoordinateConverter.h"

using Callback = std::function<void()>;

/**
 * @brief ボタン判定と付随するコールバックの追加コンポーネント．
 * コールバックはvoid()のみ登録可能，void
 * Scene::Func()のバインドまたはラムダ関数から登録可能
 */
class ButtonComponent : public Component {
 public:
  std::vector<Callback> onHoverStartFuncs;  // ホバー開始時に実行する関数リスト
  std::vector<Callback> onHoverFuncs;  // ホバー時に実行する関数リスト
  std::vector<Callback> onHoverEndFuncs;  // ホバー終了時に実行する関数リスト
  std::vector<Callback>
      onClickStartFuncs;  // クリック開始時に実行する関数リスト
  std::vector<Callback> onClickFuncs;  // クリック中に実行する関数リスト
  std::vector<Callback> onClickEndFuncs;  // クリック終了時に実行する関数リスト

  /**
   * @brief カメラセレクターが無い場合は動作しない
   */
  std::shared_ptr<MouseCameraSelector> cameraSelector;

  bool isHovering = false;  // ホバーしているか(自動更新)
  bool isClicked = false;   // クリックしているか(自動更新)
  /**
   * @brief レイヤー構造による重複判定を無視するか
   */
  bool ignoreLayerCheck = false;

  ButtonComponent() {}

  void AddOnHoverStartListener(Callback callback);
  void AddOnHoverListener(Callback callback);
  void AddOnHoverEndListener(Callback callback);
  void AddOnClickStartListener(Callback callback);
  void AddOnClickListener(Callback callback);
  void AddOnClickEndListener(Callback callback);

  void Update() override;
};
