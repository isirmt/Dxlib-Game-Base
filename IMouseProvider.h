#pragma once

/**
 * @brief �}�E�X����̃C���^�[�t�F�[�X
 */
class IMouseProvider {
 public:
  virtual ~IMouseProvider() = default;

  /**
   * @brief �}�E�X���W���擾����
   * @param x X���W�Q��
   * @param y Y���W�Q��
   */
  virtual void GetMousePosition(int& x, int& y) = 0;

  /**
   * @brief �}�E�X�̃{�^����������Ă��邩
   * @param buttonFlag �{�^���̃R�[�h
   * @return TRUE: ������Ă���
   */
  virtual bool IsMouseButtonDown(int buttonFlag) = 0;
};
