#pragma once

/**
 * @brief �L�[�{�[�h����̃C���^�[�t�F�[�X
 */
class IKeyboardProvider {
 public:
  virtual ~IKeyboardProvider() = default;
  /**
   * @brief ����̃L�[�R�[�h��������Ă��邩
   * @param keyCode �L�[�R�[�h
   * @return TRUE: ������Ă���
   */
  virtual bool IsKeyDown(int keyCode) = 0;
};
