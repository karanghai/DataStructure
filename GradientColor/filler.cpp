/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace. Heavily based on
 * old MP4 by CS225 Staff, Fall 2010.
 * 
 * @author Chase Geigle
 * @date Fall 2012
 */
#include "filler.h"

animation filler::dfs::fillSolid( PNG & img, int x, int y, 
        RGBAPixel fillColor, int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to fill with the correct colorPicker parameter.
     */
	solidColorPicker dfsa(fillColor);
	return fill( img, x,y,dfsa,tolerance,frameFreq );
	
   // return animation();
}

animation filler::dfs::fillGrid( PNG & img, int x, int y, 
        RGBAPixel gridColor, int gridSpacing, int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to fill with the correct colorPicker parameter.
     */
   gridColorPicker dfsb(gridColor, gridSpacing);
	return fill( img, x,y,dfsb,tolerance,frameFreq );
	// return animation();
}

animation filler::dfs::fillGradient( PNG & img, int x, int y, 
        RGBAPixel fadeColor1, RGBAPixel fadeColor2, int radius, 
        int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to fill with the correct colorPicker parameter.
     */
  gradientColorPicker dfsc(fadeColor1,fadeColor2,radius,x,y);
	return fill( img, x,y,dfsc,tolerance,frameFreq );
//  return animation();
}

animation filler::dfs::fill( PNG & img, int x, int y, 
        colorPicker & fillColor, int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to filler::fill with the correct template parameter
     *  indicating the ordering structure to be used in the fill.
     */
	return filler::fill<Stack>(img,x,y,fillColor,tolerance,frameFreq); 
 //  return animation();
}

animation filler::bfs::fillSolid( PNG & img, int x, int y, 
        RGBAPixel fillColor, int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to fill with the correct colorPicker parameter.
     */
	solidColorPicker bfsa(fillColor);
	return fill( img, x,y,bfsa,tolerance,frameFreq );
  //  return animation();
}

animation filler::bfs::fillGrid( PNG & img, int x, int y, 
        RGBAPixel gridColor, int gridSpacing, int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to fill with the correct colorPicker parameter.
     */
	gridColorPicker bfsb(gridColor, gridSpacing);
	return fill( img, x,y,bfsb,tolerance,frameFreq );
   // return animation();
}

animation filler::bfs::fillGradient( PNG & img, int x, int y, 
        RGBAPixel fadeColor1, RGBAPixel fadeColor2, int radius, 
        int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to fill with the correct colorPicker parameter.
     */
	gradientColorPicker bfsc(fadeColor1,fadeColor2,radius,x,y);
	return fill( img, x,y,bfsc,tolerance,frameFreq );
    //return animation();
}

animation filler::bfs::fill( PNG & img, int x, int y, 
        colorPicker & fillColor, int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to filler::fill with the correct template parameter
     *  indicating the ordering structure to be used in the fill.
     */
	return filler::fill<Queue>(img,x,y,fillColor,tolerance,frameFreq);
   // return animation();
}

