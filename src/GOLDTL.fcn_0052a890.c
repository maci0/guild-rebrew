extern int g_665d58[][6];

#pragma pack(1)
// SIZE 0xa
struct hm_6a2900 {
	char h;
	char m;
	int v;
	int pad;
};
#pragma pack()

extern struct hm_6a2900 g_6a2900[5];

// FUNCTION: GOLD 0x525a40
// SIZE: 114
// FUNCTION: GOLDTL 0x52a890
// SIZE: 114

int __cdecl fcn_00500e20(int);

void __cdecl fcn_0052a890(int a)
{
	int k;
	int i;

	k = fcn_00500e20(a);
	for (i = 0; i < 5; i++) {
		g_6a2900[i].h = g_665d58[k][i] / 60;
		g_6a2900[i].m = g_665d58[k][i] - g_6a2900[i].h * 60;
		g_6a2900[i].v = (g_6a2900[i].h * 60 + g_6a2900[i].m) * 60;
	}
}
