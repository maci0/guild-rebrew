

int __cdecl fcn_00413190(int);
void __cdecl fcn_004432d0(int, int);
void __cdecl fcn_00442be0(char*);

void __cdecl fcn_00418ae0(char* p)
{
	int k;
	int save;

	save = *(int*) 0x6b8010;
	k = -1;
	if (*(int*) (p + 0x20c) != *(int*) 0x67a370) {
		k = fcn_00413190(*(int*) (p + 0x20c));
		fcn_004432d0(k, 1);
	}
	fcn_00442be0(p);
	*(int*) 0x6b5cfc = 0;
	if (k != -1) {
		fcn_004432d0(save, 1);
	}
}
