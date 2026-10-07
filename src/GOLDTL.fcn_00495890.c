typedef struct Ent {
	unsigned short id;
	unsigned char kind;
	char pad3;
	int handle;
	char pad8[0x21c - 8];
} Ent;
// SIZE 0x21c

extern char g_7f4ca0[];

unsigned short __cdecl fcn_0042e410(int n);
void __cdecl fcn_004c4510(Ent* e, int h);
void __cdecl fcn_004c4570(int a, int b, int c, int* flags);
void __cdecl fcn_004c5360(void);

// FUNCTION: GOLD 0x495ed0
// FUNCTION: GOLDTL 0x495890
void __cdecl fcn_00495890(void)
{
	int flags;
	int i;

	flags = 1;
	for (i = 0; i < 768; i++) {
		if (((Ent*)g_7f4ca0)[i].kind != 3) {
			continue;
		}
		flags |= fcn_0042e410(2) ? 2 : 0;
		flags |= fcn_0042e410(3) ? 4 : 0;
		flags |= fcn_0042e410(3) ? 8 : 0;
		flags |= fcn_0042e410(2) ? 0x10 : 0;
		fcn_004c4510(&((Ent*)g_7f4ca0)[i], ((Ent*)g_7f4ca0)[i].handle);
		fcn_004c4570(4, 1, 0x1e8, &flags);
		fcn_004c5360();
	}
}
