#pragma once
#include <list>
#include <memory>
#include <unordered_map>
#include <vector>

#include "DxMouseProvider.h"
#include "GameObject.h"
#include "MouseCameraSelector.h"
#include "RenderTarget.h"

/**
 * @brief �V�[���̒��ۃN���X
 */
class Scene : public std::enable_shared_from_this<Scene> {
 protected:
  std::list<GameObjectPtr> gameObjects;
  std::shared_ptr<MouseCameraSelector> cameraSelector;
  std::unordered_map<int, std::shared_ptr<RenderTarget>> renderTargets;

  bool isAdditive = false;

 public:
  Scene() = default;
  virtual ~Scene() = default;

  virtual void Update();
  virtual void Render();

  virtual void Start() = 0;
  virtual void Reset();

  /**
   * @brief �I�u�W�F�N�g���V�[���ɒǉ�����(�錾����Ȃ��ꍇ�ǉ�����Ȃ�)
   * @param obj 
   */
  void AddObject(GameObjectPtr obj);
  /**
   * @brief �����_�����O�p�̃X�N���[�����쐬����
   * @param layer ���C���[�ԍ�(�C��)
   * @param width ��
   * @param height ����
   */
  void RegisterRenderTarget(int layer, int width, int height);
  /**
   * @brief �ǉ��V�[���Ƃ��Đݒ肷��
   * �ǉ��V�[���Ƃ��Đݒ肳���ƁC�X�V���Ƀ^�[�Q�b�g��s�p�ӂɔ��������Ȃ�
   * @param additive �t���O
   */
  void SetAdditive(bool additive) { isAdditive = additive; }
  /**
   * @brief �ǉ��V�[���Ƃ��Đݒ肳��Ă��邩
   * @return 
   */
  bool IsAdditive() const { return isAdditive; }
  /**
   * @brief �J�����Z���N�^�[��o�^����(�J�����Z���N�^�[���V�[���֓n��)
   * @param _cameraSelector �o�^����J�����Z���N�^�[
   */
  void SetCameraSelector(
      std::shared_ptr<MouseCameraSelector> _cameraSelector) {
    cameraSelector = _cameraSelector;
  }
  /**
   * @brief �Q�[���I�u�W�F�N�g���擾����
   * @return �Q�[���I�u�W�F�N�̔z��
   */
  const std::list<GameObjectPtr>& GetGameObjects() const { return gameObjects; }

 private:
  /**
   * @brief �폜�ҋ@�̃I�u�W�F�N�g���폜����
   */
  void ProcessPending();
};
