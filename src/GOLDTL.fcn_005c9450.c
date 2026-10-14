

void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

typedef struct
{
	char pad0[0x5c];
	int x5c;
	char pad60[0x170];
	int x1d0;
	char pad1d4[0x11c];
	char* x2f0;
} Slot;
// SIZE 0x2f4

extern char* g_1015ea0;
extern int g_772514;
extern char s_6ac948[];
extern char s_68be7c[];

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_AddObjekt(void);
int __cdecl fcn_0050cf50(char*, int);
int __cdecl fcn_0046f740(int, int, int, int);
void __cdecl fcn_0051af00(char*, char*, ...);
void __cdecl fcn_0046fac0(int, int, char*, int);

int __cdecl fcn_005c9450(unsigned short* who, int n, int* arr)
{
	int cnt;
	int flag;
	char buf[0x100];
	int y;
	char* e;
	int v;
	int h;

	y = 0;
	flag = 0;
	if (n > 0 && arr != 0) {
		flag = 1;
		memset(arr, 0xff, n * 4);
	}
	h = 0;
	cnt = 0;
	for (e = gm_StartFilteredEntitySearch(1, 4, *who); e != 0; e = gm_AddObjekt()) {
		if (e[0x5a] & 1) {
			continue;
		}
		v = fcn_0050cf50(e, e[0x5c]);
		h = fcn_0046f740(0x20, y, (unsigned char) e[0] + 0x427, g_772514);
		fcn_0051af00(buf, s_6ac948, e);
		fcn_0046fac0(0x80, y, buf, g_772514);
		fcn_0051af00(buf, s_68be7c, v);
		fcn_0046fac0(0x80, y + 0x1b, buf, g_772514);
		if (flag == 1 && cnt < n) {
			((Slot*)g_1015ea0)[h].x5c = 1;
			((Slot*)g_1015ea0)[h].x1d0 = 3;
			((Slot*)g_1015ea0)[h].x2f0 = e;
			arr[cnt] = h;
		}
		cnt++;
		y += 0x40;
	}
	return cnt;
}