template <template <class T> class OrderingStructure>
animation filler::fill( PNG & img, int x, int y,
        colorPicker & fillColor, int tolerance, int frameFreq ) {
    /**
     * @todo You need to implement this function!
     *
     * This is the basic description of a flood-fill algorithm: Every fill
     * algorithm requires an ordering structure, which is passed to this
     * function via its template parameter. For a breadth-first-search
     * fill, that structure is a Queue, for a depth-first-search, that
     * structure is a Stack. To begin the algorithm, you simply place the
     * given point in the ordering structure. Then, until the structure is
     * empty, you do the following:
     *
     * 1.     Remove a point from the ordering structure. 
     *
     *        If it has not been processed before and if its color is
     *        within the tolerance distance (up to and **including**
     *        tolerance away in square-RGB-space-distance) to the original
     *        point's pixel color [that is, \f$(currentRed - OriginalRed)^2 +
              (currentGreen - OriginalGreen)^2 + (currentBlue -
              OriginalBlue)^2 \leq tolerance\f$], then: 
     *        1.    indicate somehow that it has been processed (do not mark it
     *              "processed" anywhere else in your code) 
     *        2.    change its color in the image using the appropriate
     *              colorPicker
     *        3.    add all of its neighbors to the ordering structure, and 
     *        4.    if it is the appropriate frame, send the current PNG to the
     *              animation (as described below).
     * 2.     When implementing your breadth-first-search and
     *        depth-first-search fills, you will need to explore neighboring
     *        pixels in some order.
     *
     *        While the order in which you examine neighbors does not matter
     *        for a proper fill, you must use the same order as we do for
     *        your animations to come out like ours! The order you should put
     *        neighboring pixels **ONTO** the queue or stack is as follows:
     *        **RIGHT(+x), DOWN(+y), LEFT(-x), UP(-y). IMPORTANT NOTE: *UP*
     *        here means towards the top of the image, so since an image has
     *        smaller y coordinates at the top, this is in the *negative y*
     *        direction. Similarly, *DOWN* means in the *positive y*
     *        direction.** To reiterate, when you are exploring (filling out)
     *        from a given pixel, you must first try to fill the pixel to
     *        it's RIGHT, then the one DOWN from it, then to the LEFT and
     *        finally UP. If you do them in a different order, your fill may
     *        still work correctly, but your animations will be different
     *        from the grading scripts!
     * 3.     For every k pixels filled, **starting at the kth pixel**, you
     *        must add a frame to the animation, where k = frameFreq. 
     *
     *        For example, if frameFreq is 4, then after the 4th pixel has
     *        been filled you should add a frame to the animation, then again
     *        after the 8th pixel, etc.  You must only add frames for the
     *        number of pixels that have been filled, not the number that
     *        have been checked. So if frameFreq is set to 1, a pixel should
     *        be filled every frame.
     */
	int frames=0;
	animation a;
	OrderingStructure<int> x_dir;
	OrderingStructure<int> y_dir;
	int curr_x=0;
	int curr_y=0;
	int tmp_x=0;
	int tmp_y=0;
	int tolerance_check;
	int used[img.width()][img.height()];
	x_dir.add(x);
	y_dir.add(y);
	RGBAPixel asdf=(*img(x, y));

	for(int b=0; b<img.width(); b++)
	for(int c=0; c<img.height(); c++)
		used[b][c]=0;

	while(!x_dir.isEmpty() && !y_dir.isEmpty())
	{
		if(!x_dir.isEmpty() && !y_dir.isEmpty())
		{
		curr_x=x_dir.remove();
		curr_y=y_dir.remove();
		}
	//check tolerance
	if(used[curr_x][curr_y]==0)
	{
	for(int i=1; i<5; i++)
	{
//cout<<"HI"<<endl;
	if(i==1)
	{
	tmp_y=curr_y;
	tmp_x=curr_x+1;
	}
	if(i==2)
	{
	tmp_y=curr_y+1;
	tmp_x=curr_x;
	}
		if(i==3)
		{
		tmp_y=curr_y;
		tmp_x=curr_x-1;
		}
	if(i==4)
	{
	tmp_y=curr_y-1;
	tmp_x=curr_x;
	}
	
	if(tmp_x>=0 && tmp_x<img.width() && tmp_y>=0 && tmp_y<img.height() && used[tmp_x][tmp_y]==0)
{
	tolerance_check=pow(asdf.red-img(tmp_x, tmp_y)->red, 2)+pow(asdf.blue-img(tmp_x, tmp_y)->blue, 2)+pow(asdf.green-img(tmp_x, tmp_y)->green, 2);

	//adding if tolerance is O.K.
	if(tolerance_check<=tolerance)
	{
	x_dir.add(tmp_x);
	y_dir.add(tmp_y);
	}
	}
	}
	}
	if(used[curr_x][curr_y]==0)
	{
	(*img(curr_x, curr_y))=fillColor(curr_x, curr_y);
	used[curr_x][curr_y]=1;
	frames++;
	if(frames==frameFreq)
	{
	frames=0;
	a.addFrame(img);
	}
	}
	
	}
	return a;
	
}
