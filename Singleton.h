#pragma once

/**
 * @brief �p����e���v���[�g�^(ex: Application)
 * @tparam T �p����
 */
template <typename T>
class Singleton {
 protected:
  Singleton() = default;
  virtual ~Singleton() = default;

 public:
  Singleton(Singleton const&) = delete;
  Singleton& operator=(Singleton const&) = delete;
  Singleton(Singleton&&) = delete;
  Singleton& operator=(Singleton&&) = delete;

  /**
   * @brief �C���X�^���X���擾����
   * @return �p����T�̃C���X�^���X 
   */
  static T& GetInstance() {
    static T instance;
    return instance;
  }
};
