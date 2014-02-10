#include "maze.h"
#include "dsets.h"
#include <iostream>
using namespace std;
SquareMaze::SquareMaze()
{
}

void SquareMaze::makeMaze(int width, int height)
{

right.clear();
bottom.clear();


maze_width = width;
maze_height = height; 
blocks = maze_width * maze_height; 
right.resize(blocks,true);
bottom.resize(blocks,true); 

DisjointSets maze; 
maze.addelements(blocks); 

srand(time(NULL));

//int x, y; 
bool rightmost=true, bottommost=true; 

int count = 0; 
//int rindex;
	while (count< (blocks - 1)) 
	{
		int rindex = rand() % blocks; 
		int x = rindex%maze_width;
		int y = rindex/maze_width;

		if(x==(maze_width-1))
		rightmost=true;
		else rightmost=false;

		if(y==(maze_height-1))
		bottommost=true;
		else bottommost=false;

		if (( rightmost == true ) && ( bottommost == true ))
		{
			rightmost=rightmost;
		}
		else if (!rightmost  && !bottommost)
		 {
			int action=rand()%3;			
					
			if (action == 0)  
			rightRemove(x,y,  maze,count,rindex);
			
		
			else if (action == 1)
			bottomRemove(x,y,  maze,count,rindex);

			else { 
			if ((maze.find(rindex) != maze.find(rindex+1)) && (maze.find(rindex) != maze.find(rindex+maze_width))&& (maze.find(rindex+1) != maze.find(rindex+1)))
			 { 
				setWall(x, y, 0, false); 
				setWall(x, y, 1, false); 
				maze.setunion(rindex, rindex+1); 
				maze.setunion(rindex, rindex+maze_width);
				count+=2;
			}
		}
		}
		
		
		else if(bottommost)
		{
			int action=rand()%2;			 
			if (action== 1)rightRemove(x,y,  maze,count,rindex);
		}
		
		else
		{
			int action =rand()%2;
			if (action == 1)bottomRemove(x,y,  maze,count,rindex);
		}

	}

}

void SquareMaze::rightRemove(int x, int y, DisjointSets & maze,int & count,int rindex)
{
		if (maze.find(rindex) != (maze.find(rindex+1))) 
		{
			setWall(x, y, 0, false); 
			maze.setunion(rindex, rindex+1); 
			count++;
		}


}

void SquareMaze::bottomRemove(int x, int y, DisjointSets & maze,int & count,int rindex)
{
		if (maze.find(rindex) != maze.find(rindex+maze_width))
		{
			setWall(x, y, 1, false); 
			maze.setunion(rindex, rindex+maze_width);
			count++;
		}

}


bool SquareMaze::canTravel(int x, int y, int dir)
{
int index = maze_width*y + x;
	
	if(dir==0 && x==maze_width-1) return false;
	if(dir==1 && y==maze_height-1)return false;
	if(dir==2 && x==0) return false;
	if(dir==3 && y==0)return false;	

//^^general cases; nothing to do with walls

	if(dir==0)
	{
		if(right[index]) return false;
		else return true;
	}

	else if(dir==1)
	{
		if(bottom[index])return false;
		else return true;		
	}

	else if(dir==2)
	{
		if(right[index-1])return false;
		else return true;
	}
	
	else if (dir==3)
	{
		if(bottom[index-maze_width])return false;
		return true;
	}

	else return false;
 
}


void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
	
		if (exists)
		 { 
			if(!dir)
			right[(y*maze_width) + x] = true;
			else if(dir) 
			bottom[(y*maze_width) + x] = true;
		}
		 


		if (!exists) 
		{ 
			if(!dir)
			right[(y*maze_width) + x] = false;
			else if(dir)
			bottom[(y*maze_width) + x] = false;
		
		}
	
	
}

vector<int> SquareMaze::solveMaze()
{
	
return vector<int>();	
}


		

PNG * SquareMaze::drawMaze() //const
{

nosolMaze = new PNG(maze_width*10+1,maze_height*10+1);

	for(int i=0;i<nosolMaze->width();i++)
	{
		if(!(i>=1&&i<=9))
		{
			(*nosolMaze)(i,0)->red=0;
			(*nosolMaze)(i,0)->green=0;
			(*nosolMaze)(i,0)->blue=0;	
		}
	}		
		

	for(int i=0;i<nosolMaze->height();i++)
	{
		
		
			(*nosolMaze)(0,i)->red=0;
			(*nosolMaze)(0,i)->green=0;
			(*nosolMaze)(0,i)->blue=0;	
		
	}		

	int x,y;	
	for(int i=0;i<blocks;i++)
	{
		x=i%maze_width;
		y=i/maze_width;
		if(right[i])
		{
			for(int k=0;k<=10;k++)
			{
				(*nosolMaze)((x+1)*10,(y*10)+k)->red=0;
				(*nosolMaze)((x+1)*10,(y*10)+k)->green=0;
				(*nosolMaze)((x+1)*10,(y*10)+k)->blue=0;
			}
		}			
	

		if(bottom[i])
		{
			for(int k=0;k<=10;k++)
			{
				(*nosolMaze)((x*10)+k,(y+1)*10)->red=0;
				(*nosolMaze)((x*10)+k,(y+1)*10)->green=0;
				(*nosolMaze)((x*10)+k,(y+1)*10)->blue=0;
			}
		}			

	}		

	return nosolMaze;
}


PNG * SquareMaze::drawMazeWithSolution()
{
	return drawMaze();
	int x=5;
	int y=5;

	int temp;
	for(int i =0;i<solved.size();i++)
	{	
		if(solved[i]==0)
		{
			temp=x+10;
			for(x;x<=temp;x++)
			{
				(*nosolMaze)(x,y)->red=255;
				(*nosolMaze)(x,y)->green=0;
				(*nosolMaze)(x,y)->blue=0;
		
			}	

			x--;
		}
		



		else if(solved[i]==1)
		{
			temp=y+10;
			for(y;y<=temp;y++)
			{
				(*nosolMaze)(x,y)->red=255;
				(*nosolMaze)(x,y)->green=0;
				(*nosolMaze)(x,y)->blue=0;
		
			}	
			y--;		
		}

		else if(solved[i]==2)
		{
			temp=x-10;
			for(x;x<=temp;x++)
			{
				(*nosolMaze)(x,y)->red=255;
				(*nosolMaze)(x,y)->green=0;
				(*nosolMaze)(x,y)->blue=0;
		
			}	
			x--;		
		}


		else if(solved[i]==3)
		{
			temp=y-10;
			for(y;y<=temp;y++)
			{
				(*nosolMaze)(x,y)->red=255;
				(*nosolMaze)(x,y)->green=0;
				(*nosolMaze)(x,y)->blue=0;
		
			}	
			y--;		
		}

}





}


