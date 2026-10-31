extern int g_aed32c;

int __cdecl gm_LookupEntityRecordById(int a0);
void __cdecl fcn_004c4510(char* a0, int a1);
void __cdecl fcn_004c4700(int a0, int a1, int a2, int* a3);
void __cdecl fcn_004c53a0(void);
int __cdecl fcn_0050f950(int a0, int a1);
void __cdecl fcn_004c54c0(int a0, int a1, int a2, int a3);
void __cdecl fcn_004c6430(int a0, int a1, int a2);
void __cdecl fcn_004c6650(int a0);
int __cdecl fcn_00500480(char* a0, int* a1, int* a2);
void __cdecl fcn_004c5da0(int a0, int a1, int a2, int a3, int a4, char* a5);
void __cdecl fcn_00546190(int a0);

/* ADDRESS: GOLDTL 0x00566110 */
void __cdecl fcn_00566110(int a0)
{
	char* ent;
	int v6;
	int v7;
	int v5;
	unsigned short v1;
	unsigned short v2;

	v6 = 0;
	if (*(int*) (a0 + 0x70) < -2) {
		return;
	}
	if (*(int*) (a0 + 0x70) < 0) {
		goto tail;
	}
	if (*(int*) (a0 + 0x70) != 0) {
		return;
	}
	ent = (char*) gm_LookupEntityRecordById(*(int*) (a0 + 0xac));
	if (ent == 0) {
		goto fail;
	}
	if (*(char*) (ent + 8) == 0) {
		goto fail;
	}
	if (*(int*) (ent + 0x16c) != 0) {
		fcn_004c4510(ent, *(int*) (ent + 4));
		fcn_004c4700(4, 1, (int) ent - g_aed32c + 0x16c, &v6);
		fcn_004c53a0();
		v2 = *(unsigned short*) (*(int*) (ent + 0x16c) + 0x27);
		v1 = *(unsigned short*) ent;
		if (fcn_0050f950(v2, v1) > -0x1e) {
			v2 = *(unsigned short*) (*(int*) (ent + 0x16c) + 0x27);
			v1 = *(unsigned short*) ent;
			v6 = -0x1e - fcn_0050f950(v2, v1);
		}
		v5 = v6;
		fcn_004c54c0(*(int*) (v2 * 0x21c + 0x7f4ca4), *(int*) (ent + 4), v5, 1);
	}
	fcn_004c6430(*(int*) (ent + 4), 0, 0);
	fcn_004c6650(*(int*) (ent + 4));
	if (fcn_00500480(ent, &a0, &v7) != 0) {
		fcn_004c5da0(*(int*) (ent + 4), a0, v7 == -1 ? -1 : v7, 0, v7 == -1, (char*) 0x6a68b0);
	}
tail:
	fcn_00546190(a0);
	return;
fail:
	*(int*) (a0 + 0x70) = -1;
}
