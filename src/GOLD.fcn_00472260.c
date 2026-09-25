// FUNCTION: GOLD 0x00472260
// SIZE: 275

typedef struct
{
	int i[0x3c4 / 4];
} fcn_00472260_Win;
// SIZE 0x3c4

typedef struct
{
	int i[0x2ec / 4];
} fcn_00472260_Ent;
// SIZE 0x2ec

extern fcn_00472260_Win g_00f8f120[]; /* 0x00f8f120 */
extern fcn_00472260_Ent* g_00f8f080; /* 0x00f8f080 */

int __cdecl fcn_004731c0(int x, int y, int a3, int win);

void __cdecl fcn_00472260(int x, int y, int win, int target, int id)
{
	int wo;

	wo = win * sizeof(fcn_00472260_Win);
	if (x == -1 && y == -1) {
		x = *(short*) ((char*) g_00f8f120 + wo + 0x8) - 0x20;
		y = *(short*) ((char*) g_00f8f120 + wo + 0xa) - 0x20;
	}
	*(int*) ((char*) g_00f8f120 + wo + 0x3ac) = fcn_004731c0(x, y, id, win);
	g_00f8f080[*(int*) ((char*) g_00f8f120 + wo + 0x3ac)].i[0x1e0 / 4] = target;
	g_00f8f080[*(int*) ((char*) g_00f8f120 + wo + 0x3ac)].i[0x1c0 / 4] = 3;
	x -= 0x20;
	*(int*) ((char*) g_00f8f120 + wo + 0x3a8) = fcn_004731c0(x, y, id + 1, win);
	g_00f8f080[*(int*) ((char*) g_00f8f120 + wo + 0x3a8)].i[0x1e0 / 4] = target;
	g_00f8f080[*(int*) ((char*) g_00f8f120 + wo + 0x3a8)].i[0x1c0 / 4] = 3;
	*(int*) ((char*) g_00f8f120 + wo + 0x248) = 0;
	g_00f8f120[target].i[0x264 / 4] = 0x30;
}
