#include <string.h>

extern unsigned char g_773d75;
extern float g_66433c;
extern float g_664160;
extern float g_664154;
extern int g_77261c;

int __cdecl fcn_0050d320(char*, char);
int __cdecl gm_WalkEntityChain(unsigned short);
int __cdecl fcn_004fa5b0(int, char*, int*);
int __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_00495400(int, unsigned short, int, void*, void*);
int __cdecl fcn_004f4830(int, void*);
int __cdecl gm_RandomMod(int);
float __cdecl gm_RandomFloat01(void);
int __cdecl fcn_004a5340(char*, int, int*, int, float, unsigned short*);
float __cdecl fcn_00507e70(char*, char*, int);
int __cdecl fcn_0055c0f0(char*, char*);
int __cdecl fcn_0055c0a0(char*, char*);

typedef struct {
	char type;
	char pad[3];
	int a;
	int b;
	int pad2;
	int pad3;
	float value;
} Msg499640;

/* ADDRESS: GOLDTL 0x00499640 */
int __cdecl fcn_00499640(int unused0, char* e, int a2, Msg499640* out1, Msg499640* out2)
{
	int vb;
	int va;
	int idx;
	Msg499640 msg0;
	Msg499640 msg1;
	int mask;
	char rec[0x24];
	int buf[0x88];
	char* entry;
	int r;
	float v;

	va = fcn_0050d320(e, g_773d75);
	if (a2 != 0) {
		goto fail;
	}
	memset(buf, 0, sizeof(buf));
	buf[0] = 1;
	vb = (int) ((float) gm_WalkEntityChain(*(unsigned short*) e) * g_66433c);
	if ((fcn_004fa5b0(0x1b, e, buf) & 2) != 0) {
		vb /= 2;
	}
	if ((float) va * g_664160 < (float) vb) {
		goto fail;
	}
	if (*(int*) (e + 0x170) == 0) {
		if (e[2] == 3) {
			goto check_flag;
		}
		msg0.type = 5;
		msg0.a = 4;
		msg0.b = 1;
		msg1.type = 0;
		msg1.a = 0;
		msg1.b = 0;
	} else {
		if (e[2] == 3) {
			goto check_flag;
		}
		if (fcn_00502cd0(*(int*) (*(char**) (e + 0x170) + 0x5d), 2, 6, 0,
				0x14) != 0) {
			goto main;
		}
		msg0.type = 2;
		msg0.a = 0x14;
		msg0.b = 1;
		msg0.value = 0.22f;
		msg1.type = 4;
		msg1.a = *(int*) (*(char**) (e + 0x170) + 1);
		msg1.b = 1;
	}
send:
	r = fcn_00495400(0x18, *(unsigned short*) e, 1, &msg0, &msg1);
	if (r == 0) {
		goto fail;
	}
	goto copy_out;
check_flag:
	if ((*(unsigned char*) (e + 0x1e8) & 2) == 0) {
fail:
		return 0;
	}
main:
	fcn_004f4830(0x15, rec);
	if (*(int*) (rec + 0x18) != 0) {
		if (gm_RandomMod(3) == 0 && g_77261c == 0) {
			goto fail;
		}
	}
	if (*(char*) out1 != 0) {
		goto fail;
	}
	mask = 0xf00500;
	if (fcn_004a5340(e, 1, &mask, 0,
			(float) (gm_RandomMod(0x20) & 0xffff) + g_664154,
			(unsigned short*) &idx) == 0) {
		goto fail;
	}
	entry = (char*) 0x7f4ca0 + (idx & 0xffff) * 0x21c;
	if (*(int*) (entry + 0x194) < 2) {
		goto fail;
	}
	v = fcn_00507e70(e, entry, 3);
	if (gm_RandomFloat01() + v < 1.0f) {
		msg0.type = 0x0e;
		msg0.a = 3;
		msg0.b = 1;
		msg0.value = 0.0f;
		msg1.type = 0;
		msg1.a = 0;
		msg1.b = 0;
		r = fcn_00495400(0x18, *(unsigned short*) e, 0, &msg0, &msg1);
		if (r == 0) {
			goto fail;
		}
		goto copy_out;
	}
	if (fcn_0055c0f0(e, entry) == 0) {
		goto fail;
	}
	if (fcn_0055c0a0(e, entry) == 0) {
		goto fail;
	}
	out1->type = 7;
	out1->a = *(int*) (entry + 4);
	out1->b = 1;
	out1->pad3 = vb;
	out1->value = (float) (*(int*) (rec + 0x18) * 2 + 1);
	return 0x18;
copy_out:
	*out1 = msg0;
	*out2 = msg1;
	return r;
}
