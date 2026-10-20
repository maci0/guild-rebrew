#pragma optimize("y", off)

typedef struct Hit4ad2e0 {
	char* p;
	float f;
} Hit4ad2e0;

void __cdecl fcn_004ad4d0(int a1);
char* __cdecl fcn_004e9110(int kind);
float __cdecl fcn_004ad500(unsigned char* a1, unsigned short* a2, int a3, int a4);
void __cdecl fcn_004c5420(int a1, int a2, int a3, int a4, int a5);
int __cdecl fcn_0051af00(char* buf, int a, int b);
int __cdecl fcn_00545d40(int id, int arg, char* text1, unsigned char flags, int value, char* text2);

/* ADDRESS: GOLDTL 0x004ad2e0 */
void __cdecl fcn_004ad2e0(void)
{
	Hit4ad2e0 hits[4];
	char text[0x104];
	int idx;
	int v3;
	int v4;
	int v5;
	int v6;
	int count;
	int i;
	int pos;
	char* obj;
	char* rec;
	float f;

	if (*(int*) 0x7f4c00 < 4) {
		return;
	}
	idx = *(int*) 0x7f4c00 % 4;
	if (idx == 0) {
		return;
	}
	v3 = *(int*) (idx * 4 + 0x664e18);
	v4 = *(int*) (idx * 4 + 0x664e0c);
	v5 = *(int*) (idx * 4 + 0x664e24);
	v6 = *(int*) ((idx - 1) * 4 + 0x664e34);
	fcn_004ad4d0(idx - 1);
	obj = fcn_004e9110(v4);
	if (obj == 0) {
		return;
	}
	count = 0;
	for (i = 0; i < 4; i++) {
		hits[i].p = 0;
		hits[i].f = 0.0f;
	}
	rec = (char*) 0x7f4ca0;
	do {
		if (!(v5 & *(int*) (rec + 0x1cc)) && (v3 & *(int*) (rec + 0x1cc)) && *(unsigned char*) (rec + 0xd) >= 7 && (*(unsigned char*) (rec + 2) == 2 || *(unsigned char*) (rec + 2) == 3 || *(unsigned char*) (rec + 2) == 4 || *(unsigned char*) (rec + 2) == 5 || *(unsigned char*) (rec + 2) == 6 || *(unsigned char*) (rec + 2) == 7)) {
			f = fcn_004ad500((unsigned char*) rec, (unsigned short*) obj, v4, 0);
			for (i = 3; i >= 0; i--) {
				if (f <= hits[i].f) {
					break;
				}
			}
			pos = i + 1;
			if (pos < 4) {
				for (i = 3; i > pos; i--) {
					hits[i] = hits[i - 1];
				}
				hits[pos].f = f;
				hits[pos].p = rec;
				count++;
			}
		}
		rec += 0x21c;
	} while ((int) rec < 0x85a0a0);
	if (count >= 4) {
		count = 4;
	}
	for (i = 0; i < count; i++) {
		if (hits[i].p == 0) {
			return;
		}
		fcn_004c5420(*(int*) (hits[i].p + 4), 0x1cc, 4, v6, 0);
		if (*(char*) (hits[i].p + 2) == 6 || *(char*) (hits[i].p + 2) == 7) {
			fcn_0051af00(text, 0x42b1, (*(char*) (hits[i].p + 9) != 0 ? 0x28 : 0) + 0x253 + v4);
			fcn_00545d40(*(int*) (hits[i].p + 4), -1, text, 0, 0x5fd, "_NACHRICHTEN_NEU_14");
		}
	}
}
