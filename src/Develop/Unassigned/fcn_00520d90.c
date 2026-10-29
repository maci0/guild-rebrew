extern int __cdecl sub_430910(void*, int, int, void*);

#pragma pack(1)
typedef struct {
	unsigned char kind;
	char pad1[3];
	int f04;
	unsigned short f08;
	char pad0a[2];
	int f0c;
	int f10;
	char f14[0x30];
	char f44[0xe];
	char f52[0xe];
	char f60[0xe];
	char pad6e[2];
	int f70;
	unsigned char f78;
	char pad79[3];
	void* blob;
	int blob_len;
	char pad84[8];
	int f8c[8];
	char f0ac[0xa0];
} Unit520d90;

typedef struct {
	int id;
	unsigned char state;
	char pad5[3];
	int has_amount;
	int owner;
	int amount;
	char pos[0xe];
	char name[0x82];
} Deal520d90;

typedef struct {
	unsigned char b0;
	char pad[3];
	int f4;
	int f8;
	int fc;
	char name[0x40];
} ApEvent520d90;
#pragma pack()

extern Unit520d90 g_77e980[1024];
extern Deal520d90 g_7d2020[256];
extern ApEvent520d90 g_7dcae0[256];

/* ADDRESS: GOLDTL 0x00520d90 */
int __cdecl fcn_00520d90(void* stream)
{
	unsigned char* p;
	Unit520d90* u;
	int i;
	int k;
	int count;
	int ver;
	int tmp;

	count = 0;
	p = (unsigned char*) g_77e980;
	do {
		if (*p != 0)
			count++;
		p += 0x14c;
	} while (p < (unsigned char*) g_77e980 + 1024 * 0x14c);
	if (sub_430910(&ver, 4, 1, stream) <= 0)
		return 0;
	if (sub_430910(&tmp, 4, 1, stream) <= 0)
		return 0;
	for (i = 0; i < 1024; i++) {
		u = &g_77e980[i];
		if (u->kind == 0)
			continue;
		if (sub_430910(&u->kind, 1, 1, stream) <= 0)
			return 0;
		if (sub_430910(&u->f04, 4, 1, stream) <= 0)
			return 0;
		if (sub_430910(&u->f08, 2, 1, stream) <= 0)
			return 0;
		if (sub_430910(&u->f0c, 4, 1, stream) <= 0)
			return 0;
		if (sub_430910(&u->f10, 4, 1, stream) <= 0)
			return 0;
		if (sub_430910(u->f14, 0x30, 1, stream) <= 0)
			return 0;
		if (sub_430910(u->f44, 0xe, 1, stream) <= 0)
			return 0;
		if (sub_430910(u->f52, 0xe, 1, stream) <= 0)
			return 0;
		if (sub_430910(u->f60, 0xe, 1, stream) <= 0)
			return 0;
		if (sub_430910(&u->f70, 4, 1, stream) <= 0)
			return 0;
		if (sub_430910(&u->f78, 1, 1, stream) <= 0)
			return 0;
		for (k = 0; k < 8; k++) {
			if (sub_430910(&u->f8c[k], 4, 1, stream) <= 0)
				return 0;
		}
		if (u->blob != 0 && u->blob_len != 0) {
			if (sub_430910(&u->blob_len, 4, 1, stream) <= 0)
				return 0;
			if (sub_430910(u->blob, u->blob_len, 1, stream) <= 0)
				return 0;
		}
		else {
			tmp = 0;
			if (sub_430910(&tmp, 4, 1, stream) <= 0)
				return 0;
		}
		if (sub_430910(u->f0ac, 0xa0, 1, stream) <= 0)
			return 0;
	}
	count = 0;
	for (i = 0; i < 256; i++) {
		if (g_7d2020[i].id != 0)
			count++;
	}
	if (sub_430910(&tmp, 4, 1, stream) <= 0)
		return 0;
	for (i = 0; i < 256; i++) {
		if (g_7d2020[i].id == 0)
			continue;
		if (sub_430910((void*) (g_7d2020[i].id + 4), 4, 1, stream) <= 0)
			return 0;
		if (sub_430910(&g_7d2020[i].state, 1, 1, stream) <= 0)
			return 0;
		if (sub_430910(&g_7d2020[i].has_amount, 4, 1, stream) <= 0)
			return 0;
		if (sub_430910(&g_7d2020[i].owner, 4, 1, stream) <= 0)
			return 0;
		if (sub_430910(&g_7d2020[i].amount, 4, 1, stream) <= 0)
			return 0;
		if (sub_430910(g_7d2020[i].pos, 0xe, 1, stream) <= 0)
			return 0;
		if (sub_430910(g_7d2020[i].name, 0x80, 1, stream) <= 0)
			return 0;
	}
	count = 0;
	for (i = 0; i < 256; i++) {
		if (g_7dcae0[i].f8 != 0 || g_7dcae0[i].fc != 0 || g_7dcae0[i].name[0] != 0)
			count++;
	}
	if (sub_430910(&tmp, 4, 1, stream) <= 0)
		return 0;
	for (i = 0; i < 256; i++) {
		if (g_7dcae0[i].f8 == 0 && g_7dcae0[i].fc == 0 && g_7dcae0[i].name[0] == 0)
			continue;
		if (sub_430910(&g_7dcae0[i].b0, 1, 1, stream) <= 0)
			return 0;
		if (sub_430910(&g_7dcae0[i].f4, 4, 1, stream) <= 0)
			return 0;
		if (sub_430910(&g_7dcae0[i].f8, 4, 1, stream) <= 0)
			return 0;
		if (sub_430910(&g_7dcae0[i].fc, 4, 1, stream) <= 0)
			return 0;
		if (sub_430910(g_7dcae0[i].name, 0x40, 1, stream) <= 0)
			return 0;
	}
	return 1;
}
unsigned char _dpad_7d1d80[672];
unsigned char _dpad_7d2020[41984];
unsigned char _dpad_7dc440[1696];
unsigned char _dpad_7dcae0[21648];
