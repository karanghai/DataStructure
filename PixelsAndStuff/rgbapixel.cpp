//rgbapixel.cpp mp1 cs 225

#include "rgbapixel.h"

RGBAPixel::RGBAPixel()//constructor,sets red,green,blue,alpha to values given in problem
{
	red=255;
	green=255;
	blue=255;
	alpha=255;
}

RGBAPixel::RGBAPixel( unsigned char red1,unsigned char green1,unsigned char blue1)//constructor with arguments, sets members to given values
{

	red=red1;
	green=green1;
	blue=blue1;
	alpha=255;

}
