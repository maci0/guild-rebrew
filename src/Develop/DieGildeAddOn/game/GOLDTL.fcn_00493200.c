extern char g_7f4ca0[];
extern float g_662c98;
unsigned short __cdecl gm_RandomMod(unsigned short n);
char* __cdecl gm_LookupEntityRecordById(int id);
int __cdecl fcn_004e8b40(int kind, int* out);
int __cdecl fcn_004e8b80(int kind, int max, void* out);
float __cdecl fcn_0050f980(unsigned int a0, unsigned int a1, unsigned int a2);
unsigned int __cdecl fcn_004a55c0(unsigned short* a0, unsigned int a1, unsigned int* a2,
				  float a3, float a4, unsigned short* a5);
void __cdecl fcn_004c4510(char* obj, int id);
void __cdecl fcn_004c4570(int a, int b, int offset, void* value);
void __cdecl fcn_004c5360(void);

/* ADDRESS: GOLDTL 0x00493200 */
int __cdecl fcn_00493200(char* a1, char* a2)
{
	char slots[0x90];
	char* pick;
	int rec[2];
	int count;
	int left;
	int index;
	int roll;
	int r;
	int m;
	unsigned int code;
	unsigned int pos;
	float f;
	unsigned char kind;
	unsigned char b;

	pick = 0;
	roll = gm_RandomMod(3);
	if (a1 == 0 || a2 == 0) {
		return 0;
	}
	kind = *(unsigned char*) (a1 + 0x130);
	if (kind == 0 || *(int*) (a1 + 0x194) < 2) {
		return 0;
	}
	if (kind == 7) {
		if (*(unsigned char*) (a1 + 0x166) == 0) {
			goto other;
		}
		if (fcn_004e8b40(*(unsigned char*) (a1 + 0x166), rec) == 0) {
			return 0;
		}
		count = fcn_004e8b80(rec[1], 6, slots);
		if (count == 0) {
			return 0;
		}
		index = gm_RandomMod(count);
		for (left = count; left != 0; left--) {
			r = *(int*) (slots + index * 24 + 4);
			if (*(int*) (a1 + 4) != r) {
				pick = gm_LookupEntityRecordById(r);
				if (pick != 0) {
					f = fcn_0050f980(*(unsigned short*) a1, *(unsigned short*) pick, 1);
					r = gm_RandomMod(0x1e);
					if ((float) r + g_662c98 > f) {
						break;
					}
					pick = 0;
				}
			}
			index = (index + 1) % count;
		}
	} else if (kind == 0xa) {
		code = 0xc00;
		pos = gm_RandomMod(0x1e);
		if (fcn_004a55c0((unsigned short*) a1, 1, &code, 0.0f,
				 (float) (int) pos + g_662c98, (unsigned short*) &pos) == 0) {
			goto other;
		}
		pick = g_7f4ca0 + (pos & 0xffff) * 0x21c;
	}
	if (pick != 0) {
		b = 1;
		fcn_004c4510(a2, *(int*) (a2 + 2));
		fcn_004c4570(4, 1, 0x1e, pick + 4);
		fcn_004c4570(1, 1, 0x22, &b);
		b = (unsigned char) gm_RandomMod(8);
		fcn_004c4570(1, 1, 0x1c, &b);
		b = (unsigned char) gm_RandomMod(8);
		fcn_004c4570(1, 1, 0x1d, &b);
		fcn_004c5360();
		return 1;
	}

other:
	kind = *(unsigned char*) (a1 + 0x130);
	if (kind != 3 && kind != 4 && roll == 0) {
		return 0;
	}
	b = 1;
	m = -1;
	fcn_004c4510(a2, *(int*) (a2 + 2));
	fcn_004c4570(4, 1, 0x1e, &m);
	fcn_004c4570(1, 1, 0x22, &b);
	b = 0xff;
	fcn_004c4570(1, 1, 0x1c, &b);
	fcn_004c4570(1, 1, 0x1d, &b);
	fcn_004c5360();
	return 1;
}
