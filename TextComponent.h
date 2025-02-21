#pragma once
#include <string>
#include <vector>

#include "Component.h"

/**
 * @brief �e�L�X�g�R���|�[�l���g�D�e�L�X�g�n���h�������ɕ\������
 */
class TextComponent : public Component {
 private:
  std::vector<std::string> cachedWrappedLines;
  std::string cachedText;
  int cachedWrapWidth = 0;
  bool needsWrapUpdate = true;

 public:
  /**
   * @brief �e�L�X�g���X�V����ƃ��b�v�ʒu���Čv�Z�����
   */
  std::string text;
  int fontHandle;
  int color;
  /**
   * @brief ���b�v�T�C�Y���X�V����ƃ��b�v�ʒu���Čv�Z�����
   */
  int wrapWidth;
  int lineHeight; // �s�ԃT�C�Y

  /**
   * @brief �R���|�[�l���g�̏�����
   * @param _text �\���������e�L�X�g
   * @param _fontHandle �t�H���g�n���h��
   * @param _color �F
   * @param _wrapWidth ���b�v�T�C�Y(0��nowrap)
   * @param _lineHeight �s��(�����l24)
   */
  TextComponent(const std::string& _text, int _fontHandle, int _color,
                int _wrapWidth = 0, int _lineHeight = 24)
      : text(_text),
        fontHandle(_fontHandle),
        color(_color),
        wrapWidth(_wrapWidth),
        lineHeight(_lineHeight) {}

  /**
   * @brief ���b�v��̍s�����擾�D�{�b�N�X�̃T�C�Y��ς���ꍇ�ɗL��
   * @return �s��(1~)
   */
  size_t GetWrappedLines() const {
    return wrapWidth > 0 ? cachedWrappedLines.size() : static_cast<size_t>(1);
  }

  void Update() override;
  void Render() override;
};
