#pragma once
#include "DxLib.h"

/**
 * @brief �L�����o�X���Ǘ�����
 */
class RenderTarget {
 public:
  /**
   * @brief �C�ӂ̃��C���[�l
   */
  int layer;
  /**
   * @brief ���C�u�����ɂ���Ċ��蓖�Ă�ꂽ�n���h��
   */
  int handle;
  int width, height; // �X�N���[���T�C�Y

  /**
   * @brief �L�����o�X�̍쐬
   * @param _layer �C�ӂ̃��C���[�l
   * @param _width ��
   * @param _height ����
   */
  RenderTarget(int _layer, int _width, int _height)
      : layer(_layer), width(_width), height(_height) {
    handle = MakeScreen(width, height, true);
  }

  ~RenderTarget() { DeleteGraph(handle); }
};
