// FUNCTION: GOLD 0x0050ca50
// FUNCTION: GOLDTL 0x0050fef0

extern char g_699aa4[];

unsigned char* __cdecl fcn_00502cd0(int list, int a, int b, int c, int d);
int __cdecl sprintf(char* buf, const char* fmt, ...);
void __cdecl fcn_004c4510(unsigned char* p, int id);
void __cdecl fcn_004c4670(int a, int b, int c, char* v);
void __cdecl fcn_004c5360(void);

void __cdecl fcn_0050fef0(int id, int delta)
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
	fcn_004c4510(r, id);
	fcn_004c4670(1, 1, 0x12, &v);
	fcn_004c5360();
}
