typedef struct {
	char pad_00[4];
	unsigned char v04;
	char pad_05[3];
	int v08;
	int v0c;
	char pad_10[0x18];
	int v28;
	int v2c;
	int v30;
	unsigned short v34;
	unsigned char v36;
	char pad_37[0x21];
	int v58;
	char pad_5c[0x14];
	int v70;
	char pad_74[0x84];
} Dlgs_0059dcf0;

extern void* g_7e4260[];
extern int g_7f4ca4[];
extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern unsigned short g_7f4c0c;

int __cdecl fcn_00525fb0(void*);
void __cdecl fcn_0052a0c0(void*, int);
int __cdecl fcn_00526120(void*, int);
void __cdecl fcn_004c5530(void*);
void __cdecl fcn_004c35f0(void);
void __cdecl fcn_005305a0(void);
void __cdecl fcn_0052a2d0(void);

/* ADDRESS: GOLDTL 0x0059dcf0 */
void __cdecl fcn_0059dcf0(void* a)
{
	Dlgs_0059dcf0 s;
	void* e;
	void* q;
	int i;
	int idx;

	e = 0;
	if (fcn_00525fb0(a) != 0)
		return;
	fcn_0052a0c0(a, 0);
	if (fcn_00526120((void*) *(int*) 0x14abb7c, 1) != 0) {
		for (i = 0; i < 0x20; i++) {
			if (g_7e4260[i] != 0
			    && *(unsigned char*) ((char*) g_7e4260[i] + 0x188) != 0) {
				e = g_7e4260[i];
				break;
			}
		}
		s.v04 = 0x6c;
		idx = *(unsigned short*) ((char*) a + 0x27);
		s.v36 = 1;
		s.v08 = g_7f4ca4[idx * 0x87];
		s.v0c = *(int*) ((char*) a + 1);
		s.v28 = g_7f4c00;
		s.v30 = g_7f4c08;
		s.v2c = g_7f4c04;
		q = *(void**) 0x7746cc;
		s.v34 = g_7f4c0c;
		s.v58 = *(int*) ((char*) e + 4);
		s.v70 = (q != 0 && *(unsigned short*) q != 0xfd) ? *(int*) ((char*) q + 2) : -1;
		fcn_004c5530(&s);
		fcn_004c35f0();
		fcn_005305a0();
	}
	fcn_0052a2d0();
}
