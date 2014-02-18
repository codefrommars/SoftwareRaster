#include "Color.h"
#include <math.h>

Color Color_new(float a, float r, float g, float b){
	Color c = {a, r, g, b};
	return c;
}
Color Color_scale(Color c, float scale){
	return Color_new(	c.a * scale,
						c.r * scale,
						c.g * scale,
						c.b * scale);
}
Color Color_add(Color c1, Color c2){
	return Color_new(	c1.a + c2.a,
						c1.r + c2.r,
						c1.g + c2.g,
						c1.b + c2.b);
}

ARGBColor color_toARGB(Color c){
	ARGBChannel a = (ARGBChannel) floorf(c.a * 255.0f);
	ARGBChannel r = (ARGBChannel) floorf(c.r * 255.0f);
	ARGBChannel g = (ARGBChannel) floorf(c.g * 255.0f);
	ARGBChannel b = (ARGBChannel) floorf(c.b * 255.0f);

	return ARGB_NEW(a, r, g, b);
}

Color Color_fromARGB(ARGBColor argb){
	return Color_new(ARGB_A(argb) / 255.0f, ARGB_R(argb) / 255.0f, ARGB_G(argb) / 255.0f, ARGB_B(argb) / 255.0f);
}
