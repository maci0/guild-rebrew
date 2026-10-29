#include <string.h>

int __cdecl fcn_00500d20(void*, void*);
char* __cdecl fcn_00508e40(int);
int __cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl gm_FindNextFilteredEntity(void);
int __cdecl fcn_00500bb0(void*, int, int, int);
int __cdecl gm_SetupEntityQuery(int);
int __cdecl gm_RandomMod(unsigned short);
int __cdecl fcn_004c5da0(int, int, int, int, int, char*);
int __cdecl fcn_00529160(int, int, int, int);
int __cdecl fcn_0050b750(int, unsigned char);
int __cdecl fcn_0050c710(int, int, int);
int __cdecl fcn_004c51a0(int, int, unsigned char, int);
int __cdecl gm_GetEntityTableEntry(int);
int __cdecl fcn_0050dc90(int);
int __cdecl fcn_0051af00(char*, ...);
int __cdecl fcn_00545d40(int, int, char*, int, int, char*);
int __cdecl gm_AccumulateTyped2(int);
int __cdecl fcn_004c5c80(int);
int __cdecl fcn_00546190(int);

/* ADDRESS: GOLDTL 0x00552a60 */
void __cdecl fcn_00552a60(int a0)
{
	unsigned char v1;
	unsigned char v2;
	int v4;
	int v5;
	int v6;
	int v7;
	unsigned char* v8;
	int v9;
	int v11;
	char v12[1024];
	int v13[5];
	unsigned short* v14;
	int v15;
	int* v16;
	int v17;
	int v18;

	v4 = fcn_00500d20((char*) a0 + 0xc4, (char*) 0x7f4c00);
	v14 = 0;
	v17 = 0;
	v15 = 0;
	v5 = (int) fcn_00508e40(*(int*) (a0 + 0xd4));
	v6 = gm_StartFilteredEntitySearch(1, 1, *(int*) (a0 + 0x10));
	v18 = v5;
	if (v6 != 0 && *(unsigned short*) (v6 + 0x27) != 0xffff) {
		v5 = *(unsigned short*) (v6 + 0x27) * 0x21c + 0x7f4ca0;
		v18 = v5;
	}
	if (*(int*) (a0 + 0x70) != -2 && v5 != 0) {
		v14 = 0;
		do {
			if (6 <= *(unsigned char*) (a0 + 0xd2)) {
				if (v14 == 0) {
					*(char*) (a0 + 0xd2) = 0;
					return;
				}
				break;
			}
			v14 = (unsigned short*) fcn_00508e40(
			    *(int*) (a0 + 0x8c + *(unsigned char*) (a0 + 0xd2) * 4));
			v17 = *(unsigned char*) (a0 + 0xd2);
			*(unsigned char*) (a0 + 0xd2) = *(unsigned char*) (a0 + 0xd2) + 1;
		} while (v14 == 0);
		*(int*) (a0 + 0x70) = 0x1e0 < v4;
		*(int*) (a0 + 0x52) = *(int*) 0x7f4c00;
		*(int*) (a0 + 0x56) = *(int*) 0x7f4c04;
		*(int*) (a0 + 0x5a) = *(int*) 0x7f4c08;
		*(unsigned short*) (a0 + 0x5e) = *(unsigned short*) 0x7f4c0c;
		fcn_00500bb0((int*) (a0 + 0x52), 0, 6, 0);
		*(unsigned char*) (a0 + 0xd2) =
		    (unsigned char) (*(unsigned char*) (a0 + 0xd2) % 6);
		v15 = (int) v14;
	} else {
		*(int*) (a0 + 0x70) = 1;
	}
	if (*(int*) (a0 + 0x70) != 0) {
		if (*(int*) (a0 + 0x70) == 1) {
			v4 = gm_StartFilteredEntitySearch(1, 1, *(int*) (a0 + 0x10));
			v14 = 0;
			if (v4 != 0 && v5 != 0) {
				v5 = gm_SetupEntityQuery(v4);
				v16 = (int*) (a0 + 0x8c);
				v17 = 6;
				do {
					v14 = (unsigned short*) fcn_00508e40(*v16);
					if (v14 != 0) {
						v6 = (int) (*(unsigned char*) (v14 + 0x41)
						    * 0.023809524f + 1.0f);
						v7 = (gm_RandomMod(4) & 0xffff) + 3;
						if (v7 != 0) {
							do {
								v7 -= 1;
								v15 = v15
								    + ((gm_RandomMod((unsigned short) ((v6 + 1) * v6)) & 0xffff)
								    + v6 * 2) * 2;
							} while (v7);
						}
						fcn_004c5c80(*(int*) (v14 + 2));
						fcn_004c5da0(*(int*) (v14 + 2),
						    *(int*) ((char*) v4 + 1),
						    *(int*) ((char*) v5 + 2), 0, 0,
						    (char*) 0x6a5bbc);
						fcn_00529160(0, 0, *v14, 0);
					}
					v16 += 1;
					v17 -= 1;
				} while (v17);
				v5 = fcn_0050b750(v15, *(unsigned char*) 0x773d75);
				fcn_0050c710(v4, 1, 1);
				v5 = (int) (((float) v6 * 0.01f + 1.0f) * v5);
				fcn_004c51a0(*(int*) (v18 + 4), -1,
				    *(unsigned char*) 0x773d75, v5);
				*(int*) (v4 + 0x4d) = *(int*) (v4 + 0x4d) + v5;
				if (*(char*) (v18 + 2) == 6) {
					v6 = gm_GetEntityTableEntry(v18);
					if (v6 != 0) {
						*(int*) (v6 + 0x18) =
						    *(int*) (v6 + 0x18) + v5;
					}
					v4 = fcn_0050dc90(v4);
					if (v4 == 0
					    || (*(unsigned char*) (v4 + 0x1b4) & 1) == 0) {
						fcn_0051af00(v12, 0x19f4, v5);
						fcn_00545d40(*(int*) (v18 + 4),
						    *(int*) (v18 + 4), v12, 0, 0x5f0,
						    (char*) 0x6b5c60);
					}
				}
			}
			fcn_00546190(a0);
			return;
		}
	} else if (v14 != 0
	    && *(int*) (*(int*) ((char*) v14 + 0x184) + 0x128) == 0) {
		v8 = (unsigned char*) gm_StartFilteredEntitySearch(1, 1,
		    *(int*) (a0 + 0xac + v17 * 4));
		v13[0] = 10;
		v13[1] = 5;
		v13[2] = 7;
		v13[3] = 0x16;
		v13[4] = 0xf;
		v9 = v13[gm_RandomMod(5) & 0xffff];
		if (v8 != 0) {
			v6 = (int) (*(unsigned char*) (v14 + 0x41) * 0.023809524f
			    + 1.0f);
			v9 = (gm_RandomMod((unsigned short) ((v6 + 1) * v6))
			    & 0xffff) + v6 * 2;
			v5 = fcn_0050b750(v9 * 2, *(unsigned char*) 0x773d75);
			if (*(char*) (a0 + 0xd8) != 0) {
				v4 = 0;
				v6 = 0x20;
				do {
					v6 -= 1;
					v7 = (gm_RandomMod(0x300) & 0xffff) * 0x21c;
					if (*(short*) (v7 + 0x7f4ca0) != -1
					    && *(char*) (v7 + 0x7f4ca8) != 0
					    && *(unsigned char*) (v7 + 0x7f4ca2) <= 9
					    && *(char*) (v7 + 0x7f4e05) != 2
					    && *(char*) (v7 + 0x7f4e05) != 1
					    && *(int*) (v7 + 0x7f4ca4)
					    != *(int*) (v18 + 4)
					    && (v4 = v7 + 0x7f4ca0,
					    gm_AccumulateTyped2(v4) < v5)) {
						v4 = 0;
					} else if (v4 != 0) {
						break;
					}
				} while (v6);
				*(char*) (a0 + 0xd8) = *(char*) (a0 + 0xd8) - 1;
				if (v4 != 0) {
					v1 = *(unsigned char*) (v4 + 0x82);
					v2 = *(unsigned char*) (v14 + 0x41);
					if (v1 - v2 <= (gm_RandomMod(0x7e) & 0xffff)) {
						fcn_004c51a0(-1, *(int*) (v4 + 4),
						    *(unsigned char*) 0x773d75, v5);
						if (*(char*) (v4 + 2) == 6
						    || *(char*) (v4 + 2) == 7) {
							fcn_0051af00(v12, 0x19f2, v5);
							fcn_00545d40(
							    *(int*) (v4 + 4),
							    *(int*) (v4 + 4), v12,
							    0, 0x5f0,
							    (char*) 0x6a5ba8);
						}
					} else if (*(char*) (v4 + 2) == 6
					    || *(char*) (v4 + 2) == 7) {
						fcn_0051af00(v12, 0x19f3);
						fcn_00545d40(*(int*) (v4 + 4),
						    *(int*) (v4 + 4), v12, 0, 0x5f0, 0);
					}
				}
			}
			v8 = (unsigned char*) (*(int*) 0x868050
			    + (unsigned int) *v8 * 0x24d);
			do {
				v9 = v13[gm_RandomMod(5) & 0xffff];
			} while (*v8 == v9);
		}
		v5 = 0;
		v9 = gm_StartFilteredEntitySearch(1, 5, v9);
		if (v9 != 0) {
			do {
				if (4 <= v5) {
					break;
				}
				v13[v5] = v9;
				v5 += 1;
				v9 = gm_FindNextFilteredEntity();
			} while (v9 != 0);
			v9 = v13[gm_RandomMod((unsigned short) v5) & 0xffff];
		} else {
			v9 = gm_StartFilteredEntitySearch(1, 5, 10);
		}
		fcn_00529160(v9, 0, *v14, a0);
		fcn_004c5c80(*(int*) (v14 + 2));
		fcn_004c5da0(*(int*) (v14 + 2), *(int*) ((char*) v9 + 1),
		    -1, 0, 1, (char*) 0x6a5bbc);
		*(int*) (a0 + 0xac + v17 * 4) = *(int*) ((char*) v9 + 1);
	}
}
