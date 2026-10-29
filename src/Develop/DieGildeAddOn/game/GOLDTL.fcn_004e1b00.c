#include <stdio.h>
#include <string.h>

char* __cdecl fcn_00508e40(int);
int __cdecl fcn_004e6cb0(int);
void __cdecl fcn_004e4730(char*);
void __cdecl fcn_004e4b60(char*);
void __cdecl fcn_004e4e90(char*);
void __cdecl fcn_004e4c40(int);
int __cdecl fcn_004fda30(int);
int __cdecl fcn_004fd9d0(int);
int __cdecl fcn_004e44b0(char*, char*);
void __cdecl fcn_004e44f0(int);
int __cdecl gm_RandomMod(int, ...);
float __cdecl fcn_004ff210(unsigned short, int);
void __cdecl fcn_004e4de0(int);
void __cdecl fcn_004e48b0(void);
void __cdecl fcn_004e4c60(void);
void __cdecl fcn_004e4c00(void);
void __cdecl fcn_004e4910(void);
void __cdecl fcn_004e3640(void);
int __cdecl fcn_00445f50(int, float, float, int);
void __cdecl fcn_004463f0(int, int, float);

/* ADDRESS: GOLDTL 0x004e1b00 */
void __cdecl fcn_004e1b00(int a0)
{
	volatile int mode;
	unsigned short* p;
	int ranges[5];
	char buf[256];
	unsigned short* q;
	unsigned short* r;
	unsigned short* s;
	char* scene;
	int id;
	int len;

	mode = fcn_004e6cb0(3);
	ranges[0] = 14000;
	ranges[1] = 12000;
	ranges[2] = 12000;
	ranges[3] = 15000;
	ranges[4] = 10000;
	p = (unsigned short*) fcn_00508e40(*(int*) (a0 + 0x34));
	if (p == 0) {
		return;
	}
	q = (unsigned short*) fcn_00508e40(*(int*) (a0 + 0x38));
	r = (unsigned short*) fcn_00508e40(*(int*) (a0 + 0x3c));
	s = (unsigned short*) fcn_00508e40(*(int*) (a0 + 0x40));
	*(int*) 0x68bfb8 = 0x702c6;
	*(int*) 0x7725c8 = 1;
	fcn_004e4730((char*) 0x68cfb0);
	fcn_00445f50(0, 0, 1.0f, 1);
	fcn_004463f0(0, 0, 0);
	if (mode == 1) {
		scene = (char*) (fcn_004e6cb0(3) * 0x4c + 0x6a2818);
	} else if (mode == 2) {
		scene = (char*) (fcn_004e6cb0(3) * 0x4c + 0x6a2730);
	} else {
		scene = (char*) (fcn_004e6cb0(4) * 0x4c + 0x6a2600);
	}
	fcn_004e4b60(scene);
	fcn_004e4e90((char*) 0x68cb08);
	if (mode == 1) {
		fcn_004e4c40(500);
	}
	if (q != 0) {
		id = fcn_004fda30(*q);
	} else {
		id = fcn_004fd9d0(gm_RandomMod(2, (gm_RandomMod(0x5e) & 0xffff) + 1) & 0xffff);
	}
	sprintf(buf + 1, (char*) 0x68cad8, id + 4);
	len = strlen(buf + 1);
	sprintf(buf + 1 + len, (char*) 0x68cad8, fcn_004fda30(*p) + 4);
	len = strlen(buf + 1);
	if (r != 0) {
		id = fcn_004fda30(*r);
	} else {
		id = fcn_004fd9d0(gm_RandomMod(2, (gm_RandomMod(0x5e) & 0xffff) + 1) & 0xffff);
	}
	sprintf(buf + 1 + len, (char*) 0x68cad8, id + 4);
	len = strlen(buf + 1);
	if (s != 0) {
		id = fcn_004fda30(*s);
	} else {
		id = fcn_004fd9d0(gm_RandomMod(2, (gm_RandomMod(0x5e) & 0xffff) + 1) & 0xffff);
	}
	sprintf(buf + 1 + len, (char*) 0x679060, id + 4);
	fcn_004e44b0((char*) 0x68cf80, buf + 1);
	fcn_004e44f0(fcn_004e44b0((char*) 0x68cf54, (char*) 0x6b5c60));
	if (*(int*) (a0 + 0xc) == *(int*) (*(unsigned short*) 0x774970 * 0x21c + 0x7f4ca4)) {
		fcn_004ff210(*p, (int) -(*(float*) ((char*) p + 0x1c) + *(float*) 0x662a98));
	}
	switch (*(char*) (a0 + 0x7c)) {
	case 0:
		scene = (char*) 0x68cf28;
		break;
	case 1:
	case 2:
		scene = (char*) 0x68cef8;
		break;
	case 3:
		scene = (char*) 0x68cec8;
		break;
	case 4:
		scene = (char*) 0x68ce98;
		break;
	default:
		goto done;
	}
	fcn_004e44b0(scene, (char*) 0x6b5c60);
done:
	fcn_004e4de0(ranges[*(char*) (a0 + 0x7c)]);
	fcn_004e48b0();
	fcn_004e44f0(fcn_004e44b0((char*) 0x68ce6c, (char*) 0x6b5c60));
	if (mode != 0) {
		fcn_004e4c60();
	}
	fcn_004e4c00();
	*(int*) 0x772f54 = 0;
	fcn_004e4910();
	*(int*) 0x7725c8 = 0;
	fcn_004e3640();
}
