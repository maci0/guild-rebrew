


#include <stdio.h>
#include <string.h>

int __cdecl fcn_0051e070(void);

void __cdecl fcn_00538500(char* out)
{
	char sep[2] = " ";
	char months[12][4] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
	char tok[3][0x10];
	char date[0x100];
	char* p;
	int i;

	strcpy(date, "Jan  9 2004");
	i = 0;
	p = strtok(date, sep);
	while (p != 0) {
		strcpy(tok[i++], p);
		p = strtok(0, sep);
	}
	for (i = 0; i < 12; i++) {
		if (strcmp(tok[0], months[i]) == 0) {
			break;
		}
	}
	if (fcn_0051e070() == 1) {
		sprintf(out, "Europa 1400 - Gold Edition - 2.06");
	} else {
		sprintf(out, "Die Gilde - Gold Edition - 2.06");
	}
}
