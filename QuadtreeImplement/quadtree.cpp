// **************************************************************
// *		   
// *  quadtree.cpp
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#include "quadtree.h"
#include "math.h"

//No argument constructor
Quadtree::Quadtree()
{
	resolution=0;	
	root =NULL;
}
//Constructor with two argument, a PNG file and the resolution 
Quadtree::Quadtree (const PNG & source, int new_resolution)
{
	
	root=NULL;   
	resolution=new_resolution;
    	buildTree(source,new_resolution);
}
//Copy constructor
Quadtree::Quadtree(Quadtree const & other)
{
        copy(other);
}
//Destructor
Quadtree::~Quadtree()
{
	clear(root);
	root=NULL;
}

//Operator= function
Quadtree const & Quadtree::operator=(Quadtree const & other)
{
	if(this!=&other)
	{
	        clear(root);
	     	copy(other);
	
	} 
	
	return *this;

}


//Helper function clear for destructor
void Quadtree::clear(QuadtreeNode * &del_root)
{
	if(del_root==NULL)
		return;
	
		clear(del_root->nwChild);	
		clear(del_root->neChild);	
		clear(del_root->swChild);	
		clear(del_root->seChild);	

	delete del_root;
	del_root=NULL;
}
	

//Helper function copy used in constructors
void Quadtree::copy(Quadtree const & other)
{
	root=NULL;
	if(other.root==NULL)return;	
	if(other.root!=NULL)
	{
		root=new QuadtreeNode();
		root->copy(other.root);
	}
	resolution=other.resolution;
}
//Helper function to the helper function copy, its in the QuadtreeNode to make access to elements easier
void Quadtree::QuadtreeNode::copy(QuadtreeNode * nroot)
{
	if(nroot==NULL)
	return;
	
	//if(nroot->nwChild==NULL)
	//return;	
	
	if(nroot->nwChild!=NULL)
	{
		nwChild=new QuadtreeNode();
		neChild=new QuadtreeNode();
		swChild=new QuadtreeNode();
		seChild=new QuadtreeNode();
	}

	nwChild->copy(nroot->nwChild);
	neChild->copy(nroot->neChild);
	swChild->copy(nroot->swChild);
	seChild->copy(nroot->seChild);
	element=nroot->element;

}

//Buildtree Helper Function
void Quadtree:: buildTreehelper(QuadtreeNode* &nroot,PNG const & source1,int new_resolution,int x,int y )
{
	if(nroot==NULL) return;	
	    
		if(new_resolution==1)
   	 	{
     		nroot->element= *source1(x,y);
	
		return;
    		}
   
  	  	nroot->nwChild= new QuadtreeNode();
 		nroot->neChild= new QuadtreeNode();
		nroot->swChild= new QuadtreeNode();
		nroot->seChild= new QuadtreeNode();
    		buildTreehelper(nroot->nwChild,source1,new_resolution/2,x,y);
    		buildTreehelper(nroot->neChild,source1,new_resolution/2,x+(new_resolution/2),y);
    		buildTreehelper(nroot->swChild,source1,new_resolution/2,x,y+(new_resolution/2));
   		buildTreehelper(nroot->seChild,source1,new_resolution/2,x+(new_resolution/2),y+(new_resolution/2));
       
		average(nroot);
}

//Calculates average rgb components of children and inputs it to the parents element
void Quadtree::average(QuadtreeNode *&nroot)
{
	 nroot->element.red = ((nroot->nwChild->element.red) +(nroot->neChild->element.red) +(nroot->swChild->element.red) +(nroot->seChild->element.red))/4;
   	 nroot->element.green = ((nroot->nwChild->element.green) +(nroot->neChild->element.green) +(nroot->swChild->element.green) +(nroot->seChild->element.green))/4;
  	 nroot->element.blue = ((nroot->nwChild->element.blue) +(nroot->neChild->element.blue) + (nroot->swChild->element.blue) +(nroot->seChild->element.blue))/4;
	 nroot->element.alpha = ((nroot->nwChild->element.alpha) +(nroot->neChild->element.alpha) +(nroot->swChild->element.alpha) + (nroot->seChild->element.alpha))/4;
}

//Buildtree
void Quadtree::buildTree(PNG const & source, int new_resolution)
{
	clear(root);
	
	resolution=new_resolution;
	root=new QuadtreeNode();    	
	buildTreehelper(root,source,new_resolution,0,0);
}




//Helper for getPixel
RGBAPixel Quadtree:: getPixelHelper(QuadtreeNode * point,int x, int y, int new_resolution)const
{
	
	if(new_resolution==1||point->nwChild==NULL)
	return point->element;

	else if(x<new_resolution/2 && y<new_resolution/2)
	return getPixelHelper(point->nwChild,x,y,new_resolution/2);

	else if(x>=new_resolution/2 && y<new_resolution/2)
	{	
		return getPixelHelper(point->neChild,x-(new_resolution/2),y,new_resolution/2);
	}
	else if(x<new_resolution/2 && y>=new_resolution/2)
	{	
			
		return getPixelHelper(point->swChild,x,y-(new_resolution/2),new_resolution/2);
	}
	else if(x>=new_resolution/2 && y>=new_resolution/2)
	{	
		return getPixelHelper(point->seChild,x-(new_resolution/2),y-(new_resolution/2),new_resolution/2);
	}
	return RGBAPixel();

}
//GetPixel
RGBAPixel Quadtree::getPixel(int x, int y)const
{
	if(resolution<=0)
	return RGBAPixel();
	
	else if(x<0||y<0)
	return RGBAPixel();
	
	else if(x>=resolution||y>=resolution)
	return RGBAPixel();
	
	else return getPixelHelper(root,x,y,resolution);

	

}


