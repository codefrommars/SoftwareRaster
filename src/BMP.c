#include "BMP.h"

#define BMP_ID 				0x4D42
#define BMP_HEADER_SIZE 	40
#define BMP_COLOR_PLANES	1
BMP_HEADER BMP_new(){
	BMP_HEADER b = {BMP_ID, 0, 0, 0, 0, BMP_HEADER_SIZE, 0, 0, BMP_COLOR_PLANES, 0, 0, 0, 0, 0, 0, 0};
	return b;
}
