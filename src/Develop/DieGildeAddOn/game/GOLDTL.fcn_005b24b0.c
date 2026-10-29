extern char g_774a80[];
extern char g_774a80[];
extern unsigned char g_773d75;
extern unsigned char g_773d75;
extern char g_868060[];
extern char g_868060[];



void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);
int __cdecl gm_RandomMod(int);

void __cdecl fcn_005b24b0(void* a1, void* a2)
{
	char t;

	t = *(char*) ((char*) a2 + 2);
	if (t == 6 || t == 7) {
		fcn_0051af00(g_774a80, 0x132f, *(unsigned short*) a1,
		    (gm_RandomMod(3) & 0xffff)
		        + (*(char*) ((char*) a2 + 9) ? 0x1333 : 0x1330),
		    *(unsigned short*) a2,
		    (gm_RandomMod(3) & 0xffff) + 0x1336,
		    &((unsigned int*)g_868060)[g_773d75 * 189]);
		fcn_00545d40(*(int*) ((char*) a2 + 4), -1, g_774a80, 1, 0x5ec, (void*) 0);
	}
}
