extern char* g_67a370;
extern int g_7e4530;
extern float g_6a2a18[7][4];
extern float g_6a2b68[7][4];
extern float g_67bbdc;
extern float g_67bbe0;
extern float g_67bbe4;

// SIZE 0x60
struct s_1041d80 {
	float v[3];
	char pad[0x54];
};

extern struct s_1041d80 g_1041d80[7];

// FUNCTION: GOLDTL 0x52a7d0
// SIZE: 182

void __cdecl fcn_004379a0(char*, int, int, void*, void*);
char __cdecl fcn_0052a320(char*);

void __cdecl fcn_0052a7d0(void)
{
	float (*src)[4];
	int i;

	if (*(int*) (g_67a370 + 0xac) != 0) {
		fcn_004379a0(g_67a370, 0, 8, (void*) fcn_0052a320, 0);
		if (g_7e4530 == 0) {
			src = g_6a2a18;
		} else {
			src = g_6a2b68;
		}
		for (i = 0; i < 7; i++) {
			*(float*) (g_67a370 + i * 0x60 + 0x128) = src[i][0];
			*(float*) (g_67a370 + i * 0x60 + 0x12c) = src[i][1];
			*(float*) (g_67a370 + i * 0x60 + 0x130) = src[i][2];
			g_67bbdc = src[i][0];
			g_67bbe0 = src[i][1];
			g_67bbe4 = src[i][2];
			g_1041d80[i].v[0] = src[i][0];
			g_1041d80[i].v[1] = src[i][1];
			g_1041d80[i].v[2] = src[i][2];
		}
	}
}
