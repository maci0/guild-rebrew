// FUNCTION: GOLD 0x00475f60
// SIZE: 126

typedef struct Win00475f60 {
	char pad0[0x3c4];
} Win00475f60;
// SIZE 0x3c4

typedef struct Obj00475f60 {
	int pad0;
	int wins[0x60];
	int count;
	char pad188[0x2ac - 0x188];
} Obj00475f60;
// SIZE 0x2ac

extern Win00475f60 g_00f8f120[]; /* 0x00f8f120 */
extern Obj00475f60 g_00fb1020[]; /* 0x00fb1020 */
extern int g_006ed958; /* 0x006ed958 */
extern int g_006ed938; /* 0x006ed938 */
extern Win00475f60* g_006ed980; /* 0x006ed980 */
extern char s_005feaf4[]; /* 0x005feaf4 */

void __cdecl fcn_004222b0(const char* msg);

int __cdecl fcn_00475f60(int k, int i)
{
	if (k) {
		g_006ed958 = k;
	} else {
		k = g_006ed958;
	}
	if (i > g_00fb1020[k].count || i < 0) {
		fcn_004222b0(s_005feaf4);
		return 0;
	}
	g_006ed938 = g_00fb1020[k].wins[i];
	g_006ed980 = &g_00f8f120[g_006ed938];
	return 1;
}
