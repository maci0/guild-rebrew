// FUNCTION: GOLDTL 0x0050ce20
// SIZE: 304

#include <string.h>

// SIZE 0xb8
typedef struct {
	int max;
	int n;
	int caps[16];
	unsigned short ids[16];
	int vals[16];
	char pada8[0xb4 - 0xa8];
	char* store;
} Stock;

extern char* g_99ec10;

unsigned short* __cdecl fcn_00502cd0(int obj, int mode, ...);
int __cdecl gm_GetMsgField(char* pkt, unsigned short* q);
int __cdecl fcn_0050dfd0(char* pkt, int item_id);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);

int __cdecl fcn_0050ce20(char* o, Stock* out, int producers)
{
	char* b;
	unsigned short* e;
	char* rec;

	memset(out, 0, sizeof(Stock));
	if (fcn_00502cd0(*(int*) (o + 0x5d), 1, 0, 0xfd) == 0) {
		return 0;
	}
	b = (char*) fcn_00502cd0(*(int*) (o + 0x5d), 2, 6, 0, 0x2a);
	if (b == 0) {
		b = (char*) fcn_00502cd0(*(int*) (o + 0x5d), 2, 6, 0, 0x116);
		if (b == 0) {
			return 0;
		}
	}
	if (producers) {
		if (*(unsigned short*) b == 0x116) {
			return 0;
		}
		out->max = (unsigned char) b[0x1c];
	} else {
		out->max = (unsigned char) b[0x1d];
		if (*(unsigned short*) b == 0x116) {
			out->max = out->max > (unsigned char) b[0x1c] ? out->max : (unsigned char) b[0x1c];
		}
	}
	for (e = fcn_00502cd0(*(int*) (b + 0x14), 1, 5); e != 0; e = gm_NextEntityQueryMatch()) {
		rec = g_99ec10 + *e * 0x41;
		if ((*rec == 0x17 && producers) || (*rec != 0x17 && !producers)) {
			out->vals[out->n] = gm_GetMsgField(b, e);
		out->caps[out->n] = fcn_0050dfd0(b, *e);
		out->ids[out->n] = *e;
		out->n++;
		}
	}
	out->store = b;
	return 1;
}
