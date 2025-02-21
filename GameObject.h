#pragma once
#include <memory>
#include <string>
#include <typeindex>
#include <unordered_map>

#include "Component.h"

using GameObjectPtr = std::shared_ptr<GameObject>;
using ComponentPtr = std::shared_ptr<Component>;

/**
 * @brief �V�[���ɔz�u�����I�u�W�F�N�g�D�R���|�[�l���g�`���œ��삷��
 */
class GameObject : public std::enable_shared_from_this<GameObject> {
  std::unordered_map<std::type_index, ComponentPtr> components_;
  bool shouldDestroy = false;
  int layer = 0;
  int orderInLayer = 0;
  bool active = true;
  bool visible = true;

 public:
  /**
   * @brief �I�u�W�F�N�g��
   */
  std::string name;

  /**
   * @brief �I�u�W�F�N�g�̏�����
   * @param _name �I�u�W�F�N�g��(�f�o�b�O�ŗL���I)
   */
  GameObject(std::string _name = "GameObject") : name(_name) {}

  /**
   * @brief �R���|�[�l���g�̒ǉ�
   * @tparam T �R���|�[�l���g�h���̌^
   * @tparam ...Args �R���|�[�l���g�̈����^
   * @param ...args �R���|�[�l���g�̈���
   * @return �R���|�[�l���g�̃|�C���^
   */
  template <typename T, typename... Args>
    requires std::is_constructible_v<T, Args...>
  std::shared_ptr<T> AddComponent(Args&&... args) {
    auto comp = std::make_shared<T>(std::forward<Args>(args)...);
    comp->SetGameObject(shared_from_this());
    components_[typeid(T)] = comp;
    return comp;
  }

  /**
   * @brief �R���|�[�l���g�̎擾
   * @tparam T �h���R���|�[�l���g�̌^
   * @return �R���|�[�l���g�̃|�C���^(nullptr�͓o�^����Ă��Ȃ���\��)
   */
  template <typename T>
  std::shared_ptr<T> GetComponent() {
    auto it = components_.find(typeid(T));
    return (it != components_.end()) ? std::dynamic_pointer_cast<T>(it->second)
                                     : nullptr;
  }

  /**
   * @brief ���C���[���̕\��������ݒ肷��
   * @param order �\������
   */
  void SetOrderInLayer(int order) { orderInLayer = order; }
  /**
   * @brief ���C���[���̕\���������擾����
   * @return �\������
   */
  int GetOrderInLayer() const { return orderInLayer; }

  /**
   * @brief ���C���[(�`���̃L�����o�X)���w�肷��
   * @param _layer �Ώۂ̃L�����o�X
   */
  void SetLayer(int _layer) { layer = _layer; }
  /**
   * @brief ���C���[���擾����
   * @return ���C���[
   */
  int GetLayer() const { return layer; }

  /**
   * @brief �I�u�W�F�N�g(�Ƃ��̎q�I�u�W�F�N�g)��j������
   */
  void Destroy();

  /**
   * @brief �j�������\�肩
   * @return TRUE: �j�������\��
   */
  bool ShouldBeDestroyed() const { return shouldDestroy; }

  /**
   * @brief �I�u�W�F�N�g�̗L������ݒ肷��
   * @param flag
   */
  void SetActive(bool flag);
  /**
   * @brief �I�u�W�F�N�g���L����
   * @return TRUE: �L��
   */
  bool IsActive() const { return active; }

  /**
   * @brief �I�u�W�F�N�g�������邩�ǂ����ݒ肷��
   * @param flag
   */
  void SetVisible(bool flag);
  /**
   * @brief �I�u�W�F�N�g�������邩
   * @return TRUE: ������
   */
  bool IsVisible() const { return visible; }

  /**
   * @brief �I�u�W�F�N�g�̃R���|�[�l���g���X�V����
   */
  void Update() {
    if (!active) return;
    for (auto& [type, component] : components_) {
      component->Update();
    }
  }

  /**
   * @brief �I�u�W�F�N�g�̃R���|�[�l���g�ŕ`�悷��
   */
  void Render() {
    if (!active || !visible) return;
    for (auto& [type, component] : components_) {
      component->Render();
    }
  }
};