//Decompress
PNG Quadtree::decompress() const
{
	PNG new_image= PNG(resolution,resolution);
	for(int i=0;i<resolution;i++)
		for(int j=0;j<resolution;j++)
		{
			
		(new_image)(i,j)->red=getPixel(i,j).red;
		(new_image)(i,j)->green=getPixel(i,j).green;
		(new_image)(i,j)->blue=getPixel(i,j).blue;
		(new_image)(i,j)->alpha=getPixel(i,j).alpha;
		}
	return new_image;
	
}

//ClockwiseRotate Heper function
void Quadtree::clockwiseRotateHelper(QuadtreeNode * nroot)
{
	if(nroot==NULL)
	return;
	
	QuadtreeNode * temp ;
	temp=nroot->nwChild;
	nroot->nwChild=nroot->swChild;
	nroot->swChild=nroot->seChild;
	nroot->seChild=nroot->neChild;
	nroot->neChild=temp;
		
	
	clockwiseRotateHelper(nroot->nwChild);
	clockwiseRotateHelper(nroot->neChild);
	clockwiseRotateHelper(nroot->swChild);
	clockwiseRotateHelper(nroot->seChild);	
	
	

}

//ClockWise Rotate
void Quadtree::clockwiseRotate 	( ) 
{
	if(root!=NULL)
	 clockwiseRotateHelper(root);

}	



//Prune helper function
void Quadtree::pruneHelper(QuadtreeNode * nroot, int tolerance) 
{
	if(nroot==NULL)
	return;
	
	else if(nroot->nwChild==NULL) //no children
	return;
	
	if(prunable(nroot,nroot->element,tolerance))
	{
		clear(nroot->nwChild);
		clear(nroot->neChild);
		clear(nroot->swChild);
		clear(nroot->seChild);
	}

	pruneHelper(nroot->nwChild,tolerance);
	pruneHelper(nroot->neChild,tolerance);
	pruneHelper(nroot->swChild,tolerance);
	pruneHelper(nroot->seChild,tolerance);
		
		
	
}
//prunable ----checks if it can be pruned or not
bool Quadtree:: prunable(QuadtreeNode* nroot, RGBAPixel &color, int tolerance)const
{
	if(nroot!=NULL)
	{	
	if(nroot->nwChild==NULL)
	{
		if(accepted_tolerance(nroot->element,color)<=tolerance)
		return true;
		else false;
	} 
	
	if(prunable(nroot->nwChild,color,tolerance)&&prunable(nroot->neChild,color,tolerance)&&prunable(nroot->swChild,color,tolerance)&&prunable(nroot->seChild,color,tolerance))
	return true;
	
	else return false;
	}
	
	else return false;
	
}


//Returns a value which when compares to the tolerance determines if its prunable or not
int Quadtree::accepted_tolerance(RGBAPixel color1,RGBAPixel color2)const
{
	int accepted=pow((color1.red-color2.red),2)+pow((color1.green-color2.green),2)+pow((color1.blue-color2.blue),2);
	return accepted;
}


//Prune 
void Quadtree::prune ( int tolerance) 
{
	return pruneHelper(root,tolerance);
}


//Prints out number of leaves given a node
int Quadtree::QuadtreeLeaves(QuadtreeNode * nroot)const
{
	if(nroot->nwChild==NULL)
	return 1;
	else
	{
		return QuadtreeLeaves(nroot->nwChild)+QuadtreeLeaves(nroot->neChild)+QuadtreeLeaves(nroot->swChild)+QuadtreeLeaves(nroot->seChild);
		
	}	
}

//Helper function to prunesize
int Quadtree::prunesizeHelper(QuadtreeNode * nroot, int tolerance)const
{
	if(nroot->nwChild==NULL)
	return 0;
	
	if(prunable(nroot->nwChild,nroot->element,tolerance)&&prunable(nroot->neChild,nroot->element,tolerance)&&prunable(nroot->swChild,nroot->element,tolerance)&&prunable(nroot->seChild,nroot->element,tolerance))
	return QuadtreeLeaves(nroot)-1;
	
	else 
	return prunesizeHelper(nroot->nwChild,tolerance)+prunesizeHelper(nroot->neChild,tolerance)+prunesizeHelper(nroot->swChild,tolerance)+prunesizeHelper(nroot->seChild,tolerance);
	
}

//PruneSize
int Quadtree::pruneSize ( int  	tolerance) const
{
	if(root!=NULL)
	return QuadtreeLeaves(root)-prunesizeHelper(root,tolerance);	
	return 0;	
	
}	



//IdealPrune
int Quadtree::idealPrune ( int  numLeaves) const
{
	int low=0;
	int high=3*(255*255);
	int mid;
	
	
	while(low <= high)
	{	
		mid=(low+high)/2;
				
		if(pruneSize(mid)==numLeaves)
		{		
			while(pruneSize(mid)==numLeaves)
			mid--;			
			return mid+1;		
		}
		if(pruneSize(mid)>numLeaves)
		low=mid+1;
		
		else        
                high=mid-1;
	}         
	
	return low;		
}







