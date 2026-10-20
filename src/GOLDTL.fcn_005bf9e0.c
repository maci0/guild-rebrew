int __cdecl gm_WalkEntityChain(unsigned short id);
int __cdecl fcn_004fa5b0(int, int, void*);
int __cdecl fcn_005463a0(int, int, int, int, int);
int __cdecl fcn_005462a0(void);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00526120(char*, int);
int __cdecl fcn_00526010(int, int, char);
int __cdecl fcn_0055c0f0(unsigned short*, int);
int __cdecl fcn_0055c0a0(unsigned short*, int);
int __cdecl fcn_00579640(unsigned short*, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_00473a90(int, int);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_00519190(int, int, int, int);
void __cdecl fcn_005c9220(int*);
int __cdecl fcn_005373e0(int, int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_004faaf0(unsigned short*);
void __cdecl fcn_004c4eb0(char*);
void __cdecl fcn_004c4ef0(char*);
void __cdecl fcn_004c5530(void*);

/* ADDRESS: GOLDTL 0x005bf9e0 */
int __cdecl fcn_005bf9e0(unsigned short* a0)
{
	unsigned int data[136];
	unsigned char tiny[4];
	unsigned char evt[0xfc];
	char text[1024];
	int t[6];
	int res;
	int idx;
	int i;
	int timeout;
	int hwnd;
	int p;
	int r;

	for (i = 0; i < 136; i++) {
		data[i] = 0;
	}
	idx = -1;
	res = 0;
	data[0] = 1;
	r = gm_WalkEntityChain(*(unsigned short*) (*(unsigned short*) 0x774970 * 0x21c + 0x7f4ca0));
	timeout = (int) ((float) r * 0.0085f);
	if (fcn_004fa5b0(0x1b, *(unsigned short*) 0x774970 * 0x21c + 0x7f4ca0, &data[1]) & 2) {
		timeout /= 2;
	}
	p = fcn_005463a0(2, 2, *(unsigned short*) 0x774970, 0, 0x1a);
	while (p) {
		if (*(int*) (p + 0xb4) == *(int*) (a0 + 2)) {
			fcn_0051af00(text, 0x170a, *a0);
			fcn_00526120(text, 4);
			return 0;
		}
		p = fcn_005462a0();
	}
	if (!fcn_00526010(*(unsigned short*) 0x774970 * 0x21c + 0x7f4ca0, timeout, *(char*) 0x773d75)) {
		return 0;
	}
	if (!fcn_0055c0f0(a0, *(unsigned short*) 0x774970 * 0x21c + 0x7f4ca0)) {
		fcn_0051af00(tiny, 0x170b, *a0);
		fcn_00526120(tiny, 0);
		return 0;
	}
	if (!fcn_0055c0a0(a0, *(unsigned short*) 0x774970 * 0x21c + 0x7f4ca0)) {
		fcn_0051af00(tiny, 0x170c, *a0);
		fcn_00526120(tiny, 0);
		return 0;
	}
	if (!fcn_00579640(a0, *(unsigned short*) 0x774970 * 0x21c + 0x7f4ca0)) {
		fcn_0051af00(tiny, 0x409f);
		fcn_00526120(tiny, 0);
		return 0;
	}
	hwnd = fcn_00470820(0, 0, (char*) 0x6ac494);
	fcn_00471b60(hwnd);
	fcn_004727a0(hwnd, 1);
	fcn_00473a90(0, 0);
	if (a0) {
		fcn_004727a0(hwnd, 1);
		idx = fcn_00472250(hwnd, 1, fcn_00519190(0x1708, 0x1711, timeout, *a0));
	}
	for (i = 0; i < 6; i++) {
		t[i] = -1;
	}
	t[0] = hwnd;
	t[1] = 2;
	t[2] = 3;
	t[3] = 4;
	t[4] = 3;
	t[5] = 0x15;
	fcn_005c9220(t);
	while (fcn_005373e0(0x5bf9e0, 0x677c7)) {
		if (*(int*) 0x14ce8e0 || *(int*) 0x100f1dc == 1) {
			*(int*) 0x774654 = 1;
		}
		if (*(int*) 0x100f1dc == 2 && idx != -1 && *(int*) 0x67d370 == idx) {
			*(unsigned char*) (evt + 0) = 0x1a;
			*(unsigned int*) (evt + 4) = *(unsigned int*) (*(unsigned short*) 0x774970 * 0x21c + 0x7f4ca4);
			*(unsigned int*) (evt + 8) = *(unsigned int*) 0x7746c8;
			*(unsigned char*) (evt + 0x32) = 1;
			*(unsigned int*) (evt + 0x80) = timeout;
			*(unsigned int*) (evt + 0x5c) = *(unsigned int*) (a0 + 2);
			*(unsigned int*) (evt + 0x58) = fcn_004faaf0(a0);
			fcn_004c4eb0((char*) 0x6ac4c0);
			fcn_004c5530(evt);
			fcn_004c4ef0((char*) 0x6ac4c0);
			fcn_0051af00(text, 0x1709, *a0);
			fcn_00526120(text, 0);
			*(int*) 0x774654 = 1;
			res = 1;
		}
	}
	fcn_00471e30(hwnd);
	return res;
}
