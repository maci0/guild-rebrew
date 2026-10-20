/* Kidnapping message handler: validates the request against the current
 * location slot, builds and posts the stealing-guild packet, and pumps the
 * message queue until the dialog reports no further action. */

typedef struct F8 {
	int mask;
	int b;
} F8;
// SIZE 0x8

int __cdecl fcn_00525f60(char* a1, int a2);
int __cdecl fcn_004a5e60(char* p, int kind, F8 f, int c, float r, int* out);
void* __cdecl fcn_00503fe0(int a1, int a2, int a3);
int __cdecl fcn_00470820(int a1, int a2, char* text);
void __cdecl fcn_00471b60(int a1);
void __cdecl fcn_00473a90(int a1, int a2);
void __cdecl fcn_004727a0(int a1, int a2);
int __cdecl fcn_00519190(int a1, int a2, int a3, int a4);
int __cdecl fcn_00472250(int a1, int a2, int a3);
int __cdecl fcn_005373e0(void* a1, int a2);
void __cdecl fcn_00471e30(int a1);
void __cdecl fcn_0051af00(char* buf, int id, ...);
int __cdecl fcn_00526120(void* a1, int a2);
void __cdecl fcn_004c5530(char* msg);
void __cdecl fcn_004c6ae0(int a1, int a2);
void __cdecl fcn_004f4f60(int a1, int a2, int a3, int a4, int a5);
void __cdecl fcn_004c35f0(void);
void __cdecl fcn_005305a0(void);

/* ADDRESS: GOLDTL 0x005ae6a0 */
int __cdecl fcn_005ae6a0(void* a0)
{
	char msg[0xf8];
	char text[2048];
	F8 f;
	void* p;
	char* q;
	int found;
	int v8;
	int v9;
	int v10;
	int slot;
	int k;
	int i;
	int res;

	res = 0;
	if (a0 != 0 &&
	    fcn_00525f60((char*) (0x7f4ca0 + *(unsigned short*) 0x774970 * 0x21c), 3) != 0 &&
	    (*(int*) ((char*) a0 + 0x16c) == 0 ||
	     *(short*) (*(int*) ((char*) a0 + 0x16c) + 0x27) != *(short*) a0)) {
	if (*(unsigned char*) ((char*) a0 + 0x1b1) != 0) {
		fcn_0051af00(text, 0x19ba, *(short*) a0);
		fcn_00526120(text + 0xc, 0);
		return 0;
	}
	p = *(void**) ((char*) a0 + 0x170);
	if (p == 0) {
		f.mask = 0x4080a0;
		f.b = 0;
		if (fcn_004a5e60((char*) a0, 0, f, 0, 100.0f, &found) == 0)
			return 0;
		p = fcn_00503fe0(1, 1, found);
	}
	v8 = fcn_00470820(0, 0, (char*) 0x6ab2b0);
	fcn_00471b60(v8);
	fcn_00473a90(0, 0);
	fcn_004727a0(v8, 1);
	v9 = fcn_00519190(0x19b9, *(short*) a0, 3, *(short*) a0);
	v10 = fcn_00472250(v8, 1, v9);
	v9 = fcn_00472250(v8, 1, v9 + 1);
	*(int*) 0x100f1dc = -1;
	do {
		if (*(int*) 0x14ce8e0 != 0)
			*(int*) 0x774654 = 1;
		if (*(int*) 0x100f1dc != -1) {
			if (*(int*) 0x67d370 != v10) {
				if (*(int*) 0x67d370 == v9)
					*(int*) 0x774654 = 1;
			} else {
				for (i = 0; i < 0x3e; i++)
					((int*) msg)[i] = 0;
				*(unsigned char*) (msg + 4) = 0x3c;
				*(unsigned char*) (msg + 0x36) = 1;
				slot = *(int*) (0x7f4ca4 + *(unsigned short*) 0x774970 * 0x21c);
				*(int*) (msg + 8) = slot;
				*(int*) (msg + 0x58) = *(int*) ((char*) a0 + 4);
				*(int*) (msg + 0x5c) = *(int*) ((char*) p + 1);
				*(int*) (msg + 0x60) = *(int*) (*(int*) 0x7746c4 + 1);
				for (i = 0; i < 8; i++)
					*(int*) (msg + 0x38 + i * 4) = -1;
				k = 0;
				for (q = (char*) 0x7f4ca4; (int) q < (int) 0x85a0a4; q += 0x21c) {
					if (*(unsigned char*) (q + 0x184) != 0) {
						*(int*) (msg + 0x38 + k * 4) = *(int*) q;
						k++;
					}
				}
				if (k != 0) {
					fcn_004c5530(msg);
					fcn_004c6ae0(*(int*) (0x7f4ca4 + *(unsigned short*) 0x774970 * 0x21c), -3);
					fcn_004f4f60(0x1a, 1, *(int*) (0x7f4ca4 + *(unsigned short*) 0x774970 * 0x21c),
						*(int*) ((char*) a0 + 4), -1);
					fcn_004c35f0();
					fcn_005305a0();
					res = 1;
					*(int*) 0x774654 = 3;
				} else {
					fcn_00526120((void*) *(int*) 0x14abaac, 0);
					*(int*) 0x100f1dc = -1;
				}
			}
		}
	} while (fcn_005373e0((void*) 0x5ae6a0, 0x677c7) != 0);
	fcn_00471e30(v8);
	return res;
	}
	return 0;
}
