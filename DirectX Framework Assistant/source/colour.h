#pragma once

namespace renderer {
	struct colour {
		float r, g, b, a;

		colour(float red, float green, float blue, float alpha = 255.0f) { // converts RGBA colour values
			r = red / 255.0f;
			g = green / 255.0f;
			b = blue / 255.0f;
			a = alpha / 255.0f;
		}
	};
}