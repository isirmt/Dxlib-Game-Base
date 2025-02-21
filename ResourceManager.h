#pragma once
#include <string>
#include <unordered_map>

#include "DxLib.h"
#include "Singleton.h"

/**
 * @brief ���\�[�X�Ǘ�(�L�[���[�h�Ǘ�)
 */
class ResourceManager : public Singleton<ResourceManager> {
  friend Singleton<ResourceManager>;
  std::unordered_map<std::string, int> images;
  std::unordered_map<std::string, int> sounds;
  std::unordered_map<std::string, int> fonts;

  ~ResourceManager() {
    Singleton::~Singleton();

    for (auto& pair : images) {
      DeleteGraph(pair.second);
    }
    for (auto& pair : sounds) {
      DeleteSoundMem(pair.second);
    }
    for (auto& pair : fonts) {
      DeleteFontToHandle(pair.second);
    }
  }

 protected:
  ResourceManager() = default;

 public:
  /**
   * @brief �摜�̃n���h�����擾����
   * @param path �t�@�C����
   * @return �n���h��
   */
  int LoadImageFromPath(const std::string& path) {
    if (images.find(path) == images.end()) {
      int handle = LoadGraph(path.c_str());
      images[path] = handle;
    }
    return images[path];
  }
  /**
   * @brief �����̃n���h�����擾����
   * @param path �t�@�C����
   * @return �n���h��
   */
  int LoadSoundFromPath(const std::string& path) {
    if (sounds.find(path) == sounds.end()) {
      int handle = LoadSoundMem(path.c_str());
      sounds[path] = handle;
    }
    return sounds[path];
  }
  /**
   * @brief �t�H���g�̃n���h�����擾����
   * @param fontName �t�H���g��
   * @param size �T�C�Y
   * @param thick ����
   * @return �n���h��
   */
  int LoadFont(const std::string& fontName, int size, int thick) {
    std::string key =
        fontName + "_" + std::to_string(size) + "_" + std::to_string(thick);
    if (fonts.find(key) == fonts.end()) {
      int handle = CreateFontToHandle(fontName.c_str(), size, thick,
                                      DX_FONTTYPE_ANTIALIASING);
      fonts[key] = handle;
    }
    return fonts[key];
  }
};
