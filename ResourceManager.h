#pragma once
#include <string>
#include <unordered_map>
#include "DxLib.h"

class ResourceManager {
private:
    std::unordered_map<std::string, int> images;
    std::unordered_map<std::string, int> sounds;
    std::unordered_map<std::string, int> fonts;

    ~ResourceManager() {
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

    // ÉRÉsÅ[ã÷é~
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    static ResourceManager& GetInstance() {
        static ResourceManager instance;
        return instance;
    }

    int LoadImage(const std::string& path) {
        if (images.find(path) == images.end()) {
            int handle = LoadGraph(path.c_str());
            images[path] = handle;
        }
        return images[path];
    }

    int LoadSound(const std::string& path) {
        if (sounds.find(path) == sounds.end()) {
            int handle = LoadSoundMem(path.c_str());
            sounds[path] = handle;
        }
        return sounds[path];
    }

    int LoadFont(const std::string& fontName, int size, int thick) {
        std::string key = fontName + "_" + std::to_string(size) + "_" + std::to_string(thick);
        if (fonts.find(key) == fonts.end()) {
            int handle = CreateFontToHandle(fontName.c_str(), size, thick, DX_FONTTYPE_ANTIALIASING);
            fonts[key] = handle;
        }
        return fonts[key];
    }
};
