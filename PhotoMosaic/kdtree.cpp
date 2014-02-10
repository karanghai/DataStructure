/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int current) const
{
    /**
     * @todo Implement this function!
     */
	if(first[current]==second[current])
	return (first<second);
	else	
	return(first[current]<second[current]);
}


template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const
{
    /**
     * @todo Implement this function!
     */
	int curr_distance=distance(currentBest, target);
	int potential_distance=distance(potential, target);
       
        if (curr_distance > potential_distance)
                return true;
        else if (potential_distance > curr_distance)
                return false;
        else
                return (potential < currentBest);
}
template <int Dim>
int KDTree<Dim>::distance(const Point<Dim> & point1, const Point<Dim> & point2) const
{
        int block,dist=0;
        for (int i=0; i < Dim ;i++)
        {
            dist=dist+(point1[i]-point2[i])*(point1[i]-point2[i]);
        }
        return dist;
}

template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
{
    /**
     * @todo Implement this function!
     */
	point_size=newPoints.size();
   if(!newPoints.empty())
	{	
		points.resize(newPoints.size());
		for(int i=0;i<newPoints.size();i++)		
		points[i]=newPoints[i];
		buildTree(points,0,0,points.size()-1);		
	}
}


template<int Dim>
void KDTree<Dim>::buildTree(vector < Point<Dim> > & newPoints, int curDim, int left_index, int right_index)
{
	if(right_index<=left_index)
	return;
	int median=(right_index+left_index)/2;
	find(points, left_index, right_index, median, curDim);
        buildTree(points,(curDim+1)%Dim,left_index,median-1);
        buildTree(points, (curDim+1)%Dim,median+1,right_index);

}

template<int Dim>
void KDTree<Dim>::find(vector< Point<Dim> >& newPoints, int left_index, int right_index, int median, int dim)
{
    if(left_index>=right_index)
        return;
    int pivot= partition(newPoints, left_index, right_index, median, dim);

    if(median < pivot)
        return find(newPoints, left_index, pivot-1, median, dim);
        
    if(median > pivot)
        return find(newPoints, pivot+1, right_index, median, dim);
        
    if(median == pivot)
        return;
    
}

template<int Dim>
int KDTree<Dim>::partition(vector< Point<Dim> >& newPoints, int left_index, int right_index, int pivotIndex, int dim)
{
	pivotIndex=(left_index+right_index)/2;
	Point<Dim> pivotVal=newPoints[pivotIndex];
	swap(newPoints[pivotIndex],newPoints[right_index]);
	int storeIndex=left_index;
	for(int i=left_index;i<right_index;i++)
	if(smallerDimVal(newPoints[i],pivotVal,dim))
	{
		swap(newPoints[storeIndex],newPoints[i]);
		storeIndex++;
	}

	swap(newPoints[right_index],newPoints[storeIndex]);
	return storeIndex;
}

template<int Dim>
void KDTree<Dim>::swap(Point<Dim> & first, Point<Dim> & second)
{
    Point<Dim> tmp=first;
    first=second;
    second=tmp;
}

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const
{
    /**
     * @todo Implement this function!
     */
	return findNearestNeighbor(query, 0, point_size-1, 0);
}

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query, int left, int right, int dim) const
{
    int median= (left+right)/2;
    Point<Dim> mid= points[median];
    Point<Dim> currentBest;
    bool flag= false;
    if(left>=right)
        return points[left];
    
    if(smallerDimVal(query, mid, dim))
    {
        currentBest=findNearestNeighbor(query, left, median-1, (dim+1)%Dim);
        flag=true;
    }
   
    else
    {
        currentBest=findNearestNeighbor(query, median+1, right, (dim+1)%Dim);
        flag=false;
    }
    int bestDistance=pointDistance(currentBest, query);

    if(shouldReplace(query, currentBest, mid))
    {
        currentBest=mid;
        bestDistance=pointDistance(mid, query);
    }
   
   
    if(otherTreeDistance(query, mid, bestDistance, dim))
    {
        Point<Dim> otherMin;
        if(flag)
        {
            otherMin=findNearestNeighbor(query, median+1, right, (dim+1)%Dim);
        }
        else
            otherMin=findNearestNeighbor(query, left, median-1, (dim+1)%Dim);
            
        if(shouldReplace(query, currentBest, otherMin))
            currentBest=otherMin;
    }
    
    
    return currentBest;
}

template<int Dim>
bool KDTree<Dim>:: otherTreeDistance(const Point<Dim> & query, const Point<Dim> & parent, int bestDistance, int dim) const
{
    int distance1=pow(query[dim]-parent[dim], 2);
    if(distance1>bestDistance)
        return false;
    else
        return true;
}

template<int Dim>
int KDTree<Dim>::pointDistance(const Point<Dim> & target, const Point<Dim> & currentBest) const
{
    int best_distance=0;
    for(int i=0; i<Dim; i++)
        best_distance+= (currentBest[i]-target[i])*(currentBest[i]-target[i]);
    
    return best_distance;
} 


