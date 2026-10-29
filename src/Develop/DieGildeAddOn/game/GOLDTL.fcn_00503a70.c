#include <string.h>

int __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_00503d10(int);
int __cdecl fcn_0050dfd0(int, int);
int __cdecl gm_GetMsgField(int, int);
float __cdecl fcn_0050bb50(int, int);

/* ADDRESS: GOLDTL 0x00503a70 */
int __cdecl fcn_00503a70(int a0)
{
	char* p;
	int count;
	int n;
	int v3;
	int v4;
	int v5;
	int v6;
	int v7;
	int v8;
	int v9;
	int v10;
	int t;
	float f;
	int tmp[6];

	if (!*(int*) 0x868050) {
		return 1;
	}
	*(int*) 0x86805c = 0;
	n = 0x58;
	p = (char*) *(int*) 0x90e094;
	do {
		v5 = a0;
		if (*p) {
			v4 = 0;
			count = *(int*) 0x86805c * 0x18;
			*(int*) (count + 0x868c40) = 0;
			*(int*) (count + 0x868c48) = 0;
			*(int*) (count + 0x868c54) = 0;
			if (p != (char*) *(int*) 0x773d78) {
				v7 = fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0xff);
				if (v7) {
					v7 = fcn_00502cd0(*(int*) (v7 + 0x14), 1, 0, a0, 0);
					if (v7) {
						v4 = 1;
						*(char**) (*(int*) 0x86805c * 0x18 + 0x868c40) = p;
						*(int*) (*(int*) 0x86805c * 0x18 + 0x868c54) = 1;
					}
				}
				v6 = fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x2a);
				if (v6) {
					v7 = fcn_00502cd0(*(int*) (v6 + 0x14), 1, 0, a0, 0);
					if (v7) {
						count = *(int*) 0x86805c * 0x18;
						*(char**) (count + 0x868c40) = p;
						*(int*) (count + 0x868c44) = v6;
						*(void**) (count + 0x868c48) = (void*) v7;
						v3 = *(unsigned short*) v7;
						goto add;
					}
				}
				if (v4) {
					*(int*) 0x86805c = *(int*) 0x86805c + 1;
				}
			}
			else {
				v6 = fcn_00503d10(a0);
				if (v6) {
					v7 = fcn_00502cd0(*(int*) (v6 + 0x14), 1, 0, v5, 0);
					if (v7) {
						count = *(int*) 0x86805c * 0x18;
						*(char**) (count + 0x868c40) = p;
						*(int*) (count + 0x868c44) = v6;
						*(void**) (count + 0x868c48) = (void*) v7;
						v3 = *(unsigned short*) v7;
add:
						v8 = fcn_0050dfd0(v6, v3);
						v9 = gm_GetMsgField(v6, v7);
						t = *(int*) (v7 + 0x1c);
						v9 = v9 - (unsigned int) ((v8 * t) >> 2);
						*(int*) (*(int*) 0x86805c * 0x18 + 0x868c4c) = v9;
						if ((int) v9 < 0) {
							v9 = 0;
						}
						*(int*) (*(int*) 0x86805c * 0x18 + 0x868c4c) = v9;
						*(int*) 0x86805c = *(int*) 0x86805c + 1;
					}
				}
			}
		}
		p += 0xa9;
		n--;
		if (!n) {
			break;
		}
	} while (1);
	count = *(int*) 0x86805c;
	v6 = 0;
	if (count > 0) {
		p = (char*) 0x868c50;
		do {
			f = fcn_0050bb50(a0, *(unsigned char*) 0x773d75);
			v6++;
			*(float*) p = f * *(float*) (*(int*) (p - 0x10) + 0x49);
			p += 0x18;
		} while (v6 < *(int*) 0x86805c);
	}
	if (count <= 0) {
		return 0;
	}
	v4 = 1;
	v5 = 0;
	do {
		if (v4 < count) {
			v7 = v5 + 0x868c58;
			n = count - v4;
			do {
				if (*(float*) (v5 + 0x868c50) < *(float*) (v7 + 0x10)) {
					memcpy(tmp, (void*) (v5 + 0x868c40), 0x18);
					memcpy((void*) (v5 + 0x868c40), (void*) v7, 0x18);
					memcpy((void*) v7, tmp, 0x18);
				}
				v7 += 0x18;
				n--;
			} while (n);
		}
		v4++;
		v5 += 0x18;
	} while (v4 - 1 < count);
	return 0;
}
