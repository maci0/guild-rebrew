


extern char* g_7746c4;
extern unsigned char* g_868050;
extern char g_6b5c60[];

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl fcn_00502cd0(int, int, int, int);
void __cdecl fcn_00526920(char*, int, char*);

void __cdecl fcn_0057fd60(int a)
{
	char* e;
	char* r;

	if (a == 0) {
		if (((unsigned char*)g_7746c4) == 0 || ((char*)g_868050)[*((unsigned char*)g_7746c4) * 589] != 0x12) {
			e = gm_StartFilteredEntitySearch(1, 5, 0x12);
			if (e != 0) {
				r = fcn_00502cd0(*(int*) (e + 0x5d), 1, 0, 0x74);
				if (r != 0) {
					fcn_00526920(e, *(int*) (r + 2), g_6b5c60);
				}
			}
		}
	}
}
