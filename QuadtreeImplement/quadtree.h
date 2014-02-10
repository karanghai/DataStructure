// **************************************************************
// *		   
// *  quadtree.h
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

class Quadtree
{
	
	
	
    	
	
	private:

	// A simple class representing a single node of a Quadtree.
	// You may want to add to this class; in particular, it could probably
	// use a constructor or two...
	class QuadtreeNode
	{
		public:
		QuadtreeNode* nwChild;  // pointer to northwest child
		QuadtreeNode* neChild;  // pointer to northeast child
		QuadtreeNode* swChild;  // pointer to southwest child
		QuadtreeNode* seChild;  // pointer to southeast child

		RGBAPixel element;  // the pixel stored as this node's "data"
       
		void copy(QuadtreeNode * nroot);
		QuadtreeNode()          //QuadtreeNode no arg constructor
        	{
            	     nwChild=NULL;
            	     neChild=NULL;
            	     swChild=NULL;
       		     seChild=NULL;
       		     element.red=0;
       		     element.green=0;
       		     element.blue=0;
       		     element.alpha=0;
       		 }
        
        	QuadtreeNode(RGBAPixel other_element)
        	{
                 
         	   nwChild=NULL;
         	   nwChild=NULL;
         	   nwChild=NULL;
         	   nwChild=NULL;
	
         	   element.red=other_element.red;
         	   element.green=other_element.green;
         	   element.blue=other_element.blue;
         	   element.alpha=other_element.alpha;
         		           
          
        }
    };
	
	QuadtreeNode* root;    // pointer to root of quadtree
	int resolution; //resolution
	
	
	public:
	
	Quadtree();

	Quadtree(const PNG & source, int new_resolution);

	Quadtree(Quadtree const & other);

	~Quadtree();	
	   
	Quadtree const & operator=(Quadtree const & other);

	void buildTree(PNG const & source, int new_resolution);

	RGBAPixel getPixel(int x, int y) const;

	PNG decompress() const;
	
	void clockwiseRotate ( ) ;
	
	void prune ( int  tolerance) ;

	int pruneSize( int  tolerance) const;
	
	int idealPrune ( int  numLeaves) const;

	

	//helper functions	
	void clear(QuadtreeNode * &del_root);
	void copy(Quadtree const &other);
	void  buildTreehelper(QuadtreeNode* &nroot,PNG const & source1,int new_resolution,int x,int y );
	void average (QuadtreeNode * &nroot);
	RGBAPixel getPixelHelper(QuadtreeNode * point,int x, int y, int new_resolution)const;
	void clockwiseRotateHelper(QuadtreeNode * nroot);
	void pruneHelper(QuadtreeNode* nroot, int tolerance);
	bool prunable(QuadtreeNode* nroot, RGBAPixel &color, int tolerance)const;
	int accepted_tolerance(RGBAPixel color1,RGBAPixel color2)const;
	int QuadtreeLeaves(QuadtreeNode * nroot)const;
	int prunesizeHelper(QuadtreeNode * nroot, int tolerance)const;
	
	/**** Functions added for testing/grading                ****/
	/**** Do not remove this line or copy its contents here! ****/
	#include "quadtree_given.h"
};

#endif
