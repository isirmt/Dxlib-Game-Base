#pragma once
#include <list>

#include "Component.h"

/**
 * @brief 座標を取り扱うなら必須のコンポーネント．システム用コンポーネント等なら必要なし
 */
class TransformComponent : public Component {
 public:
  /**
   * @brief 親オブジェクト(弱参照)
   */
  std::weak_ptr<GameObject> parent;
  /**
   * @brief 子オブジェクト配列
   */
  std::list<std::shared_ptr<GameObject>> children;

  /**
   * @brief ローカル座標
   * この値を変更するとUpdateでワールド座標が反映される
   */
  float localX, localY;
  float localRotation;
  float localScaleX, localScaleY;

  /**
   * @brief ワールド座標(自動計算)
   */
  float worldX, worldY;
  float worldRotation;
  float worldScaleX, worldScaleY;

  /**
   * @brief 座標変換コンポーネント．初期値の設定が可能
   * @param x 初期値0
   * @param y 初期値0
   * @param rotation 角度(ラジアン) 初期値0
   * @param scaleX 初期値1
   * @param scaleY 初期値1
   */
  TransformComponent(float x = 0.f, float y = 0.f, float rotation = 0.f,
                     float scaleX = 1.f, float scaleY = 1.f)
      : localX(x),
        localY(y),
        localRotation(rotation),
        localScaleX(scaleX),
        localScaleY(scaleY),
        worldX(x),
        worldY(y),
        worldRotation(rotation),
        worldScaleX(scaleX),
        worldScaleY(scaleY) {}

  /**
   * @brief 親オブジェクトの設定(自動でTransformを取得しchildren設定がされる)
   * @param newParent 新しい親オブジェクト
   */
  void SetParent(std::shared_ptr<GameObject> newParent);

  /**
   * @brief ワールド座標反映関数
   */
  void UpdateWorldTransform();

  void Update() override;
};
