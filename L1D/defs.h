#include <stdio.h>

#define L1I 16*1024
#define L1D 16*1024
#define L2 256*1024
#define L3 8*1024*1024
#define L4 4*8192*8*1024

#define DEBUG 1 
#ifdef DEBUG
#define DEBUG_PRINT 1 
#else 
#define DEBUG_PRINT 0
#endif 
#define PRINT_DEBUG(fmt, ...) \
	do { if(DEBUG_PRINT) fprintf(stderr, fmt, \
										 __VA_ARGS__);} while (0)

#ifdef VERBOSE 
#define INFO_PRINT 1 
#else 
#define INFO_PRINT 0
#endif 

