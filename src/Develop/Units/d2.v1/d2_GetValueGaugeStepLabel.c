#include <string.h>

extern char* d2_Controls;
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x00468c30 */
/* ADDRESS: GOLDDE 0x0045c5b0 */
void __cdecl d2_GetValueGaugeStepLabel(int slot, int n, char* out)
{
	char buf[0x400];
	char* p;
	char* q;
	int i;

	i = 0;
	strcpy(buf, (char*) &((D2_CONTROL_TL*) d2_Controls)[slot] + 0xe8);
	q = buf;
	p = strchr(buf + 1, '|');
	for (; i < n; i++) {
		if (p == 0) {
			return;
		}
		q = p;
		p = strchr(p + 1, '|');
	}
	if (p != 0) {
		*p = 0;
		strcpy(out, q);
	}
}
