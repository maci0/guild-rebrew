extern char* g_1041d00;
extern char* g_6b86ec;
extern char* g_6b86e0;
extern char* g_6b86e4;
extern char* g_6b86e8;
extern int g_6b86f8;
extern int g_6b86f0;
extern int g_6b86f4;
extern float g_662d40[3];

unsigned char __cdecl fcn_00438450(char* o);
void __cdecl fcn_00455280(char* o, char* a, float* v, char* m);
void __cdecl fcn_00455450(char* o, char* a, char* v, char* m);

/* ADDRESS: GOLDTL 0x00450d40 */
char __cdecl fcn_00450d40(char* o, char* a)
{
	if (*(int*) (o + 0x218) == 4) {
		if (!(fcn_00438450(o) & 0x40)) {
			*(char**) (o + 0x1f0) = g_6b86ec;
			g_6b86ec = o;
			return 1;
		}
		*(char**) (o + 0x1f0) = g_1041d00;
		g_1041d00 = o;
		return 1;
	}
	if (*(int*) (o + 0x218) == 8) {
		if ((o[0x215] & 1) && *(float*) (o + 0x94) > 0.0f && g_6b86f8 < 4) {
			*(char**) (o + 0x1f0) = g_6b86e0;
			g_6b86e0 = o;
			g_6b86f8++;
		}
		return 1;
	}
	if (*(int*) (o + 0x218) == 7) {
		if (*(float*) (o + 0x94) > 0.0f && !(o[0x215] & 4)) {
			fcn_00455280(o, a, g_662d40, o + 0x1d8);
			*(char**) (o + 0x1f0) = g_6b86e4;
			g_6b86e4 = o;
			g_6b86f0++;
		}
		return 1;
	}
	if (*(float*) (o + 0x94) > 0.0f) {
		fcn_00455450(o, a, o + 0x4c, o + 0x1d8);
		*(char**) (o + 0x1f0) = g_6b86e8;
		g_6b86e8 = o;
		g_6b86f4++;
	}
	return 1;
}
