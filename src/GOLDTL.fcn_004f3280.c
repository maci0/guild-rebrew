// FUNCTION: GOLD 0x004f1170
// SIZE: 132
// FUNCTION: GOLDTL 0x004f3280
// SIZE: 132

#pragma pack(push, 1)
typedef struct
{
	int h0;
	int h4;
	int id;
	int x0c;
	char x10;
	int x11;
	int x15;
	char pad[3];
} Msg1c;
// SIZE 0x1c
#pragma pack(pop)

extern unsigned short* g_773da8;
extern char g_7f4ca0[];

void __cdecl fcn_004f4f60(int a, int b, int c, int d, int e);
int __cdecl fcn_004c6cb0(Msg1c* m);

int __cdecl fcn_004f3280(char* obj, int a2, int a3, int a4, int a5)
{
	Msg1c m;

	if (*(unsigned short*) (obj + 0x27) == 0xffff || *(unsigned short*) (obj + 0x27) == *g_773da8 || a3 == -1) {
		return -1;
	}
	m.id = *(int*) (obj + 1);
	m.x0c = a2;
	m.x10 = (char) a3;
	m.x11 = a4;
	m.x15 = a5;
	fcn_004f4f60(0x1b, 1, *(int*) (g_7f4ca0 + 4 + *(unsigned short*) (obj + 0x27) * 0x21c), -1, *(int*) (obj + 1));
	return fcn_004c6cb0(&m);
}
