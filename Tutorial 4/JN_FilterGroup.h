#pragma once

struct JN_FilterGroup
{
	enum
	{
		BALLS = (1 << 0),
		PADDLES = (1 << 1),
		HEXAGONS = (1 << 2),
		SPINNERS = (1 << 3),
		DEAD_ZONE = (1 << 4)
	};
};