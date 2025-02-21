#pragma once
#include <string>
#include <vector>

#include "Component.h"

/**
 * @brief テキストコンポーネント．テキストハンドルを元に表示する
 */
class TextComponent : public Component {
 private:
  std::vector<std::string> cachedWrappedLines;
  std::string cachedText;
  int cachedWrapWidth = 0;
  bool needsWrapUpdate = true;

 public:
  /**
   * @brief テキストを更新するとラップ位置が再計算される
   */
  std::string text;
  int fontHandle;
  int color;
  /**
   * @brief ラップサイズを更新するとラップ位置が再計算される
   */
  int wrapWidth;
  int lineHeight; // 行間サイズ

  /**
   * @brief コンポーネントの初期か
   * @param _text 表示したいテキスト
   * @param _fontHandle フォントハンドル
   * @param _color 色
   * @param _wrapWidth ラップサイズ(0はnowrap)
   * @param _lineHeight 行間(初期値24)
   */
  TextComponent(const std::string& _text, int _fontHandle, int _color,
                int _wrapWidth = 0, int _lineHeight = 24)
      : text(_text),
        fontHandle(_fontHandle),
        color(_color),
        wrapWidth(_wrapWidth),
        lineHeight(_lineHeight) {}

  /**
   * @brief ラップ後の行数を取得．ボックスのサイズを変える場合に有効
   * @return 行数(1~)
   */
  size_t GetWrappedLines() const {
    return wrapWidth > 0 ? cachedWrappedLines.size() : static_cast<size_t>(1);
  }

  void Update() override;
  void Render() override;
};
