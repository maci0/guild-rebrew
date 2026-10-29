#include <string.h>

extern int __cdecl fcn_0064d41a(char* buf, const char* fmt, ...);
extern int __cdecl fcn_00435500();
extern int __cdecl fcn_00434760();
extern int __cdecl fcn_00433ba0();
extern int __cdecl fcn_00413120();
extern int __cdecl fcn_00413190();
extern int __cdecl fcn_004050c0();
extern int __cdecl fcn_004032b0();
extern char __cdecl fcn_0045b990();
extern void __cdecl m_FreeTracked(void* ptr);
extern void* __cdecl m_alloc(unsigned int size, const char* tag);
extern int __cdecl fcn_00407e30();
extern int __cdecl fcn_00421350();
extern int __cdecl fcn_00407760();
extern int __cdecl fcn_0045b920();
extern int __cdecl fcn_00451840();

/* Rebuilds one object's render state from its definition record. Native
 * extent 1056 bytes. */
/* ADDRESS: GOLDTL 0x004094c0 */
unsigned int __cdecl fcn_004094c0(int a0, int a1)
{
	char buf[0x60];
	char small[4];
	int v14;
	int v15;
	unsigned int v16;
	unsigned int v17;
	int rec;
	int obj;
	int n;
	int r;
	void (__cdecl* fn)(int);

	rec = a0;
	obj = *(int*) (a0 + 0x14);
	if (*(int*) (obj + 0x7c) != 0) {
		fcn_0064d41a(buf, (char*) 0x67553c, obj);
		fcn_00435500(*(int*) (*(int*) (obj + 0x34) + 0x1ec) + 0xf4, buf);
		r = fcn_00433ba0(buf);
		fcn_00434760(r, 1);
		*(int*) (obj + 0x7c) = 0;
	}
	fcn_00413120(*(int*) (obj + 0x34));
	*(int*) (obj + 0x80) = 0;
	*(int*) (obj + 0x7c) = 0;
	*(int*) (obj + 0x70) = 0;
	*(float*) (obj + 0x1a4) = 1.0f;
	*(unsigned short*) (*(int*) (rec + 0x14) + 0x8c) &= 0xfff7;
	*(int*) (rec + 0xf4) = 0;
	*(int*) (rec + 0x104) = 0;
	*(int*) (rec + 0x154) = -1;
	memset((void*) (obj + 0x90), 0, 0x80);
	v16 = *(unsigned int*) (rec + 0x30);
	v17 = *(unsigned int*) (rec + 0x34);
	n = fcn_00413190(*(int*) (obj + 0x88));
	if (n != *(int*) (rec + 0x38)) {
		fcn_004050c0(rec);
		return 0;
	}
	if (*(unsigned char*) (rec + 0x160) & 8)
		*(int*) (rec + 0x110) = fcn_004032b0(rec + 0x114);
	r = fcn_0045b990(a1, *(int*) (*(int*) (rec + 0x14) + 0x34) + 0x4c,
	    &v15, &v14, small);
	if (r == 0) {
		if (*(char*) 0x6b5c28 != 0)
			*(unsigned char*) (*(int*) (rec + 0x14) + 0x8c) |= 8;
		if (*(int*) (rec + 0xf4) != 0) {
			m_FreeTracked((void*) *(int*) (rec + 0xf4));
			*(int*) (rec + 0xf4) = 0;
		}
		fcn_004050c0(rec);
		return 0;
	}
	if (v15 < 1) {
		v15 = 1;
	}
	else {
		n = *(int*) (a1 + 0x20) - 2;
		if (n < v15)
			v15 = n;
	}
	if (v14 < 1) {
		v14 = 1;
	}
	else {
		n = *(int*) (a1 + 0x20) - 2;
		if (n < v14)
			v14 = n;
	}
	if (*(unsigned char*) (obj + 4) & 4)
		*(unsigned int*) (rec + 0x160) &= 0xffffffef;
	if (*(unsigned int*) (rec + 0x160) & 0x10)
		fcn_00407e30(a1, *(int*) (obj + 0x34) + 0x4c, rec + 0x144, v16, v17,
		    &v17, &v16, 8, *(unsigned int*) (rec + 0x160));
	else
		fcn_00407e30(a1, *(int*) (obj + 0x34) + 0x4c,
		    *(int*) (obj + 0x34) + 0x4c, v16, v17,
		    &v17, &v16, 8, *(unsigned int*) (rec + 0x160));
	*(unsigned int*) 0x14d0c28 = 0x14cfc20;
	*(unsigned int*) 0x14d0c24 = 0x200;
	r = fcn_00421350((void*) 0x14d0c20, a1, v15, v14, v17, v16,
	    *(char*) (obj + 0x240));
	if (r == -1) {
		*(char*) (*(int*) (rec + 0x14) + 0x110) = 0;
		if (*(char*) 0x6b5c28 != 0)
			*(unsigned char*) (*(int*) (rec + 0x14) + 0x8c) |= 8;
		if (*(int*) (rec + 0xf4) != 0) {
			m_FreeTracked((void*) *(int*) (rec + 0xf4));
			*(int*) (rec + 0xf4) = 0;
		}
		fn = (void (__cdecl*) (int)) *(int*) (rec + 0x15c);
		if (fn != 0)
			fn(rec);
		fcn_004050c0(rec);
		return 0;
	}
	*(int*) (rec + 0xf4) = (int) m_alloc(*(unsigned int*) 0x14d0c20 * 2,
	    (char*) 0x675ad8);
	*(int*) (rec + 0xf0) = fcn_00407760(obj, (void*) 0x14d0c20,
	    (void*) *(int*) (rec + 0xf4), a1);
	*(int*) (rec + 0xf8) = 0;
	*(int*) (rec + 0xfc) = -1;
	fcn_0045b920(a1, *(unsigned char*) *(int*) (rec + 0xf4),
	    ((unsigned char*) *(int*) (rec + 0xf4))[1], (float*) (rec + 0x124));
	*(float*) (rec + 0x124) = *(float*) 0x6b5c38 + *(float*) (rec + 0x124);
	*(float*) (rec + 0x128) = *(float*) 0x6b5c3c + *(float*) (rec + 0x128);
	*(float*) (rec + 0x12c) = *(float*) 0x6b5c40 + *(float*) (rec + 0x12c);
	if (*(unsigned char*) (rec + 0x160) & 8) {
		obj = *(int*) (rec + 0x110);
		*(int*) (rec + 0x134) = *(int*) (obj + 0x38);
		*(int*) (rec + 0x138) = *(int*) (obj + 0x3c);
		*(int*) (rec + 0x13c) = *(int*) (obj + 0x40);
	}
	else {
		fcn_0045b920(a1, v17, v16, (float*) (rec + 0x134));
		*(float*) (rec + 0x124) = *(float*) 0x6b5c38 + *(float*) (rec + 0x124);
		*(float*) (rec + 0x128) = *(float*) 0x6b5c3c + *(float*) (rec + 0x128);
		*(float*) (rec + 0x12c) = *(float*) 0x6b5c40 + *(float*) (rec + 0x12c);
		if (*(unsigned char*) (rec + 0x160) & 0x10) {
			if (fcn_00451840((void*) (rec + 0x134), (void*) (rec + 0x144),
				(int) 0x41f00000) == 0) {
				*(int*) (rec + 0x144) = *(int*) (rec + 0x134);
				*(int*) (rec + 0x148) = *(int*) (rec + 0x138);
				*(int*) (rec + 0x14c) = *(int*) (rec + 0x13c);
			}
		}
	}
	*(int*) (rec + 0x104) = 0;
	return 1;
}
