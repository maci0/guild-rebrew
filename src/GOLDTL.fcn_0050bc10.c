#include <stdio.h>
#include <string.h>

int __cdecl fcn_0050b710(int, unsigned char);
char* __cdecl itoa(int, char*, int);

/* Formats a scaled game value into `dst`: values below 1000 print directly,
 * larger ones with '.' thousand separators. Every form carries the trailing
 * %c marker that the reference passes as the literal 0x11. */

/* ADDRESS: GOLDTL 0x0050bc10 */
void __cdecl fcn_0050bc10(int value, unsigned char mode, char* dst)
{
	char digits[0x40];
	char text[0x80];
	char* c;
	int negative;
	int scaled;
	int n;
	int p;
	int i;
	int written;

	negative = value < 0;
	scaled = fcn_0050b710(negative ? -value : value, mode);
	if (scaled == 0) {
		sprintf(dst, "0%c", 0x11);
		return;
	}
	if (scaled < 1000) {
		if (negative) {
			sprintf(dst, "-%i%c", scaled, 0x11);
		} else {
			sprintf(dst, "%i%c", scaled, 0x11);
		}
		return;
	}

	itoa(scaled, digits, 10);
	n = strlen(digits);
	p = (int) ((double) (n - 1) * *(float*) 0x662a68 + (double) n);
	c = text + p - 1;
	written = 0;
	for (i = n - 1; i >= 0; i--) {
		*c = digits[i];
		c--;
		written++;
		if (i != 0 && written % 3 == 0) {
			*c = '.';
			c--;
		}
	}
	text[p] = 0;
	if (negative) {
		sprintf(dst, "-%s%c", text, 0x11);
	} else {
		sprintf(dst, "%s%c", text, 0x11);
	}
}
