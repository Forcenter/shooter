#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace sgs {
	constexpr const float SCALE = 0.5f;

	constexpr const int WINDOW_WIDTH = static_cast< int >(1920 * SCALE);
	constexpr const int WINDOW_HEIGHT = static_cast<int>(1080 * SCALE);
	const short unsigned int SUPPORTED_KEY_NUMBER = 3;

	const float PI = 3.1415926536f;

	enum keyStatus {
		pressed = 0,
		released = 1,
	};
	
	enum direction {
		forward = 0,
		right = 1,
		back = 2,
		left = 3,
	};

	constexpr const float SIZE_SWORDSMAN = SCALE * 30.f;

	constexpr const float SIZE_HERO = SCALE * 50.f;
	constexpr const float SPEED_HERO = SCALE *  10.0f;
	constexpr const float SPEED_SWORDSMAN = SCALE *  7.0f;
	constexpr const int SWORDSMAN_ATTACK_SPEED = 30;
	constexpr const float SWORDSMAN_ATTACK_RADIUS = SCALE *  100.f;

	const sf::Vector2f BULLET_SIZE = { 20 * SCALE, 10 * SCALE };
	const float BULLET_SPEED = 20.f * SCALE;
	const int FIRING_COOLDOWN = 10;

	constexpr const float MIN_SCREEN_STEP = 0.2f * SCALE;
	constexpr const float MAX_DISTANCE_TO_CAM = 400.f * SCALE;
	constexpr const float SCREEN_SPEED = 5.f / SCALE;
}

#endif