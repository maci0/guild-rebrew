extern int g_7e4318;
extern unsigned short g_774970;
extern char g_7f4ca4[];

char* __cdecl fcn_00502cd0(int, int, int, int);
void __cdecl fcn_00529160(char*, int, int, int);
void __cdecl fcn_004c5c80(int);
void __cdecl fcn_004c5da0(int, int, int, int, int, int);
int __cdecl fcn_004c5620(int, char*);
void __cdecl fcn_004c5530(char*);

/* ADDRESS: GOLDTL 0x00531320 */
void __cdecl fcn_00531320(void)
{
	char* v1;
	int v10[34];
	char msg[4];
	char* v12;
	int* v13;
	int* v9;
	int* v17;
	int v16;
	int v6;
	int v18;
	int v19;
	int v5;
	int v7;
	int v8;
	int v14;
	int v15;
	char v20;
	unsigned int v21;
	char v22;
	unsigned int v23;
	unsigned int v24;

	v5 = 0;
	v9 = v10;
	v16 = 0;
	v18 = 0;
	v12 = 0;
	v19 = 0;
	v20 = 0;
	v13 = (int*) 0x7f4e0c;
	v6 = g_7e4318;
	v17 = v9;
	do {
		if (v20 != 0) {
			break;
		}
		if (*(char*) &v13[7] != 0) {
			if (v5 != 0) {
				if (v5 == 0x43 && *v13 == v18 && (char*) v13[4] == v12) {
					if (*v13 == v6) {
						v9 = (int*) (v12 + 0xc4);
						v6 = 0;
						do {
							if (*v9 == v13[-0x5a]) {
								v1 = &v12[v6 * 4 + 0xc4];
								v1[0] = '\xff';
								v1[1] = '\xff';
								v1[2] = '\xff';
								v1[3] = '\xff';
								break;
							}
							v6 += 1;
							v9 = &v9[1];
						} while (v6 < 4);
						fcn_00529160((char*) g_7e4318, 0, v13[-0x5b], 0);
						fcn_004c5c80(v13[-0x5a]);
						v15 = *(unsigned int*) (v5 + 2);
						v14 = *(unsigned int*) (g_7e4318 + 1);
						v5 = v13[-0x5a];
						goto stored;
					}
					v5 = v13[-0x5a];
					*v9 = v5;
					v16 += 1;
					v17 = &v9[1];
					v7 = 0;
					v9 = (int*) (v12 + 0xc4);
					do {
						if (*v9 == v5) {
							v1 = &v12[v7 * 4 + 0xc4];
							v1[0] = '\xff';
							v1[1] = '\xff';
							v1[2] = '\xff';
							v1[3] = '\xff';
							v6 = g_7e4318;
							break;
						}
						v7 += 1;
						v9 = &v9[1];
					} while (v7 < 4);
					if (v16 >= 4) {
						v20 = 1;
					}
				}
			} else {
				v1 = (char*) v13[4];
				if (v1 != 0 && (v5 = *v13) != 0 && *v1 == 'C') {
					v19 = 0x43;
					v12 = v1;
					if (v5 != v6) {
						v20 = 'C';
						v22 = 2;
						v17 = &v9[1];
						v21 = *(unsigned int*) (g_7f4ca4 + g_774970 * 0x21c);
						v23 = *(unsigned int*) (v6 + 1);
						v7 = v13[-0x5a];
						v24 = *(unsigned int*) (v5 + 1);
						*v9 = v7;
						v16 += 1;
						if (v16 <= 3) {
							v8 = 4 - v16;
							v9 = v17;
							while (v8 != 0) {
								int* v2;

								v2 = &v9[1];
								*v9 = -1;
								v8 -= 1;
								v9 = v2;
							}
						}
						v8 = 0;
						v9 = (int*) (v1 + 0xc4);
						do {
							v18 = v5;
							if (*v9 == v7) {
								v1 = &v1[v8 * 4 + 0xc4];
								v1[0] = '\xff';
								v1[1] = '\xff';
								v1[2] = '\xff';
								v1[3] = '\xff';
								goto final;
							}
							v8 += 1;
							v9 = &v9[1];
						} while (v8 < 4);
					} else {
						v9 = (int*) (v1 + 0xc4);
						v6 = 0;
						do {
							if (*v9 == v13[-0x5a]) {
								v1 = &v1[v6 * 4 + 0xc4];
								v1[0] = '\xff';
								v1[1] = '\xff';
								v1[2] = '\xff';
								v1[3] = '\xff';
								break;
							}
							v6 += 1;
							v9 = &v9[1];
						} while (v6 < 4);
						fcn_00529160((char*) g_7e4318, 0, v13[-0x5b], 0);
						fcn_004c5c80(v13[-0x5a]);
						v15 = *(unsigned int*) (v5 + 2);
						v14 = *(unsigned int*) (g_7e4318 + 1);
						v5 = v13[-0x5a];
stored:
						fcn_004c5da0(v5, v14, v15, 0, 0, 0);
final:
						v6 = g_7e4318;
					}
				}
			}
			*(char*) &v13[7] = 0;
			v5 = v19;
			v9 = v17;
		}
		v13 = &v13[0x87];
	} while ((int) v13 < 0x85a20c);
	if (v12 != 0) {
		fcn_004c5620(*(unsigned int*) &v12[0x70], v12);
	}
	if (v20 == 0) {
		return;
	}
	fcn_004c5530(msg);
}
