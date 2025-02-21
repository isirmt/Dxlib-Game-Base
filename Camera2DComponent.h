#pragma once
#include "Component.h"

class Camera2DComponent : public Component {
 public:
  int srcX, srcY, srcWidth, srcHeight;  // �L�����o�X�̐؂蔲���͈͂̎w��
  int destX = 0, destY = 0, destWidth, destHeight;  // �J�����ł̕`��͈͎w��
  int renderLayer;  // �J�����œ��e���郌�C���[

  /**
   * @brief �J�����R���|�[�l���g�D����ɗp�����邽�ߓK�p�ɂ͒��ӂ��K�v�D
   * @param _srcX �L�����o�X�̐؂蔲���N�_
   * @param _srcY �L�����o�X�̐؂蔲���N�_
   * @param _srcWidth �L�����o�X�̐؂蔲����
   * @param _srcHeight �L�����o�X�̐؂蔲������
   * @param _destWidth �؂蔲�����L�����o�X��`�悷�镝
   * @param _destHeight �؂蔲�����L�����o�X��`�悷�鍂��
   * @param _renderLayer �J�����œ��e���郌�C���[
   */
  Camera2DComponent(int _srcX, int _srcY, int _srcWidth, int _srcHeight,
                    int _destWidth, int _destHeight, int _renderLayer = 0)
      : srcX(_srcX),
        srcY(_srcY),
        srcWidth(_srcWidth),
        srcHeight(_srcHeight),
        destWidth(_destWidth),
        destHeight(_destHeight),
        renderLayer(_renderLayer) {}

  void Update() override;
  /**
   * @brief
   * �X�N���[���n���h����p���ĕ`�悷��D
   * renderLayer�͏������`���Ă���݂̂Ńn���h���ł͂Ȃ�
   * @param offscreenHandle
   */
  void Render(int offscreenHandle) const;
};
