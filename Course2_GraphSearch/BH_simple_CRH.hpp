// https://gist.github.com/clarkngo/65c7837f0d558e8ce6becad55f860f4e
// [CRH] This is a simplified heap
// because it only has no add element
// this need to update to know the corresponding vertex

#include<iostream>
#include<climits> // list of limited values
#include<math.h> // for print
using namespace std;
// #define DEBUG

// Prototype of a utility function to swap two integers
void swap(int *x, int *y);

// A class for Min Heap
class MinHeap
{
	int *harr; // pointer to array of elements in heap
    int *varr; // pointer to array of elements corresponds to vertex
	int capacity; // maximum possible size of min heap
	int heap_size; // Current number of elements in min heap
  public:
	// Constructor
	MinHeap(int capacity);

	// to heapify a subtree with the root at given index
	void MinHeapify(int );

	int parent(int i) { return (i-1)/2; }

	// to get index of left child of node at index i
	int left(int i) { return (2*i + 1); }

	// to get index of right child of node at index i
	int right(int i) { return (2*i + 2); }

	// to extract the root which is the minimum element
	int extractMin();

	// Decreases key value of key at index i to new_val
	void decreaseKey(int i, int new_val);

	// Returns the minimum key (key at root) from min heap
	int getMin() { return harr[0]; }

    // Returns the minimum vector at root from min heap
	int getMinv() { return varr[0]; }


	// Deletes a key stored at index i
	void deleteKey(int i);

	// Inserts a new key 'k', with v goes to the matrix
	void insertKey(int k, int v);

    // check if heap is empty
	bool empty();

	// get heap size
	int getsize();

	void printheap();
};

bool MinHeap::empty(){
	if (heap_size==0) return true;
	return false;
}
int MinHeap::getsize(){
	return heap_size;
}


void MinHeap::printheap(){
    int row = 0;
    row =(int) log2((double) heap_size+1)+1;
    int i = 0;
    int j = 0;
    for( i = 0;i<row;i++){
        int j_start = j;
        int total = (int) pow((double) 2, (double) i) ;
         while (j-j_start<total && j<heap_size){
           cout << harr[j] <<" " ;
		   j++;
         }
         cout << endl;
    }

}

// Constructor: Builds a heap from a given array a[] of given size
// this way one get a dynamics array
MinHeap::MinHeap(int cap)
{
	heap_size = 0;
	capacity = cap;
	harr = new int[cap];
    varr = new int[cap];
}

// Inserts a new key 'k'
void MinHeap::insertKey(int k, int v)
{
	if (heap_size == capacity)
	{
		cout << "\nOverflow: Could not insertKey\n";
		return;
	}

	// First insert the new key at the end
	heap_size++;
	int i = heap_size - 1;
	harr[i] = k;
    varr[i] = v;

	// Fix the min heap property if it is violated
	while (i != 0 && harr[parent(i)] > harr[i])
	{
	swap(&harr[i], &harr[parent(i)]);
    swap(&varr[i], &varr[parent(i)]);


	i = parent(i);
	}
}

// Decreases value of key at index 'i' to new_val. It is assumed that
// new_val is smaller than harr[i].
void MinHeap::decreaseKey(int i, int new_val)
{
	harr[i] = new_val;
	#ifdef DEBUG
	printheap();
	cout << parent(i) << " " << harr[i] << " "<< harr[parent(i)] << endl;
	#endif
	while (i != 0 && harr[parent(i)] > harr[i])
	{
	swap(&harr[i], &harr[parent(i)]); 
    swap(&varr[i], &varr[parent(i)]);
	
	
	i = parent(i);
	}
	#ifdef DEBUG
	printheap();
	#endif
}

// Method to remove minimum element (or root) from min heap
int MinHeap::extractMin()
{
	if (heap_size <= 0)
		return INT_MAX;
	if (heap_size == 1)
	{
		heap_size--;
		return harr[0];
	}

	// Store the minimum value, and remove it from heap
	
	int root = harr[0];
	harr[0] = harr[heap_size-1];
	// move the last one to the top
    varr[0] = varr[heap_size-1];
	

	heap_size--;
	#ifdef DEBUG
	printheap();
	#endif
	MinHeapify(0);

	return root;
}


// This function deletes key at index i. It first reduced value to minus
// infinite, then calls extractMin()
void MinHeap::deleteKey(int i)
{
	decreaseKey(i, INT_MIN);
	extractMin();
}

// A recursive method to heapify a subtree with the root at given index
// This method assumes that the subtrees are already heapified
// [CRH] Essentially heapify Down
void MinHeap::MinHeapify(int i)
{
	int l = left(i);
	int r = right(i);
	int smallest = i;
	if (l < heap_size && harr[l] < harr[i])
		smallest = l;
	if (r < heap_size && harr[r] < harr[smallest])
		smallest = r;
	if (smallest != i)
	{
		swap(&harr[i], &harr[smallest]);
        swap(&varr[i], &varr[smallest]);
		#ifdef DEBUG
	    printheap();
	    #endif
		MinHeapify(smallest);
	}
}

// [CRH] A utility function to check if a given vertex
// 'v' is in min heap or not

// A utility function to swap two elements
void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

