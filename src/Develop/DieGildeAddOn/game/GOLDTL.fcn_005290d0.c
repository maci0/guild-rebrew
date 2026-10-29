extern unsigned char* lpGebaeudePROT;




unsigned char* __cdecl fcn_00508e40(int);
int __cdecl ahm_CheckFlag(unsigned char*);

void __cdecl fcn_005290d0(char* o)
{
	int i;
	unsigned char* e;
	unsigned char* t;

	*(int*) (o + 0x14) = 0;
	*(int*) (o + 0x18) = 0;
	for (i = 0; i < 8; i++) {
		if (((int*) (o + 0x8c))[i] != -1) {
			e = fcn_00508e40(((int*) (o + 0x8c))[i]);
			if (e != 0 && *(unsigned char**) (e + 0x16c) != 0) {
				t = lpGebaeudePROT + **(unsigned char**) (e + 0x16c) * 0x24d;
				if (e[0x165] == t[0x22f]) {
					(*(int*) (o + 0x14))++;
				} else if (e[0x165] == t[0x230]) {
					(*(int*) (o + 0x18))++;
				} else if (*t == 0x1e && ahm_CheckFlag(e) != 0) {
					(*(int*) (o + 0x14))++;
				}
			}
		}
	}
}
