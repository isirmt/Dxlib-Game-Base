#pragma once

/**
 * @brief �E�C���h�E���Ǘ�
 */
class WindowManager {
 public:
  /**
   * @brief �E�C���h�E�݌v�T�C�Y
   */
  int designWidth, designHeight;
  /**
   * @brief �E�C���h�E����
   */
  int windowWidth, windowHeight;
  /**
   * @brief �E�C���h�E�̐݌v�T�C�Y����̔{��
   */
  float scaleX, scaleY;

  /**
   * @brief �E�C���h�E�̏����T�C�Y�̐ݒ�
   * @param dWidth 
   * @param dHeight 
   */
  WindowManager(int dWidth, int dHeight)
      : designWidth(dWidth),
        designHeight(dHeight),
        windowWidth(dWidth),
        windowHeight(dHeight),
        scaleX(1.0f),
        scaleY(1.0f) {}

  /**
   * @brief �E�C���h�E�̃T�C�Y�{�����Čv�Z����
   * @param newWidth 
   * @param newHeight 
   */
  void UpdateWindowSize(int newWidth, int newHeight) {
    windowWidth = newWidth;
    windowHeight = newHeight;
    scaleX = static_cast<float>(designWidth) / newWidth;
    scaleY = static_cast<float>(designHeight) / newHeight;
  }

  /**
   * @brief �E�C���h�E�̔{������X�N���[�����W�����ʍ��W�ɕϊ�����
   * @param windowX 
   * @param windowY 
   * @param gameX 
   * @param gameY 
   */
  void ConvertMousePosition(int windowX, int windowY, int& gameX, int& gameY) {
    gameX = static_cast<int>(windowX * scaleX);
    gameY = static_cast<int>(windowY * scaleY);
  }
};
