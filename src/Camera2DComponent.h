#pragma once
#include "Component.h"

class Camera2DComponent : public Component {
 public:
  int srcX, srcY, srcWidth, srcHeight;  // キャンバスの切り抜く範囲の指定
  int destX = 0, destY = 0, destWidth, destHeight;  // カメラでの描画範囲指定
  int renderLayer;  // カメラで投影するレイヤー

  /**
   * @brief カメラコンポーネント．分岐に用いられるため適用には注意が必要．
   * @param _srcX キャンバスの切り抜く起点
   * @param _srcY キャンバスの切り抜く起点
   * @param _srcWidth キャンバスの切り抜く幅
   * @param _srcHeight キャンバスの切り抜く高さ
   * @param _destWidth 切り抜いたキャンバスを描画する幅
   * @param _destHeight 切り抜いたキャンバスを描画する高さ
   * @param _renderLayer カメラで投影するレイヤー
   */
  Camera2DComponent(int _srcX, int _srcY, int _srcWidth, int _srcHeight,
                    int _destWidth, int _destHeight, int _renderLayer = 0)
      : srcX(_srcX),
        srcY(_srcY),
        srcWidth(_srcWidth),
        srcHeight(_srcHeight),
        destWidth(_destWidth),
        destHeight(_destHeight),
        renderLayer(_renderLayer) {}

  void Update() override;
  /**
   * @brief
   * スクリーンハンドルを用いて描画する．
   * renderLayerは順序を定義しているのみでハンドルではない
   * @param offscreenHandle
   */
  void Render(int offscreenHandle) const;
};
