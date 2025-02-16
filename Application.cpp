#include <iostream>
#include <stdlib.h>
#include "Application.h"
#include "DxLib.h"
#include "TopScene.h"

Application::Application() : running(true), requestedReseting(false)
{
    SetGraphMode(1280, 720, 32);
    SetWindowSize(1280, 720);
    ChangeWindowMode(TRUE);

    if (DxLib_Init() == -1)
    {
        exit(EXIT_FAILURE);
    }

    ChangeScene(std::make_shared<TopScene>());
}

Application& Application::GetInstance()
{
    static Application instance;

    return instance;
}

void Application::ChangeScene(std::shared_ptr<Scene> newScene)
{
    scenes_.clear();
    newScene->SetAdditive(false);
    scenes_.push_back(newScene);
    newScene->Start();
}

void Application::AdditiveScene(std::shared_ptr<Scene> additiveScene)
{
    additiveScene->SetAdditive(true); // クリアは行わない
    scenes_.push_back(additiveScene);
    additiveScene->Start();
}

void Application::UnloadScene(std::shared_ptr<Scene> scene)
{
    scenes_.erase(std::remove(scenes_.begin(), scenes_.end(), scene), scenes_.end());
}

void Application::Update()
{
    for (auto& scene : scenes_)
    {
        scene->Update();
        // ベースシーンに対してリセット要求があるか
        if (!scene->IsAdditive() && requestedReseting)
        {
            requestedReseting = false;
            scene->Reset();
        }
    }
}

void Application::Render()
{
    for (auto& scene : scenes_)
    {
        scene->Render();
    }
}

void Application::Run()
{
    while (running && !ScreenFlip() && !ProcessMessage() && !clsDx()) {
        Update();
        Render();
    }
    exit(EXIT_SUCCESS);
}
