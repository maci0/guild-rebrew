extern float g_6628fc;
extern double g_664f10;
extern char g_68bdc4[];
extern char g_68bda8[];
extern char g_68bdd4[];

unsigned int __cdecl fcn_004e6cb0(int n);
int __cdecl fcn_004234e0(int, char*, int, int, int, int, int);
int __cdecl fcn_00442910(int, char*, float*, char*);
int __cdecl fcn_00412f10(int, char*, int);

/* ADDRESS: GOLDTL 0x004d4700 */
int __cdecl fcn_004d4700(char* e)
{
	float rot[3];
	int h;

	rot[0] = 0.0f;
	rot[1] = 0.0f;
	rot[2] = 0.0f;
	rot[1] = fcn_004e6cb0(0x168) * g_6628fc * g_664f10;
	fcn_004234e0(0, g_68bdd4, 1, 63, 127, 0, 0);
	h = fcn_00442910(0, *(char**) (*(char**) (e + 0x14) + 0x34) + 0x4c, rot, g_68bdc4);
	return fcn_00412f10(h, g_68bda8, 0x12);
}
