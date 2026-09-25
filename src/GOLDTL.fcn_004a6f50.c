// FUNCTION: GOLDTL 0x4a6f50
// SIZE: 368

typedef struct Seq {
	int state;
	char pad4[0xb0 - 4];
	int xb0;
} Seq;
// SIZE 0xb4

extern Seq* g_1007cd4;

void __cdecl fcn_004a8770(void);
void __cdecl fcn_004a8640(void);
void __cdecl fcn_004a7be0(void);
void __cdecl fcn_004a8810(void);
void __cdecl fcn_004a7d40(void);
void __cdecl fcn_004a86b0(void);
void __cdecl fcn_004a7b40(void);
void __cdecl fcn_004a7900(void);
void __cdecl fcn_004a8700(void);
void __cdecl fcn_004a87b0(void);

short __cdecl fcn_004a6f50(void)
{
	switch (g_1007cd4->state) {
	case 0:
		g_1007cd4->state = 1;
		return g_1007cd4->xb0 ? 0x10 : 0x21;
	case 1:
		fcn_004a8770();
		g_1007cd4->state++;
		fcn_004a8640();
		fcn_004a7be0();
		fcn_004a8810();
		return 0;
	case 2:
		g_1007cd4->state = 3;
		return (g_1007cd4->xb0 ? 0 : 0x20) | 9;
	case 3:
		fcn_004a7be0();
		fcn_004a7d40();
		g_1007cd4->state++;
		fcn_004a86b0();
		fcn_004a7b40();
		return 0;
	case 4:
		g_1007cd4->state = 5;
		fcn_004a7be0();
		fcn_004a8810();
		return (g_1007cd4->xb0 ? 0 : 0x20) | 9;
	case 5:
		fcn_004a7d40();
		fcn_004a7b40();
		g_1007cd4->state++;
		return 0x1c;
	case 6:
		fcn_004a7900();
		g_1007cd4->state++;
		return 0x10;
	case 7:
		fcn_004a8700();
		g_1007cd4->state++;
		break;
	case 8:
		fcn_004a7be0();
		g_1007cd4->state++;
		return (g_1007cd4->xb0 ? 0 : 0x20) | 9;
	case 9:
		fcn_004a7d40();
		fcn_004a7b40();
		g_1007cd4->state++;
		return 0;
	case 10:
		g_1007cd4->state = 11;
		fcn_004a87b0();
		return 0x10;
	}
	return 0;
}
