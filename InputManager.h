#pragma once
#include <memory>

#include "IKeyboardProvider.h"
#include "IMouseProvider.h"
#include "Singleton.h"

/**
 * @brief �C���v�b�g�V�X�e���̊Ǘ�
 */
class InputManager : public Singleton<InputManager> {
 public:
  /**
   * @brief �v���o�C�_�[��ݒ肷��
   * @param mouse �}�E�X����v���o�C�_�[
   * @param keyboard �L�[�{�[�h����v���o�C�_�[
   */
  void Initialize(std::shared_ptr<IMouseProvider> mouse,
                  std::shared_ptr<IKeyboardProvider> keyboard) {
    mouseProvider = mouse;
    keyboardProvider = keyboard;
  }

  /**
   * @brief �}�E�X�̃v���o�C�_�[���擾����
   * @return �}�E�X�̃v���o�C�_�[
   */
  std::shared_ptr<IMouseProvider> GetMouseProvider() const {
    return mouseProvider;
  }
  /**
   * @brief �L�[�{�[�h�̃v���o�C�_�[���擾����
   * @return �L�[�{�[�h�̃v���o�C�_�[
   */
  std::shared_ptr<IKeyboardProvider> GetKeyboardProvider() const {
    return keyboardProvider;
  }

 private:
  std::shared_ptr<IMouseProvider> mouseProvider;
  std::shared_ptr<IKeyboardProvider> keyboardProvider;
};
