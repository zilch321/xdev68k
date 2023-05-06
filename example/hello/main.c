#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int argc, char** argv)
{
	int i, p;
	int iPage;
	FILE *fp;
	unsigned char buf[32];
	char sName[512];

	iPage = 0;
	printf("dump.x Version 0.50\n\n");

	for (i = 1; i < argc; i++)
	{
		if (argv[i][0] != '-')
		{
			strcpy(sName, argv[i]);
		}
	}
	
	do
	{
		printf("Dump File: [ %s ]\n", sName);
		if (sName[0] == 0) break;
		fp = fopen(sName, "rb");
		if (fp == 0)
		{
			printf("Cannot open the file...\n");
			break;
		}
		/*      00000000: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00   ................ */
		printf("ADDRESS   +0 +1 +2 +3 +4 +5 +6 +7 +8 +9 +A +B +C +D +E +F   0123456789ABCDEF\n");
		while (1)
		{		
			p = fread(buf, 1, 16, fp);
			if (p == 0) break;
			printf("%08X: ",iPage);
			for(i = 0; i < p ; i++)
			{
				printf("%02X ", buf[i]);
			}
			for(; i < 16 ; i++)
			{
				printf("   ");
			}

			printf("  ");

			for(i = 0; i < p ; i++)
			{
				if ((buf[i] >= 0x20) && (buf[i] <= 'z')) printf("%c", buf[i]);
				else printf(".");
			}
			printf("\n");
			iPage += 16;
		
		}
		fclose(fp);
	} while (0);

	return;
}