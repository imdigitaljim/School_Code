#pragma once
#define INT_MAX 2147483647

//globally declared for optimizing time (and reducing memory allocation calls)
char tempAry1[32], tempAry2[32];
static int inversion_count = 0;
int i = 0, j = 0;


/* bit helpers globals
we now have 1-32 instead of 0-31 because of the bit operations thus we need 33 elements to skip over 0 element
*/
char tree[33]; 

uint32_t sum = 0;
uint32_t temp = 0;

//binary indexed tree approach
void get_inversions() 
{
	memset(tree, 0, sizeof(tree));
	for (i = 31; i >= 0; --i)
	{
		sum = 0; //reset for each 
		temp = tempAry2[i]; //get relevant index value
		
		//traverse ancestors
		while (temp > 0) {			
			sum += tree[temp];
			//move tempIndex to parent node of BIT tree
			temp -= (temp & -temp);
		}
		
		//add to the inversions
		inversion_count += sum;
		
		//update the tree array
		temp = tempAry2[i] + 1; //will not work with 0
		while (temp <= 31) //traverse all ancestors
		{
			tree[temp] += 1; //added for summing later if needed
			temp += (temp & -temp); //update index to parent 
		}
	}
}

int calculate_node_distance(const char *x, const char *y)
{
	//sets array to use in order to get distances with respect to each other 
	for (i = 0; i < 32; i++)
	{
		tempAry1[(int)x[i]] = i;
	}
	for (i = 0; i < 32; i++)
	{
		tempAry2[i] = tempAry1[(int)y[i]]; 
	}
	inversion_count = 0; //reset inversions
	get_inversions(); //get inversionos
	return inversion_count;
}



