#pragma once

struct Color
{
	int color_red{}, color_green{}, color_blue {};

	Color (int red = 255, int green = 255, int blue = 255)
	{
		color_red = red;
		color_green = green;
		color_blue = blue;
	}
};