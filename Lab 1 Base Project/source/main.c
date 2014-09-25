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

remainder CRCCheck(char test [], int length, remainder old_crc)
	
{
	remainder new_crc = CRCGenerator(test, length);
	
	remainder result = old_crc ^ new_crc;
	
	return (result);
}

int main()
{
	char demo[] = "In Flanders fields the poppies blow, Between the crosses, row on row, That mark our place; and in the sky, The larks, still bravely singing, fly, Scarce heard amid the guns below. We are the Dead. Short days ago, We lived, felt dawn, saw sunset glow, Loved and were loved, and now we lie, In Flanders fields. Take up our quarrel with the foe, To you from failing hands we throw, The torch; be yours to hold it high. If ye break faith with us who die, We shall not sleep, though poppies grow, In Flanders fields.";
	//char demo[] = "2";
	remainder CRC_foobar = 18;

	remainder CRC_generated = CRCGenerator(demo,strlen(demo));

	remainder CRC_checked_good= CRCCheck(demo,strlen(demo),CRC_generated);
	
	remainder CRC_checked_foobar= CRCCheck(demo,strlen(demo),CRC_foobar);
	
	return 0;
}










