#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern float g_662a68;

int __cdecl fcn_0050b710(int, unsigned char);
char* __cdecl itoa(int, char*, int);

/* ADDRESS: GOLDTL 0x0050bc10 */
void __cdecl fcn_0050bc10(int value, unsigned char mode, char* dst)
{
	char digits[0x40];
	char text[0x80];
	char* c;
	int scaled;
	int n;
	int p;
	int i;
	int written;

	scaled = fcn_0050b710(abs(value), mode);
	if (value < 0) {
		if (scaled != 0) {
			if (scaled >= 1000) {



			
			itoa(scaled, digits, 10); written = -1;
			n = strlen(digits);
			p = (int) ((double) (strlen(digits) - 1) * g_662a68
				+ (int) strlen(digits));
			c = text + p;
			
			for (i = strlen(digits); i >= 0; i--) {
				*c = digits[i];
				c--;
				if (i != 0 && written > 0 && (written + 1) % 3 == 0) {
					*c = '.';
					c--;
				}
				written++;
			}
			text[p] = 0;
			sprintf(dst, "-%s%c", text, 0x11);
			return; }
			sprintf(dst, "-%i%c", scaled, 0x11); return; }
	} else if (scaled >= 1000) {




	
		itoa(scaled, digits, 10); written = -1;
		n = strlen(digits);
		p = (int) ((double) (strlen(digits) - 1) * g_662a68
			+ (int) strlen(digits));
		c = text + p;
		
		for (i = strlen(digits); i >= 0; i--) {
			*c = digits[i];
			c--;
			if (i != 0 && written > 0 && (written + 1) % 3 == 0) {
				*c = '.';
				c--;
			}
			written++;
		}
		text[p] = 0;
		sprintf(dst, "%s%c", text, 0x11);
		return;
	} else if (scaled != 0) { sprintf(dst, "%i%c", scaled, 0x11); return; }
	sprintf(dst, "0%c", 0x11);
}
