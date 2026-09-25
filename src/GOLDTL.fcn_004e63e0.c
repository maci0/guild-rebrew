int __cdecl fcn_004e6200(int, int*);
char* __cdecl fcn_00508e40(int);
int __cdecl fcn_0064d41a(char*, char*, ...);
int __cdecl fcn_004c6d70(int*, char*);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00535960(void);

// FUNCTION: GOLDTL 0x4e63e0
// SIZE: 241

int __cdecl fcn_004e63e0(int* a1)
{
	int flag;
	char buf[0x80];
	char* e;
	int i;
	int r;

	if (fcn_004e6200(a1[3], a1) == 0) {
		flag = 1;
		e = fcn_00508e40(a1[3]);
		fcn_0064d41a(buf, "cut_CheckMaster(): invalid master for id %i", a1[0]);
		for (i = 0; i < 16; i++) {
			if (flag == 0)
				break;
			if (a1[i + 13] != -1) {
				e = fcn_00508e40(a1[i + 13]);
				if (e != 0 && (e[2] == 6 || e[2] == 7))
					flag = 0;
			}
		}
		if (e != 0 && *(int*) (e + 4) != a1[3]) {
			fcn_0064d41a(buf, "cut_CheckMaster(): new master for id %i => %i", a1[0], *(int*) (e + 4));
			r = fcn_004c6d70(a1, e);
			while (fcn_004c4450(r) == 0)
				fcn_00535960();
			return 0;
		}
	}
	return 1;
}
