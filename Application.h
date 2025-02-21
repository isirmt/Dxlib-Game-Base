#pragma once
#include <memory>
#include <vector>

#include "Scene.h"
#include "SceneManager.h"
#include "Singleton.h"
#include "WindowManager.h"

/**
 * @brief �A�v���P�[�V�������s�N���X
 */
class Application : public Singleton<Application> {
  friend class Singleton<Application>;
  bool running; // ���s�p���t���O(false�ŏI��
  std::shared_ptr<WindowManager> windowManager;
  std::shared_ptr<MouseCameraSelector> cameraSelector;
  std::shared_ptr<SceneManager> sceneManager;

 protected:
  /**
   * @brief �A�v���P�[�V�����̃Z�b�g�A�b�v
   */
  Application();

  /**
   * @brief �V�[���̍X�V
   */
  void Update();
  /**
   * @brief �V�[���̍X�V
   */
  void Render();

 public:
  /**
   * @brief ��ʑJ�ڂ����s����
   * @param newScene �J�ڐ�V�[��(std::make_shared)
   */
  void ChangeScene(std::shared_ptr<Scene> newScene);

  /**
   * @brief ��ʑJ�ڂ�����ɃV�[�����d�˂�
   * @param additiveScene �ǉ��V�[��(std::make_shared)
   */
  void AdditiveScene(std::shared_ptr<Scene> additiveScene);

  /**
   * @brief �V�[������菜��(additive��)
   * @param scene �Ώۂ̃V�[��
   */
  void UnloadScene(std::shared_ptr<Scene> scene);

  /**
   * @brief ���݂̃}�E�X���W�ň�ԏ�ɂ���I�u�W�F�N�g���擾����
   * @return ��ԏ�̃|�C���^(�܂���nullptr)
   */
  std::shared_ptr<GameObject> GetTopGameObjectAtPoint();

  /**
   * @brief �A�v���̎��s(while���[�v)
   */
  void Run();
};
