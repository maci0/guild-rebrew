extern unsigned char g_773d75;
extern char g_7f4ca0[];

void __cdecl fcn_004c5150(int, int, unsigned char, int);
void __cdecl fcn_004c5420(int, int, int, int, int);
int* __cdecl fcn_004ac1e0(int);
unsigned short __cdecl fcn_0042e410(unsigned short);
void __cdecl fcn_004c4510(void*, int);
void __cdecl fcn_004c4670(int, int, short, char*);
void __cdecl fcn_004c5360(void);
int __cdecl fcn_00507b00(int);
void __cdecl fcn_004c54c0(int, int, int, int);

// FUNCTION: GOLD 0x004ac2f0
// FUNCTION: GOLDTL 0x4ac410

void __cdecl fcn_004ac410(unsigned char* a1, int a2, int a3)
{
	int* p;
	char c;
	int i;
	char* rec;

	fcn_004c5150(-1, *(int*) (a1 + 4), g_773d75, a2);
	fcn_004c5420(*(int*) (a1 + 4), 0x1c8, 4, 0x20000, 0);
	p = fcn_004ac1e0(a3);
	if (p == 0)
		return;
	if (p[0] == 0 && *(unsigned short*) (p + 1) <= 4) {
		c = fcn_0042e410(8) + 8;
		c = c < 252.0f - a1[*(unsigned short*) (p + 1) + 0x80] ? c : 252.0f - a1[*(unsigned short*) (p + 1) + 0x80];
		fcn_004c4510(a1, *(int*) (a1 + 4));
		fcn_004c4670(1, 1, *(unsigned short*) (p + 1) + 0x80, &c);
		fcn_004c5360();
		return;
	}
	if (p[0] == 1) {
		for (i = 0; i < 768; i++) {
			rec = g_7f4ca0 + i * 540;
			if (*(int*) (rec + 4) != *(int*) (a1 + 4)
			    && fcn_00507b00(*(unsigned char*) (rec + 0x164)) == *(unsigned short*) (p + 1))
				fcn_004c54c0(*(int*) (a1 + 4), *(int*) (rec + 4), fcn_0042e410(4) + 3, 0);
		}
	}
}
