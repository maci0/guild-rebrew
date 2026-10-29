


extern int g_6b8010;

int __cdecl fcn_004c5620(int a, char* q);
int __cdecl fcn_00413190(int x);
void __cdecl fcn_004432d0(int a, int b);
void __cdecl fcn_004030e0(char* r);
char* __cdecl gm_EntityAccumulate(char* p);
int __cdecl fcn_00502f00(char* list, int id);

void __cdecl fcn_00506300(char* p)
{
	int save;
	char* q;
	char* r;
	char* e;

	save = g_6b8010;
	q = *(char**) (p + 0x24);
	if (q != 0 && (q[0x78] & 2)) {
		*(int*) (q + 0x84) = fcn_004c5620(-1, q);
	}
	r = *(char**) (p + 0x3b);
	if (r != 0) {
		fcn_004432d0(fcn_00413190(*(int*) (r + 0x88)), 1);
		fcn_004030e0(r);
		fcn_004432d0(save, 1);
	}
	e = gm_EntityAccumulate(p);
	if (e != 0) {
		fcn_00502f00(e + 0x5d, *(int*) (p + 2));
	}
}
