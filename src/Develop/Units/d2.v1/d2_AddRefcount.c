


typedef struct S00469900 {
	char pad0[0x30];
	int f30;
	char pad34[8];
	int f3c;
	int f40;
	int pad44;
	int f48;
	int f4c;
	int pad50;
} S00469900;
// SIZE 0x54

extern char* d2_FileObjTable;
extern volatile int gm_GameTicks;

/* ADDRESS: GOLDDE 0x0045d220 */
void __cdecl d2_AddRefcount(int i)
{
	S00469900* e;
	int kind;

	kind = ((S00469900*)d2_FileObjTable)[i].f3c;
	e = &((S00469900*)d2_FileObjTable)[i];
	if ((kind == 5 || kind == 8) && e->f30 == 0) {
		i = e->f4c;
	}
	((S00469900*)d2_FileObjTable)[i].f40++;
	((S00469900*)d2_FileObjTable)[i].f48 = gm_GameTicks;
}
