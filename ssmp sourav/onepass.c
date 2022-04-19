#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void main()
{
	FILE *f1, *f2, *f3, *f4;
	int lc, sa, l, o, len;
	char m1[20], la[20], op[20], otp[20], op1[10];
	f1 = fopen("onepassinput.txt", "r");
	f3 = fopen("symtab.txt", "w");
	fscanf(f1, "%s%s%s", la, m1, op1);
	if (strcmp(m1, "START") == 0)
	{
		sa = (int)strtol(op1, NULL, 16);
		lc = sa;
		printf("%x\t%s\t%s\t%x\n",sa, la, m1, sa);
	}
	else
	{
		lc = 0;
	}
	fscanf(f1, "%s%s", la, m1);
	while (!feof(f1))
	{
		fscanf(f1, "%s", op);
		printf("\n%x\t%s\t%s\t%s\n", lc, la, m1, op);
		if (strcmp(la, "_") != 0)
		{
			fprintf(f3, "%x\t%s\n", lc, la);
		}
		f2 = fopen("optab.txt", "r");
		fscanf(f2, "%s%d", otp, &o);
		while (!feof(f2))
		{
			if (strcmp(m1, otp) == 0)
			{
				lc = lc + 3;
				break;
			}
			fscanf(f2, "%s%d", otp, &o);
		}
		fclose(f2);
		if (strcmp(m1, "WORD") == 0)
		{
			lc = lc + 3;
		}
		else if (strcmp(m1, "RESW") == 0)
		{
			lc = lc + (3 * atoi(op));
		}
		else if (strcmp(m1, "BYTE") == 0)
		{
			if (op[0] == 'X')
			{
				lc = lc + 1;
			}
			else
			{
				len = strlen(op) - 2;
				lc = lc + len;
			}
		}
		else if (strcmp(m1, "RESB") == 0)
		{
			lc = lc + atoi(op);
		}
		fscanf(f1, "%s%s", la, m1);
	}
	if (strcmp(m1, "END") == 0)
	{
		printf("\nprogram length=%d\n", lc - sa);
	}
	fclose(f1);
	fclose(f3);
}