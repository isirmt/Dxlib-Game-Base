#pragma once

/**
 * @brief 継承先テンプレート型(ex: Application)
 * @tparam T 継承先
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
   * @brief インスタンスを取得する
   * @return 継承先Tのインスタンス 
   */
  static T& GetInstance() {
    static T instance;
    return instance;
  }
};
