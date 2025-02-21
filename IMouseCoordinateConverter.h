#pragma once

/**
 * @brief ��ʍ��W�����̍��W�֕ϊ�����C���^�[�t�F�[�X
 */
class IMouseCoordinateConverter {
 public:
  virtual ~IMouseCoordinateConverter() = default;

  /**
   * @brief ���W�ϊ��̎��s
   * @param screenX ��ʍ��WX
   * @param screenY ��ʍ��WY
   * @param outX �ϊ����X�Q��
   * @param outY �ϊ����Y�Q��
   */
  virtual void Convert(int screenX, int screenY, int& outX, int& outY) = 0;
};
