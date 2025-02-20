#pragma once
#include <memory>
#include <vector>
#include "Scene.h"

class SceneManager {
public:
    SceneManager() = default;

    void ChangeScene(std::shared_ptr<Scene> newScene) {
        scenes_.clear();
        newScene->SetAdditive(false);
        scenes_.push_back(newScene);
        newScene->Start();
    }

    void AdditiveScene(std::shared_ptr<Scene> additiveScene) {
        additiveScene->SetAdditive(true);
        scenes_.push_back(additiveScene);
        additiveScene->Start();
    }

    void UnloadScene(std::shared_ptr<Scene> scene) {
        scenes_.erase(std::remove(scenes_.begin(), scenes_.end(), scene), scenes_.end());
    }

    void Update() {
        for (auto& scene : scenes_) {
            scene->Update();
        }
    }

    void Render() {
        for (auto& scene : scenes_) {
            scene->Render();
        }
    }

    const std::vector<std::shared_ptr<Scene>>& GetScenes() const { return scenes_; }

private:
    std::vector<std::shared_ptr<Scene>> scenes_;
};
