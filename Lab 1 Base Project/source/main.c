#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define poly 0x8408

typedef uint16_t remainder;

remainder CRCGenerator(char test[], int length)
	
{
	remainder rem = 0;
	
	for (int bytes = 0; bytes < length; bytes++)
	{
		rem = rem ^ test[bytes];
		
		for (int bits = 0; bits < 8; bits++)
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

remainder CRCCheck(char test [], remainder old_crc)
	
{
	remainder new_crc = CRCGenerator(test, strlen(test));
	
	remainder result = old_crc ^ new_crc;
	
	return (result);
}

int main()
{
	char demo[] = "2014";
	
	remainder CRC_foobar = 18;

	remainder CRC_generated = CRCGenerator(demo,strlen(demo));

	remainder CRC_checked_good= CRCCheck(demo,CRC_generated);
	
	remainder CRC_checked_foobar= CRCCheck(demo,CRC_foobar);
	
	return 0;
}









