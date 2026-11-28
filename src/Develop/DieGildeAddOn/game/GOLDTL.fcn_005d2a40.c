#include <string.h>

char* __cdecl gm_LookupEntityRecordById(int);
float __cdecl gm_GetEntityAge(int);
int __cdecl gm_CalcPersonWealth(unsigned short);
float __cdecl gm_CalcEntityFavor(unsigned int, unsigned int, unsigned int);
int __cdecl gm_CheckPrivilege(int, char*, int);

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/* fcn_00505e30: float of short [0x7f4caa + (a&0xffff)*540]. */
/* ADDRESS: GOLDTL 0x00508e80 */
float __cdecl gm_GetEntityAge(int a)
{
#ifdef REBREW_GOLD
	return (float) (unsigned short) *(unsigned short*) (0x770b8a + (a & 0xffff) * 540);
#else
	return (float) (unsigned short) *(unsigned short*) (0x7f4caa + (a & 0xffff) * 540);
#endif
}

#ifndef REBREW_GOLD
/* ADDRESS: GOLDTL 0x005d2a40 */
int __cdecl gm_CalcWerbungSteps(int sourceId, int targetId)
{
	char* p;
	char* q;
	char* t;
	int buf[0x88];
	float f8;
	float fc;
	float f10;
	float v;
	int i;
	int n;

	f8 = 0.0f;
	fc = 0.0f;
	f10 = 0.0f;
	memset(buf, 0, sizeof buf);
	buf[0] = 1;
	p = gm_LookupEntityRecordById(sourceId);
	q = gm_LookupEntityRecordById(targetId);
	if (p == 0 || q == 0) {
		return 0;
	}
	t = gm_LookupEntityRecordById(*(int*) (q + 0x60));
	if (t != 0) {
		f10 = (float) (gm_CalcPersonWealth(*(unsigned short*) t) / 2);
	}
	t = gm_LookupEntityRecordById(*(int*) (q + 0x64));
	if (t != 0) {
		f8 = (float) (gm_CalcPersonWealth(*(unsigned short*) t) / 2);
	}
	if ((float) gm_CalcPersonWealth(*(unsigned short*) q) > 0.0f) {
		fc = (float) gm_CalcPersonWealth(*(unsigned short*) q);
	}
	else {
		fc = 0.0f;
	}
	fc = MAX(fc, MAX(f10, f8));
	f8 = (float) gm_CalcPersonWealth(*(unsigned short*) p);
	if (f8 > fc) {
		f8 = 1.0f;
	}
	else {
		f8 = (fc - f8) / fc * 5.0f + 1.0f;
	}
	f10 = (100.0f - gm_CalcEntityFavor(*(unsigned short*) p, *(unsigned short*) q, 1)) * 0.05f + 1.0f;
	f8 = (1.0f - MIN(30.0f, MAX(gm_GetEntityAge(*(unsigned short*) q), 15.0f)) * (1.0f / 15.0f)) * 4.0f
		+ 1.0f + f10 + f8;
	for (i = 0; i < 5; i++) {
		f8 = f8 + (float) (unsigned char) q[0x80 + i] * (1.0f / 252.0f);
	}
	if (gm_CheckPrivilege(0x10, p, (int) buf) & 2) {
		f8 = f8 * 0.5f;
	}
	return (int) MIN(15.0f, MAX(f8, 2.0f));
}

#endif
