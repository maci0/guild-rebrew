#include <string.h>

extern unsigned char g_773d75;
extern double g_6640e8;

int __cdecl gm_LookupEntityRecordById(int id);
int __cdecl fcn_0042e410(int a);
int __cdecl fcn_0050dac0(short);
void __cdecl io_FormatTextBuffer(char* buf, int fmt, ...);
void __cdecl fcn_00545d40(int a, int b, char* buf, int c, int d, int e);
void __cdecl fcn_004c51a0(int a, int b, unsigned char c, int d);

/* Entity command: sends the timed command text built from the entity record and
 * the current frame timing back to the sender slot. Native function spans
 * 0x004bb210..0x004bb312 (259 bytes); rows 0x004bb210 (47) and 0x004bb23f (212)
 * are one function split at the head's branch target. */
/* ADDRESS: GOLDTL 0x004bb210 */
int __cdecl fcn_004bb210(int* a)
{
	int v;
	double d;
	char buf[0x800];
	int* e;

	e = (int*) gm_LookupEntityRecordById(a[0]);
	if (e == 0) {
		return 1;
	}
	if ((unsigned short) fcn_0042e410(0x100) > (unsigned short) *((unsigned char*) e + 0x82)) {
		return 0x400;
	}
	v = fcn_0042e410(3) & 0xffff;
	d = (double) v + *(double*) 0x6629c8;
	v = (int) (((double) fcn_0050dac0(*(short*) e) * d) * g_6640e8);
	io_FormatTextBuffer(buf, *(unsigned short*) ((char*) a + 4) + 0x12e7, v);
	fcn_00545d40(e[1], e[1], buf, 0x100 < strlen(buf), 0x603, 0);
	fcn_004c51a0(a[0], -1, g_773d75, v);
	return 0;
}
