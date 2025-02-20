#pragma once

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

  static T& GetInstance() {
    static T instance;
    return instance;
  }
};
