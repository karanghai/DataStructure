#include<iostream>
using namespace std;
/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{
    /// @todo Graded in MP3.1
	clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    /// @todo Graded in MP3.1
	ListNode * temp;
	if(head!=NULL&&tail!=NULL)
	{
		do {
			temp = head;
			head = head->next;
			delete temp;
		    } 
		while (head!= NULL);
 
	}	
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata)
{
    /// @todo Graded in MP3.1
	if(head!=NULL)
	{
		ListNode *A;
		A= new ListNode(ndata);
		A->next=head;
		A->prev=NULL;
		head->prev=A;
		head=A;
		length++;
	}
	else
	{
		ListNode *A;
		A= new ListNode(ndata);
		A->next=NULL;
		A->prev=NULL;
		head=A;
		tail=A;
		length++;
	}
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack( const T & ndata )
{
    /// @todo Graded in MP3.1
	if(tail!=NULL )
	{
		ListNode *A;
		A= new ListNode(ndata);
		tail->next=A;
		A->prev=tail;
		A->next=NULL;
		tail=A;
		length++;
	}
	
	else
	{
		ListNode *A;
		A= new ListNode(ndata);
		A->next=NULL;
		A->prev=NULL;
		head=A;
		tail=A;
		length++;
	}
}


/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{

	reverse(tail,head);
	
	
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse( ListNode * & startPoint, ListNode * & endPoint )
{
   
    /// @todo Graded in MP3.1
/*if(startPoint!=NULL && endPoint!=NULL && startPoint->prev!=NULL && endPoint->next!=NULL) //if in the middle
{
		
	ListNode * A;	
	A=startPoint->prev;
	ListNode * B;
	B=endPoint->next;

	if(startPoint==endPoint)
	return;
	
	ListNode *curr,*temp;
	curr=startPoint;
	
	while(curr!=B)
	{
		temp=curr->prev;		
		curr->prev=curr->next;
		curr->next=temp;
		curr=curr->prev;

	}			

	temp=endPoint;
	temp=curr_tail;	endPoint=startPoint;
	startPoint=temp;
	//startPoint->prev=A;
	//endPoint->next=B;

}
else if(startPoint!=NULL && endPoint!=NULL && startPoint->prev==NULL && endPoint->next!=NULL) // startPoint->prev=NULL
{
	
	ListNode * B;
	B=endPoint->next;

	if(startPoint==endPoint)
	return;
	
	ListNode *curr,*temp;
	curr=startPoint;
		
	while(curr!=B)
	{
		temp=curr->prev;		
		curr->prev=curr->next;
		curr->next=temp;
		curr=curr->prev;

	}			

	temp=endPoint;
	endPoint=startPoint;
	startPoint=temp;
	//startPoint->prev=NULL;ListNode * B;
	B=endPoint->next;
	ListNode * A;
	A=startPoint->prev;
	//endPoint->next=B;

}

else if(startPoint!=NULL && endPoint!=NULL && startPoint->prev!=NULL && endPoint->next==NULL) // endPoint->next=NULL
{
	
	if(startPoint==endPoint)
	return;
	
	ListNode *curr,*temp;
	curr=startPoint;
		
	while(curr!=NULL)
	{
		temp=curr->prev;		
		curr->prev=curr->next;
		curr->next=temp;
		curr=curr->prev;

	}			

	temp=endPoint;
	endPoint=startPoint;
	startPoint=temp;
	//startPoint->prev=A;
	//endPoint->next=NULL;

}
*/
if(startPoint!=NULL && endPoint!=NULL ) // endPoint->next=NULL
{
	
	if(startPoint==endPoint)
	return;
	int j=0;
	ListNode* np=startPoint;
	ListNode *temp_end=endPoint;
	while(temp_end!=NULL)
	{
		temp_end=temp_end->next;
		if(temp_end==startPoint)
		{
			startPoint=endPoint;
			endPoint=np;
			j++;
			break;
		}
	}	

	ListNode * A=startPoint->prev;
	ListNode * B =endPoint->next;
	
	
	
	
	ListNode *curr,*temp;
	curr=startPoint;
		
	while(curr!=B)
	{
		temp=curr->prev;		
		curr->prev=curr->next;
		curr->next=temp;
		curr=curr->prev;
		
	}			

	
	//if(endPoint->prev!=NULL)
	//ListNode * A =endPoint->prev;
	//if(startPoint->next	
	//ListNode * C =startPoint->next;
	
	if(j==0)
	{
		temp=endPoint;
		endPoint=startPoint;
		startPoint=temp;
		startPoint->prev=A;
		endPoint->next=B;		
	}
	
	//A->prev=endPoint;
	//C->next=startPoint;
	//startPoint->prev=A;
	//A->next=startPoint;
	//endPoint->next=B;
	//B->prev=endPoint;
	
}




}


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth( int n )
{
  /// @todo Graded in MP3.1
if(head!=NULL && tail!=NULL && n>1)
{
	/*int k=1;	
	int l=0;
	ListNode * curr=head;	
	ListNode * curr_tail=head;
	ListNode * nblock;
	while(curr_tail!=NULL)
	{
		if(curr_tail->next==NULL)		//if curr_tail reaches tail switch
		{
			if(l==0)
			{	
					
				reverse(head,curr_tail);
				l++;
				break;
			}			
			else			
			{	
					
				reverse(curr,curr_tail);
				break;	
			}	
		}				


		else if(k%n==0)		//if nth term, switch
		{
			
			if(l==0)
			{			
				nblock=curr_tail->next;			
				reverse(head,curr_tail);
				l++;
			}						
			
			else
			{	
				nblock=curr_tail->next;		
				reverse(curr,curr_tail);	
			}	
		}
		
					
		curr_tail=nblock;
		curr=nblock;
		k++;	
	}
		
	delete curr;
	delete curr_tail;*/

	ListNode * curr=head;
	ListNode * curr_tail=head;
	ListNode * temp;
	int j=0;
	
	while(curr_tail!=NULL)
	{
		for(int i=0;i<n-1;i++)
		{
			if(curr_tail->next!=NULL)			
			{			
				curr_tail=curr_tail->next;

			}
		}		
		
						
		reverse(curr,curr_tail);
		if(curr->prev!=NULL)
		curr->prev->next=curr;
		if(curr_tail->next!=NULL)		
		curr_tail->next->prev=curr_tail;
		
		
		curr=curr_tail->next;
		curr_tail=curr;
		
		
	}	
	while(head->prev!=NULL)
	head=head->prev;

	while(tail->next!=NULL)
	tail=tail->next;


}
}
/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
if(head==NULL || tail==NULL ||length==0)
return ;
   
else if(head!=tail&& head!=NULL && tail!=NULL)
{	
 /// @todo Graded in MP3.1


	ListNode * temp=head;
	ListNode * toRemove;
	ListNode * end1=tail;
	ListNode * temp2;	
	

	while (temp->next!=end1)
	{
		toRemove=temp->next;		
		temp2=toRemove->next;
		temp->next=temp2;
		temp2->prev=temp;
		end1->next=toRemove;
		toRemove->prev=end1;
		toRemove->next=NULL;
		end1=toRemove;
		temp=temp->next;
			
	}


}


}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head)
    {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    }
    else
    {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL)
    {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint)
{
    /// @todo Graded in MP3.2
if(start==NULL || length==0)
return NULL;

else if (length==1)
return start;

else if(splitPoint>=0&&splitPoint<=length)
{
	int count=0;
	ListNode * curr=start;	
	while(count<splitPoint)
	{
		curr=curr->next;
		count++;
	}
	if(curr!=NULL)	
	{	
		ListNode * temp=curr->prev;	
		temp->next=NULL;
		curr->prev=NULL;	
	}	
	
	return curr;

}
		
else
return NULL; // change me!
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if(tail != NULL)
    {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode * second)
{

ListNode * curr1=first;
ListNode * curr2=second;
ListNode * next_curr1;
ListNode * next_curr2;
ListNode * temp;

if(first!=NULL && second!=NULL)
{
	

	while(curr1!=NULL && curr2!=NULL)
	{	
		if(curr1->data<curr2->data||curr1->data==curr2->data)
		{
			
			next_curr1=curr1->next;//temporary Nodes
			temp=curr2->prev;//temporary Nodes		
			
			if(temp!=NULL)
			temp->next=curr1;
			curr1->prev=temp;		
			curr1->next=curr2;
			curr2->prev=curr1;
			
			curr1=next_curr1;
	
		} 


		else if(curr2->data<curr1->data)
		{
			next_curr2=curr2->next;//temporary Nodes
			temp=curr1->prev;//temporary Nodes		
			
			if(temp!=NULL)
			temp->next=curr2;
			curr2->prev=temp;
					
			curr2->next=curr1;
			curr1->prev=curr2;
			
			curr2=next_curr2;


		}

	


	}
	while(first->prev!=NULL)
	first=first->prev;
	return first;


}
/// @todo Graded in MP3.2

return NULL; // change me!

}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode * List<T>::mergesort(ListNode * start, int chainLength)
{
    /// @todo Graded in MP3.2
/*
if(start==NULL||chainLength<=0)
return NULL;

else if(chainLength==1)
return start;

else if(start!=NULL && chainLength>1)
{

if(chainLength%2==1)
return merge(mergesort(start,chainLength/2),mergesort(split(start,chainLength/2+1),chainLength/2+1));

else 
return merge(mergesort(start,chainLength/2),mergesort(split(start,chainLength/2),chainLength/2));
}*/
if(chainLength>1)
{
int divide=chainLength/2;
ListNode * start2=split(start,divide);
ListNode * first=mergesort(start,divide);
ListNode * second=mergesort(start2,chainLength-divide);

return merge(first,second);

}

else if (chainLength==1)
return start;


else
return NULL; // change me!




}




