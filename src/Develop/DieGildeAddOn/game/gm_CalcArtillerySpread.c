


extern float g_6652d4;
extern float g_6652c8;
extern float g_6652d0;
extern float g_662960;

int __cdecl gm_QueryEntities(int a, int b, int c, int d, int e);

/* ADDRESS: GOLDDE 0x004dd430 */
void __cdecl gm_CalcArtillerySpread(char* p, float* o1, float* o2)
{
	float x;
	float y;

	x = 0.02f;
	y = 0.2f;
	if (gm_QueryEntities(*(int*) (p + 0x5d), 2, 6, 0, 0x25c)) {
		x = 0.02f - 0.003f;
		y = 0.17f;
	}
	if (gm_QueryEntities(*(int*) (p + 0x5d), 2, 6, 0, 0x25f)) {
		x -= g_6652d4;
		y -= g_6652c8;
	}
	if (gm_QueryEntities(*(int*) (p + 0x5d), 2, 6, 0, 0x260)) {
		x -= g_6652d0;
		y -= g_662960;
	}
	*o1 = x;
	*o2 = y;
}
