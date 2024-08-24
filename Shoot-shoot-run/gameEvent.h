#pragma once
#include "SFML/Graphics.hpp"

struct GameEvent {
public:
	enum class EventType {
		None = 0,
		SwordAttack = 1,
	};

	EventType type;
};
