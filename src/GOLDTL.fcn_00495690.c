extern char* g_77261c;

void __cdecl fcn_004c47e0(void*);
void __cdecl fcn_004c4510(void*, int);
void __cdecl fcn_004c4670(int, int, int, int*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_004c53e0(void);
void __cdecl fcn_004c4820(int, float);
void* __cdecl fcn_0064d740(void* dst, const void* src, unsigned int n);

/* ADDRESS: GOLDTL 0x00495690 */
int __cdecl fcn_00495690(int a0)
{
	unsigned char* b;
	unsigned char idx;
	void* fn;
	char* t;
	int i;

	b = (unsigned char*) (0x7f4ca0 + a0 * 0x21c);
	idx = *(unsigned char*) (0x7f4dd2 + a0 * 0x21c);
	if (!idx)
		goto fail;
	fn = *(void**) (0x100856c + idx * 0x94);
	if (!fn)
		goto fail;
	if (!((int (__cdecl*) (void*, void*, void*)) fn) (b, b + 0x134, b + 0x14c))
		goto fail;
	fcn_004c47e0(b);
	for (i = 0; i < 0x20; i += 8) {
		t = (char*) (0x1008570 + (unsigned int) b[0x131] * 0x94 + i);
		if ((unsigned char) t[0] < 0xe)
			fcn_004c4820(t[0], *(float*) (t + 4) * *(float*) 0x664158);
	}
	for (i = 0; i < 0x20; i += 8) {
		t = (char*) (0x1008590 + (unsigned int) b[0x132] * 0x94 + i);
		if ((unsigned char) t[0] < 0xe)
			fcn_004c4820(t[0], *(float*) (t + 4) * *(float*) 0x664158);
	}
	if (b[0x131] != b[0x132]) {
		fcn_004c4820(0xd, 1000.0f);
		if (g_77261c && *(int*) (g_77261c + 4) == *(int*) (b + 0x210)) {
			*(unsigned char*) &a0 = 1;
			fcn_004c4510(b, *(int*) (b + 4));
			fcn_004c4670(1, 1, 0x215, &a0);
			fcn_004c5360();
		}
	} else {
		fcn_004c4820(0xd, 500.0f);
		if (g_77261c && *(int*) (g_77261c + 4) == *(int*) (b + 0x210)) {
			*(unsigned char*) &a0 = 2;
			fcn_004c4510(b, *(int*) (b + 4));
			fcn_004c4670(1, 1, 0x215, &a0);
			fcn_004c5360();
		}
	}
	goto copies;
fail:
	if (g_77261c && *(int*) (g_77261c + 4) == *(int*) (b + 0x210)) {
		*(unsigned char*) &a0 = 3;
		fcn_004c4510(b, *(int*) (b + 4));
		fcn_004c4670(1, 1, 0x215, &a0);
		fcn_004c5360();
	}
	return 0;
copies:
	fcn_004c53e0();
	idx = b[0x132];
	fcn_0064d740((char*) (0x1008590 + idx * 0x94), (char*) (0x1008570 + idx * 0x94), 0x20);
	return 1;
}
