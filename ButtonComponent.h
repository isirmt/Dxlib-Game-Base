#pragma once
#include <functional>
#include <memory>
#include <vector>

#include "Component.h"
#include "MouseCameraSelector.h"
#include "IMouseCoordinateConverter.h"

using Callback = std::function<void()>;

/**
 * @brief �{�^������ƕt������R�[���o�b�N�̒ǉ��R���|�[�l���g�D
 * �R�[���o�b�N��void()�̂ݓo�^�\�Cvoid
 * Scene::Func()�̃o�C���h�܂��̓����_�֐�����o�^�\
 */
class ButtonComponent : public Component {
 public:
  std::vector<Callback> onHoverStartFuncs;  // �z�o�[�J�n���Ɏ��s����֐����X�g
  std::vector<Callback> onHoverFuncs;  // �z�o�[���Ɏ��s����֐����X�g
  std::vector<Callback> onHoverEndFuncs;  // �z�o�[�I�����Ɏ��s����֐����X�g
  std::vector<Callback>
      onClickStartFuncs;  // �N���b�N�J�n���Ɏ��s����֐����X�g
  std::vector<Callback> onClickFuncs;  // �N���b�N���Ɏ��s����֐����X�g
  std::vector<Callback> onClickEndFuncs;  // �N���b�N�I�����Ɏ��s����֐����X�g

  /**
   * @brief �J�����Z���N�^�[�������ꍇ�͓��삵�Ȃ�
   */
  std::shared_ptr<MouseCameraSelector> cameraSelector;

  bool isHovering = false;  // �z�o�[���Ă��邩(�����X�V)
  bool isClicked = false;   // �N���b�N���Ă��邩(�����X�V)
  /**
   * @brief ���C���[�\���ɂ��d������𖳎����邩
   */
  bool ignoreLayerCheck = false;

  ButtonComponent() {}

  void AddOnHoverStartListener(Callback callback);
  void AddOnHoverListener(Callback callback);
  void AddOnHoverEndListener(Callback callback);
  void AddOnClickStartListener(Callback callback);
  void AddOnClickListener(Callback callback);
  void AddOnClickEndListener(Callback callback);

  void Update() override;
};
