#include "image.h"

void Image::flipleft()		//Flips the image about a vertical line through its center by swapping pixels. 
{
	RGBAPixel *temp=new RGBAPixel;
	for(int y=0;y<this->height();y++)
		for(int x=0;x<this->width()/2;x++)
		{
			*temp=*(*this)(x,y);
			*(*this)(x,y)=*(*this)(this->width()-x-1,y);
			*(*this)(this->width()-x-1,y)=*temp;
		}
			

	delete temp;
	temp=NULL;

}

void Image::adjustbrightness(int r, int g, int b)	//Adds to the red, green, and blue parts of each pixel in the image.
{
	
	for(int y=0;y<this->height();y++)
		for(int x=0;x<this->width();x++)
		{
			if((*this)(x,y)->red + r >=255)		//for red
			{
				(*this)(x,y)->red=255;
			}
			else if((*this)(x,y)->red + r <=0)
			{
				(*this)(x,y)->red=0;			
			}
			else
			{
				(*this)(x,y)->red=(*this)(x,y)->red + r;
			}
			
			if((*this)(x,y)->green + g >=255)		//for green
			{
				(*this)(x,y)->green=255;
			}
			else if((*this)(x,y)->green + g <=0)
			{
				(*this)(x,y)->green=0;			
			}
			else
			{
				(*this)(x,y)->green=(*this)(x,y)->green + g;
			}
			
			if((*this)(x,y)->blue + b >=255)		//for blue
			{		
				(*this)(x,y)->blue=255;
			}
			else if((*this)(x,y)->blue + b <=0)
			{
				(*this)(x,y)->blue=0;			
			}
			else
			{
				(*this)(x,y)->blue=(*this)(x,y)->blue + b;
			}
		}

}

void Image::invertcolors()	//Makes each RGB component of each pixel equal to 255 minus its original value. 
{
	for(int y=0;y<this->height();y++)
		for(int x=0;x<this->width();x++)
		{
			(*this)(x,y)->red=255-(*this)(x,y)->red;
			(*this)(x,y)->green=255-(*this)(x,y)->green;
			(*this)(x,y)->blue=255-(*this)(x,y)->blue;
		}


}


