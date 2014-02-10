#ifndef EMAZE_H
#define EMAZE_H

#include "dsets.h"
#include <vector>
#include "png.h"
#include <iostream>
using namespace std;

class SquareMaze
{
    public:
        void makeMaze(int width,int height);
        bool canTravel(int x,int y ,int dir);
        void setWall(int x, int y,int dir,bool exists);
        vector<int> solveMaze();
        PNG * drawMaze();//const;
        PNG * drawMazeWithSolution();
	SquareMaze();
	void rightRemove(int x, int y, DisjointSets & maze,int & count,int i);
	void bottomRemove(int x, int y, DisjointSets & maze,int & count,int i);
	
	vector<int> solved;
	PNG *nosolMaze;
	//PNG *nosolMaze;
	
	//bool canBreak(int x, int y, int dir);
    private:
        int maze_height;//maze_height;
        int maze_width;//maze_width;
	int blocks;//tile_num;//tile_num;
        vector<bool> right,bottom;
	
} ;       

#endif 
