// FUNCTION: GOLDTL 0x49f5c0
// SIZE: 258

typedef struct Small3i {
	int code;
	int a;
	int b;
} Small3i;
// SIZE 0xc

extern char g_67eb6c[];
extern char g_67eb54[];

void __cdecl fcn_004c4eb0(char* s);
void __cdecl fcn_004c4ef0(char* s);
void __cdecl fcn_004c6900(Small3i* a1);
void __cdecl fcn_004c5420(int, int, int, int, int);

int __cdecl fcn_0049f5c0(char* a1, char* a2)
{
	Small3i m;

	if (*(int*) (a2 + 8) == 0x6a6f696e) {
		m.code = *(int*) (a2 + 8);
		m.a = *(int*) (a1 + 4);
		m.b = *(int*) (a2 + 4);
		fcn_004c4eb0(g_67eb6c);
		fcn_004c6900(&m);
		fcn_004c5420(*(int*) (a1 + 4), 0x1c8, 4, 0x2000000, 0);
		fcn_004c4ef0(g_67eb6c);
		return 0x35;
	}
	if (*(int*) (a2 + 8) == 0x6c656176) {
		m.code = *(int*) (a2 + 8);
		m.a = *(int*) (a1 + 4);
		m.b = *(int*) (a2 + 4);
		fcn_004c4eb0(g_67eb54);
		fcn_004c6900(&m);
		fcn_004c5420(*(int*) (a1 + 4), 0x1c8, 4, 0x2000000, 0);
		fcn_004c4ef0(g_67eb54);
		return 0x35;
	}
	if (*(int*) (a2 + 8) == 0x6e6f6f70) {
		fcn_004c5420(*(int*) (a1 + 4), 0x1c8, 4, 0x2000000, 0);
		return 0x35;
	}
	return 0;
}
