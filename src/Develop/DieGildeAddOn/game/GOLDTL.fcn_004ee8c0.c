


extern int g_14cbca0;
extern int g_699364;
extern unsigned char g_773d75;

char* __cdecl fcn_00502cd0(int a, int b, int c, int d, int e);
void __cdecl gm_AddObjekt(int a, int b, int c);
void __cdecl fcn_00501d20(int season);

int __cdecl fcn_004ee8c0(char* obj, char* tgt, char* src)
{
	int i;
	char* query;

	for (i = 0; i < 6; i++) {
		if (*(int*) (tgt + 0xc + i * 8) == 0) {
			query = fcn_00502cd0(*(int*) (src + 0x5d), 2, 6, 0, 0xff);
			if (g_14cbca0 != -1) {
				g_699364 = *(int*) (obj + 0x14);
			}
			*(int*) (tgt + 0xc + i * 8) = *(int*) (obj + 8);
			*(int*) (tgt + 0x10 + i * 8) = *(int*) (obj + 0x10);
			if (query != 0) {
				gm_AddObjekt(*(int*) (query + 2), *(int*) (obj + 8), 2);
			}
			fcn_00501d20(g_773d75);
			return 1;
		}
	}
	return 0;
}
