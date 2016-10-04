/**** Compilation instructions 
	Compile the source code to object file with -O3 optimization
	No modifications are required for this code

*	Basic algorithm is to allocate an array the size much  larger then # of pages in L1 and L2 TLB can store
*	Think of this array as a multiple of pages and in our case we use 3000 page array 
*	Initialize the first element of every cache line to store the address of the first 
*	element of the next successive page, the last line of the array will store NULL.
*	In a loop implement the concept of pointer chasing by first initializing the pointer
*	to the first elem of the first line, the pointer then loads the address of the first 
*	element of the second page and so on, this will generate hits misses in the TLB
* 	as a side effect it also misses L1 and L2 due to the large stride, all get hits in L3.
*/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <inttypes.h>

int  main()
{


	int i,j,stride, elemXpage, padsize, pagesize;
	uintptr_t *arr,*elem=NULL;
	int arrsize, num_of_pages;
	num_of_pages=3000; // set it to greater than number of L1 and L2 TLB entries 
	pagesize=4096; // 4k size 
	padsize=0; // experimental value 
	
	arrsize=((pagesize*num_of_pages) + padsize)/sizeof(uintptr_t);

	arr =(uint64_t *)  malloc(arrsize*sizeof(uintptr_t)); // create the array of integers
	if(arr==NULL)
	{
		printf("could not allocate memory \n");
		exit(1);
	}

	elemXpage=pagesize/sizeof(void *); // num of elems in one page


	/***** first elem of each page stores address of first element of first elem of a successive page **/	
	stride=elemXpage;
	for(i=0;i<(arrsize-stride);i+=stride)
	{
		arr[i] = (uintptr_t )&arr[i+stride];
	}		
	arr[arrsize-stride]=(uintptr_t ) NULL; //if last page, then there is no more pointer to store
   		
	//printf("%p \n",(uintptr_t)(arr+0+stride));	
	//printf("%p\n",(uintptr_t)arr[0]);
	//for(j=0;j<400000;j++)
	for(j=0;j<40000;j++)
	{
		elem=(uintptr_t *)arr[0]; //initialize to point to first elem of array
		while(elem!=NULL)// continue while not last line 
		{
			elem=(uintptr_t *)*elem; // load address of first elem of next line
		}
	}	

	printf("\n\n # of iters = %d\n",(arrsize/stride)*j);

	free(arr);
	free(elem);
	
	return 0;
}
