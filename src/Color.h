#ifndef COLOR_H_
#define COLOR_H_

#include <inttypes.h>

typedef uint32_t ARGBColor;
typedef uint8_t ARGBChannel;

#define ARGB_A(argb) ((ARGBChannel)((argb & 0xFF000000)>>24))
#define ARGB_R(argb) ((ARGBChannel)((argb & 0x00FF0000)>>16))
#define ARGB_G(argb) ((ARGBChannel)((argb & 0x0000FF00)>>8))
#define ARGB_B(argb) ((ARGBChannel)((argb & 0x000000FF)))

#define ARGB_NEW(a, r, g, b) ( ((ARGBColor)a << 24) | ((ARGBColor)r << 16) | ((ARGBColor)g << 8) | (ARGBColor)(b))

typedef struct{
//	float a, r, g, b;
	float a, r, g, b;
} Color;


Color Color_fromARGB(ARGBColor argb);
Color Color_new(float a, float r, float g, float b);
Color Color_scale(Color c, float scale);
Color Color_add(Color c1, Color c2);

ARGBColor color_toARGB(Color c);

#define COLOR_WHITE 	Color_fromARGB(0xFFFFFFFF)
#define COLOR_BLACK 	Color_fromARGB(0xFF000000)
#define COLOR_RED 		Color_fromARGB(0xFFFF0000)
#define COLOR_YELLOW 	Color_fromARGB(0xFFFFFF00)
#define COLOR_GREEN 	Color_fromARGB(0xFF00FF00)
#define COLOR_BLUE 		Color_fromARGB(0xFF0000FF)

#endif /* COLOR_H_ */
