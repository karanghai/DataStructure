#include "png.h"
#include "rgbapixel.h"

int main()//main function, takes image and flips it by copying the color component of the pixels
{
	int x,y,z;
	PNG in("in.png");
	if(in.width()!=0 && in.height()!=0)
	{
		PNG out(in.width(),in.height());
		for(int i=0;i<in.width();i++)
			for(int j=0;j<in.height();j++)
			{
				x=in(i,j)->red;
				y=in(i,j)->green;
				z=in(i,j)->blue;
				out(in.width()-i-1,in.height()-j-1)->red=x;
				out(in.width()-i-1,in.height()-j-1)->green=y;
				out(in.width()-i-1,in.height()-j-1)->blue=z;

			}	

	out.writeToFile("out.png");
	}

return 0;
}

