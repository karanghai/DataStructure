#ifndef SCENE1_H
#define SCENE1_H

#include "image.h"//adding image.h
class Scene: public PNG 
{
	public:
	Scene(int max);
	~Scene();
	Scene(const Scene &source);
	const Scene & operator=(const Scene &source);	
	void changemaxlayers(int newmax);
	void addpicture(const char *FileName,int index,int x, int y);
	void changelayer(int index,int newindex);
	void translate(int index, int xcoord,int ycoord);
	void deletepicture (int index);
	Image* getpicture(int index) const;
	Image drawscene() const;
	void copy(const Scene & source);
	Image **im_array;
	void clear();
	private:
	int *x;
	int *y;
	int maxim;

	
};

#endif 
