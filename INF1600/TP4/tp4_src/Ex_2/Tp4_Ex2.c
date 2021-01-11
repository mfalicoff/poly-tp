
#include <stdio.h>

unsigned int change_endianness(unsigned int x)
{
	unsigned int y;
    
	asm volatile (                                  
        "bswap     %0 \n\t"                                                                                                                        
		: "=r" (y)
		: "r"(x)
	);
    
    
	return y;
}

int main()
{
	unsigned int data = 0xff1122ee;

	printf("Donnée en little-endian: %08x\n"
	       "Donnée en big-endian   : %08x\n"
	       "Donnée en little-endian: %08x\n",
	       data,
	       change_endianness(data),
           change_endianness(change_endianness(data))
           );

	return 0;
}
