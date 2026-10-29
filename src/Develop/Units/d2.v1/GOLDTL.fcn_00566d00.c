int __cdecl fcn_00508e40(int);
int __cdecl fcn_00500cb0(void*, int);
void __cdecl fcn_00545670(int, int, int, int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_00519190(int, int, int, int, int);
void __cdecl fcn_00545780(int);
void __cdecl fcn_00546190(int);
void __cdecl fcn_0051af00(char*, int, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);
void __cdecl fcn_004c6b20(int, int, int);
int __cdecl fcn_0050e720(int, int, int, int);
void __cdecl fcn_004c54c0(int, int, int, int);

/* ADDRESS: GOLDTL 0x00566d00 */
void __cdecl fcn_00566d00(int a0)
{
	char buf[256];
	unsigned short* a;
	unsigned short* b;
	int v2;
	int v3;
	int v4;
	int state;
	int v;

	a = (unsigned short*) fcn_00508e40(*(int*) (a0 + 0xac));
	b = (unsigned short*) fcn_00508e40(*(int*) (a0 + 0xb0));
	if (!a || !b) {
		fcn_00546190(a0);
		return;
	}
	if (*(char*) ((char*) b + 2) != 6 && *(char*) ((char*) b + 2) != 7) {
		if (fcn_00500cb0((char*) a0 + 0x52, 0x7f4c00) > 0) {
			return;
		}
		*(int*) (a0 + 0x70) = 2;
	}
	state = *(int*) (a0 + 0x70);
	switch (state) {
	case 0:
		fcn_00545670(a0, 0, 0, 0x6a5a10, 0x5ec);
		d2_SetForm(*(int*) (*(int*) (a0 + 0x74) + 8), 0);
		v2 = *a;
		fcn_00519190(0x19b2, v2, *(int*) (a0 + 0xb4), v2, v2);
		*(int*) (a0 + 0x70) = *(int*) (a0 + 0x70) + 1;
		return;
	case 1:
		if (*(int*) 0x100f884 != *(int*) (*(int*) (a0 + 0x74) + 8)) {
			return;
		}
		v = *(int*) 0x100f1dc;
		if (v == -1) {
			return;
		}
		if (v == 2) {
			fcn_0051af00(buf, 0x19b3, *b);
			fcn_00545d40(*(int*) (a + 2), *(int*) (a + 2), buf, 0, 0x5fa, 0);
			fcn_004c6b20(*(int*) (a + 2), -(unsigned int) *(unsigned char*) ((char*) a + 0x1b1), 0);
			fcn_00545780(a0);
			fcn_00546190(a0);
			return;
		}
		if (v == 1) {
			fcn_0051af00(buf, 0x19b4, *b, *(int*) (a0 + 0xb4));
			fcn_00545d40(*(int*) (a + 2), *(int*) (a + 2), buf, 0, 0x5fa, 0);
		}
		fcn_00545780(a0);
		fcn_00546190(a0);
		return;
	case -1:
	case -2:
		fcn_00545780(a0);
		fcn_00546190(a0);
		return;
	case 2:
		v3 = *a;
		v2 = *b;
		v4 = *(int*) (a0 + 0xb4);
		if (fcn_0050e720(v3, v2, v4, *(unsigned char*) ((char*) a + 0x1b1) * 16000)) {
			fcn_0051af00(buf, 0x19b3, *b);
			fcn_00545d40(*(int*) (a + 2), *(int*) (a + 2), buf, 0, 0x5fa, 0);
			fcn_004c6b20(*(int*) (a + 2), -(unsigned int) *(unsigned char*) ((char*) a + 0x1b1), 0);
			fcn_00546190(a0);
			return;
		}
		fcn_0051af00(buf, 0x19b4, *b, *(int*) (a0 + 0xb4));
		fcn_00545d40(*(int*) (a + 2), *(int*) (a + 2), buf, 0, 0x5fa, 0);
		fcn_004c54c0(*(int*) (a + 2), *(int*) (b + 2), 10, 1);
		fcn_00546190(a0);
		return;
	}
	return;
}
