#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define poly 0x8408

typedef uint16_t remainder;

remainder CRCCheck(unsigned char test[], int length)
{
	remainder rem = 0;
	
	for (int bytes = 0; bytes < length; bytes++)
	{
		rem = rem ^ test[bytes];
		
		for (int bits = 0; bits < 7; bits++)
		{
			if (rem & 0x0001)
			{
				rem = (rem >> 1) ^ poly;
			}
			else
			{
				rem = (rem >> 1);
			}
		}
	}
	
return (rem);	
		
	
	
}	
int main()
{
	unsigned char demo[] = "2014";
	int strLength = strlen(demo);
	remainder CRC_generated = CRCCheck(demo, strLength);

	return 0;
}




