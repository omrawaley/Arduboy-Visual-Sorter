#line 1 "/Users/om/Downloads/ARDUBOY/VisualSorter/bar.h"
#pragma once

#include <stdint.h>

class Bar
{
	private:

	public:

		uint8_t x;
		uint8_t y;

		uint8_t width;
		uint8_t height;

		Bar(uint8_t x, uint8_t width, uint8_t height)
		{
			this->x = x;
			this->y = 64 - height;

			this->width = width;
			this->height = height;
		}
};

constexpr int barGap = 5;
constexpr int barWidth = 3;