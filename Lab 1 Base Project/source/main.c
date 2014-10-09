// Group 17 - CRC16-CCITT implementation (Little endian)
// September 26th 2014
// Andrew Wong	260448904
// Claus Choi

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define poly 0x8408

//The CRCs generated will have a width of 16 bits
typedef uint16_t remainder;

remainder CRCGenerator(char test[], int length)
	
{
	remainder rem = 0;
//algorithm for division begins here	
	for (int bytes = 0; bytes < length; bytes++)
	{
//push next byte into remainder
		rem = rem ^ test[bytes];
//perform bitwise divison for each bit in the byte		
		for (int bits = 0; bits < 8; bits++)
		{
			if (rem & 0x0001)
			{
//XOR the remainder and divisor and store as new remainder (subtraction)
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

//Very similar to the CRCGenerator function with the exception of the comparison in the end of the new CRC generated XORed with the old CRC received
remainder CRCCheck(char test [], int length, remainder old_crc)
	
{
	remainder new_crc = CRCGenerator(test, length);
	
	remainder result = old_crc ^ new_crc;
	
	return (result);
}

extern remainder lab1code(char test[], int length);


int main()
{

	//char demo[] = "In Flanders fields the poppies blow, Between the crosses, row on row, That mark our place; and in the sky, The larks, still bravely singing, fly, Scarce heard amid the guns below. We are the Dead. Short days ago, We lived, felt dawn, saw sunset glow, Loved and were loved, and now we lie, In Flanders fields. Take up our quarrel with the foe, To you from failing hands we throw, The torch; be yours to hold it high. If ye break faith with us who die, We shall not sleep, though poppies grow, In Flanders fields.";
	char demo[] = "2014";
	remainder CRCAss = lab1code( demo, strlen(demo));
//Random CRC code
	remainder CRC_foobar = 18;

//Generates the CRC code for the poem
	remainder CRC_generated = CRCGenerator(demo,strlen(demo));

//Case 1: Ideal solution where the CRC code inputed into the checker matches exactly the CRC generated. Will return a remainder of 0.
	remainder CRC_checked_good= CRCCheck(demo,strlen(demo),CRC_generated);
//Case 2: Solution where CRC code inputed does not match the CRC generated for the poem. Will return a non-zero remainder.
	remainder CRC_checked_foobar= CRCCheck(demo,strlen(demo),CRC_foobar);
	//char test[] = "2014";
	
	return 0;
}





