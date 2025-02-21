#pragma once
#include "Component.h"
#include "MouseCameraSelector.h"

class DragComponent : public Component {
 public:
  bool wasLeftMouseDown = false; // �O�t���[���ŉ�����Ă�����
  bool dragging = false; // �h���b�O����
  int offsetX = 0; // �h���b�O�J�n���ɃI�t�Z�b�g��ݒ肷��
  int offsetY = 0; // �h���b�O�J�n���ɃI�t�Z�b�g��ݒ肷��
  /**
   * @brief ���C���[�\���ɂ��d������𖳎����邩
   */
  bool ignoreLayerCheck = false;
  /**
   * @brief �R���o�[�^�[��nullptr(�J�����̊O)�̎��Ƀh���b�O������O����
   */
  bool cancelDraggingOnConverterNull = false;

  /**
   * @brief �ړ�������I�u�W�F�N�g��ς���ۂɎw��
   */
  std::shared_ptr<class TransformComponent> targetTransform;

  /**
   * @brief �J�����Z���N�^�[�������ꍇ�͓��삵�Ȃ�
   */
  std::shared_ptr<MouseCameraSelector> cameraSelector;

  DragComponent() = default;

  void Update() override;
};
