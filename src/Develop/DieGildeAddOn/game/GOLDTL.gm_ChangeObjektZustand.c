


extern char g_699aa4[];

unsigned char* __cdecl fcn_00502cd0(int list, int a, int b, int c, int d);
int __cdecl sprintf(char* buf, const char* fmt, ...);
#include "client_packet_builder.h"
void __cdecl fcn_004c4670(int a, int b, int c, char* v);
void __cdecl fcn_004c5360(void);

void __cdecl gm_ChangeObjektZustand(int id, int delta)
{
	char buf[0x80];
	char v;
	unsigned char* r;

	v = (char) delta;
	r = fcn_00502cd0(0, 2, 7, 1, id);
	if (r == 0) {
		sprintf(buf, g_699aa4, id);
		return;
	}
	if (r[0x12] + delta < 0) {
		v = 0;
	}
	fcn_004c4510((char*) r, id);
	fcn_004c4670(1, 1, 0x12, &v);
	fcn_004c5360();
}
