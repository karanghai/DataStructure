#include "scene.h"
#include <iostream>
using namespace std;

Scene::Scene(int max)	//right
{
	im_array= new Image*[max];
	for(int i=0;i<max;i++)
		im_array[i]=NULL;
	maxim=max;
	x= new int[max];
	y= new int [max];	

}

Scene::Scene(const Scene & source)//right
{

	copy(source);

}

Scene::~Scene()//right
{
	clear();
}

void Scene::clear()//right
{
	
	if(im_array!=NULL)
	{
	for(int i=0;i<maxim;i++)
	{
		if(im_array[i]!=NULL)
		{
		delete im_array[i];
		}
	}	
	delete[] im_array;		
	}
	if(x!=NULL)	
	delete[] x;
	if(y!=NULL)
	delete[] y;
}


void Scene::copy(const Scene & source)	//helper function right
{
	maxim=source.maxim;
	im_array=new Image*[maxim];
	for(int i=0;i<maxim;i++)
	{
		if(source.im_array[i]!=NULL)
		{		
			im_array[i]=new Image(*(source.im_array[i]));
		} 	
		else
		im_array[i]=NULL;	
	}	
	x= new int[maxim];
	y= new int[maxim];
	for(int i=0;i<maxim;i++)
	{	
		x[i]=source.x[i];
		y[i]=source.y[i];
	}
}

const Scene & Scene::operator=(const Scene & source)//right
{
	if(this!=&source)
	{
	clear();
	copy(source);
	}
	return *this;


}

void Scene::changemaxlayers(int newmax)//right
{
	Image ** im_array_new= new Image*[newmax];
	int *new_x=new int[newmax];
	int *new_y=new int[newmax];
	if(im_array_new!= NULL && newmax>maxim && new_x!=NULL && new_y!=NULL)
	{
	for(int i=0; i<maxim; i++)
	im_array_new[i]=im_array[i];
        
        for(int i=maxim; i<newmax; i++)
        im_array_new[i]=NULL;
        
       
        for(int i=0; i<maxim; i++)
        {
            new_x[i]=x[i];
            new_y[i]=y[i];
        }
        for(int i=maxim; i<newmax; i++)
        {
            new_x[i]=0;
            new_y[i]=0;
        }
         maxim=newmax;
    }
    else if(newmax==maxim)
        return;
    else
        cout <<"invalid newmax" <<endl;
        
    delete[] im_array;
    im_array=im_array_new;
    im_array_new=NULL;
    delete[] im_array_new;

    delete[] x;
    x=new_x;
    new_x=NULL;
    delete[] new_x;

    delete[] y;
    y=new_y;
    new_y=NULL;
    delete[] y;   	
} 

void Scene::addpicture(const char * FileName,int index,int x1,int y1)//right
{
	if(index>=0&&index<maxim)
	{		
	im_array[index]= new Image();
	im_array[index]->readFromFile(FileName);
	x[index]=x1;
	y[index]=y1;
	}
	else
	cout << "index out of bounds" << endl;


}

void Scene::changelayer(int index,int newindex)//right
{
	if(index<0||index>maxim-1||newindex<0||newindex>maxim-1)		
	cout << "invalid index" << endl;
	
	if(index==newindex)
	return;
	
	x[newindex]=x[index];
	x[index]=0;
	y[newindex]=y[index];
	y[index]=0;
	
	if(im_array[newindex]!=NULL)
	{	
	delete im_array[newindex];	
	im_array[newindex]=im_array[index];
	im_array[index]=NULL;
	}
	else
	{
	im_array[newindex]=im_array[index];
	im_array[index]=NULL;	
	}
	
	
	
	
} 	

void Scene::translate(int index,int xccord,int ycoord)
{
	if(index<0||index>maxim-1||im_array[index]==NULL)
	{
	cout << "invalid index" << endl;
	return;
	}
	x[index]=xccord;
	y[index]=ycoord;

}

void Scene::deletepicture(int index)//right
{
	if(index<0||index>maxim-1||im_array[index]==NULL)
	{	
	cout << "invalid index" << endl;
	return;
	}	
	
	delete im_array[index];
	im_array[index]=NULL;
}

Image * Scene::getpicture (int index) const//right
{

	if(index<0||index>maxim-1||im_array[index]==NULL)	
	{	
	cout << "invalid index" << endl;	
	return NULL;
	}

	return im_array[index];
}


Image Scene::drawscene () const
{
	int xlength=0;
	int ylength=0;
	
	for(int i=0;i<maxim;i++)
	{ 
		if(im_array[i]!=NULL)
		{		
			if((im_array[i]->width()+x[i])>xlength)
			{
			xlength=im_array[i]->width()+x[i];
			}		
			if((im_array[i]->height()+y[i])>ylength)
			{	
			ylength=im_array[i]->height()+y[i];
			}
		}
	}
	Image dnewscene;
	dnewscene.resize(xlength,ylength);
	for(int i=0;i<maxim;i++)
	{
		if(im_array[i]!=NULL)	
		{		
			for(int j=0;j<im_array[i]->width();j++)
			{		
				for(int k=0;k<im_array[i]->height();k++)
				{
					*(dnewscene(j+x[i],k+y[i]))=*((*im_array[i])(j,k));	
				}	
			}
		}
	}	
	return dnewscene;
}




