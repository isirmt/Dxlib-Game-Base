#pragma once
#include "Component.h"

/**
 * @brief �{�^����h���b�O�C�Փ˔���ɗ��p�\�Ȓ����`����R���|�[�l���g
 */
class ColliderComponent : public Component {
 public:
  /**
   * @brief ����̑傫��
   */
  float width, height;

  /**
   * @brief �����`����̃T�C�Y���w�肷��
   * @param w ��
   * @param h ����
   */
  ColliderComponent(float w, float h) : width(w), height(h) {}

  /**
   * @brief ����́u�L�����o�X���W�v���I�u�W�F�N�g�͈̔͂ɓ����Ă��邩���肷��
   * @param x �L�����o�XX���W
   * @param y �L�����o�XY���W
   * @return TRUE: �����Ă���, FALSE: �����Ă��Ȃ�
   */
  bool Contains(float x, float y);
};
