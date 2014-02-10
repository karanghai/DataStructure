#ifndef IMAGE1_H
#define IMAGE1_H

#include "png.h"

class Image : public PNG	//class Image
{
	public:
	void flipleft();
	void adjustbrightness(int r,int g,int b);
	void invertcolors();
};


#endif
