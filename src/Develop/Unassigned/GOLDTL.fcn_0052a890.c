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




int __cdecl gm_GetSeason(int);

void __cdecl gm_UpdateDaylightSchedule(int a)
{
	int k;
	int i;

	k = gm_GetSeason(a);
	for (i = 0; i < 5; i++) {
		g_6a2900[i].h = g_665d58[k][i] / 60;
		g_6a2900[i].m = g_665d58[k][i] - g_6a2900[i].h * 60;
		g_6a2900[i].v = (g_6a2900[i].h * 60 + g_6a2900[i].m) * 60;
	}
}
