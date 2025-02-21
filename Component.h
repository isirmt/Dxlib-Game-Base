#pragma once
#include <memory>

class GameObject;

/**
 * @brief �R���|�[�l���g�̒��ۃN���X
 */
class Component {
 protected:
  /**
   * @brief �R���|�[�l���g��ێ�����Q�[���I�u�W�F�N�g
   */
  std::weak_ptr<GameObject> gameObject;

 public:
  virtual ~Component() = default;
  /**
   * @brief �X�V�֐�(�f�t�H���g�͉������Ȃ�)
   */
  virtual void Update() {};
  /**
   * @brief �`��֐�(�f�t�H���g�͉������Ȃ�)
   */
  virtual void Render() {};

  /**
   * @brief �R���|�[�l���g�ƃQ�[���I�u�W�F�N�g��R�Â���
   * @param obj �R�Â���I�u�W�F�N�g
   */
  void SetGameObject(std::shared_ptr<GameObject> obj) { gameObject = obj; }
  std::shared_ptr<GameObject> GetGameObject() const {
    return gameObject.lock();
  }
};
