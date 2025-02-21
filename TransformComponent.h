#pragma once
#include <list>

#include "Component.h"

/**
 * @brief ���W����舵���Ȃ�K�{�̃R���|�[�l���g�D�V�X�e���p�R���|�[�l���g���Ȃ�K�v�Ȃ�
 */
class TransformComponent : public Component {
 public:
  /**
   * @brief �e�I�u�W�F�N�g(��Q��)
   */
  std::weak_ptr<GameObject> parent;
  /**
   * @brief �q�I�u�W�F�N�g�z��
   */
  std::list<std::shared_ptr<GameObject>> children;

  /**
   * @brief ���[�J�����W
   * ���̒l��ύX�����Update�Ń��[���h���W�����f�����
   */
  float localX, localY;
  float localRotation;
  float localScaleX, localScaleY;

  /**
   * @brief ���[���h���W(�����v�Z)
   */
  float worldX, worldY;
  float worldRotation;
  float worldScaleX, worldScaleY;

  /**
   * @brief ���W�ϊ��R���|�[�l���g�D�����l�̐ݒ肪�\
   * @param x �����l0
   * @param y �����l0
   * @param rotation �p�x(���W�A��) �����l0
   * @param scaleX �����l1
   * @param scaleY �����l1
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
   * @brief �e�I�u�W�F�N�g�̐ݒ�(������Transform���擾��children�ݒ肪�����)
   * @param newParent �V�����e�I�u�W�F�N�g
   */
  void SetParent(std::shared_ptr<GameObject> newParent);

  /**
   * @brief ���[���h���W���f�֐�
   */
  void UpdateWorldTransform();

  void Update() override;
};
