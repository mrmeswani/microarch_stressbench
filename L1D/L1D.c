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
#include <unistd.h>
#include "defs.h"

#define LineSize 64 // cache linesize
#define BUFFER_SIZE L1D*2 //set to much greater than L1D size  
#define PAD_SIZE 0
#define ITERS 100000 

int  main(int argc, char **argv)
{


	int i,j,stride, padsize, linesize, elemXline;
	uintptr_t *arr,*elem=NULL;
	int arrsize, buffer_size, iters;
	int opt;
	static char usage[]="usage: %s [-s buffer_size] [-l cacheline_size] [-n num_iterations]\n";
	buffer_size=BUFFER_SIZE; // set it to greater than size of L1D cache 
	padsize=PAD_SIZE; // experimental value
	iters=ITERS;
    linesize=LineSize;

   	// over ride defaults 
	while ((opt = getopt(argc, argv, "n:s:l:z:")) != -1) {
		switch(opt) {
			case 's':
				buffer_size = strtol(optarg, (char **)NULL, 10);
				break;
			case 'n':
				iters = strtol(optarg, (char **)NULL, 10);
				break;
			case 'l':
				linesize = strtol(optarg, (char **)NULL, 10);
				break;
			case '?':
				fprintf(stderr, usage, argv[0]);
				exit(1);
			default:
				fprintf(stderr, usage, argv[0]);
				exit(1);
		}
	}

	PRINT_DEBUG("buffer size is %d\n",buffer_size);

	elemXline = linesize/sizeof(uintptr_t);	
	arrsize=((buffer_size) + padsize)/sizeof(uintptr_t);

	arr =(uint64_t *)  malloc(arrsize*sizeof(uintptr_t)); // create the array of integers
	if(arr==NULL)
	{
		printf("could not allocate memory \n");
		exit(1);
	}



	/*** first elem of each linr stores the address of the first elemet of 3rd cache line ***/
	stride=elemXline*3;
	for(i=0;i<(arrsize-stride);i+=stride)
	{
		arr[i] = (uintptr_t )&arr[i+stride];
	}		
	arr[arrsize-stride]=(uintptr_t ) NULL; //if last cache line, then there is no more pointer to store
   		
	for(j=0;j<iters;j++)
	{
		elem=(uintptr_t *)arr[0]; //initialize to point to first elem of array
		while(elem!=NULL)// continue while not last line 
		{
			elem=(uintptr_t *)*elem; // load address of first elem of next line
		}
	}	


	PRINT_INFO("Arr size is %d, stride is %d, num iterations %d \n",arrsize, stride, j);
	printf("\nExpected # of L1D misses = %d\n",(arrsize/stride)*j);

	free(arr);
	free(elem);
	
	return 0;
}
