#pragma once
#include <chrono>
#include <thread>
#include "DxLib.h"

class Time
{
private:
	static float deltaTime;
	static float targetFPS;
	static bool unlimitedFPS;

protected:

	Time() = default;

public:

	Time(const Time&) = delete;
	Time& operator=(const Time&) = delete;

	static Time& GetInstance() {
		static Time instance;
		return instance;
	}

	float GetDeltaTime() const {
		return deltaTime;
	}

	void SetTargetFPS(float fps) {
		targetFPS = fps;
	}

	void SetunlimitedFPS(bool flag) {
		unlimitedFPS = flag;
	}

	void Update() {
		using namespace std::chrono;
		static auto lastTime = high_resolution_clock::now();
		auto currentTime = high_resolution_clock::now();
		duration<float> elapsed = currentTime - lastTime;
		deltaTime = elapsed.count();
		lastTime = currentTime;
		printfDx("delta time: %.5f\n", deltaTime);
		printfDx("fps(estimation): %.2f\n", 1.f / deltaTime);

		if (!unlimitedFPS) {
			float frameTime = 1.0f / targetFPS;
			if (deltaTime < frameTime) {
				std::this_thread::sleep_for(duration<float>(frameTime - deltaTime));
				deltaTime = frameTime;
			}
		}
	}
};

