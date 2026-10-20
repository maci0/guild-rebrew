char __cdecl fcn_00438b40(char*, float*);
char __cdecl fcn_00438cb0(char*, float*);

/* ADDRESS: GOLDTL 0x00445aa0 */
char __cdecl fcn_00445aa0(char* a0, unsigned int a1, float a2)
{
	float v14[4];
	float v15[4];
	int size;
	char* v3;
	float t;
	char* v1;
	char* v2;
	int v4;
	int v5;
	int flag;
	int i;
	unsigned int idx;
	unsigned int idx2;

	if (a0 == 0)
		return 0;
	if (a1 >= 7)
		return 0;
	if (a2 < 0.0f)
		return 0;
	if (!(a2 <= 1.0f))
		return 0;
	size = *(int*) (a0 + 0x218);
	if (size < 5)
		return 0;
	v3 = (char*) *(int*) (a0 + 0x1e8);
	if (v3 == 0)
		return 0;
	t = a2 + *(float*) (v3 + 0x1a4);
	if (t <= 1.0f) {
		idx = a1;
		if (t < -1.0f) {
			t = t + 1.0f;
			idx = (a1 - 1) % 7;
		}
	} else {
		t = t - 1.0f;
		idx = (a1 + 1) % 7;
	}
	idx2 = (idx + 1) % 7;
	v1 = v3 + idx * 0x38;
	v2 = v3 + idx2 * 0x38;
	flag = (*(float*) (v3 + 0x24 + ((idx + 6) % 7) * 0x38) != 0.0f) || (size == 8);
	v4 = (*(float*) (v1 + 0x24) != 0.0f) || (size == 8);
	v5 = (*(float*) (v2 + 0x24) != 0.0f) || (size == 8);
	if (flag && v4 && v5) {
		*(float*) (a0 + 0x94) = (*(float*) (v2 + 0x24) - *(float*) (v1 + 0x24)) * t + *(float*) (v1 + 0x24);
		goto L;
	}
	if (v4 && t < 0.5f) {
		*(int*) (a0 + 0x94) = *(int*) (v1 + 0x24);
		goto L;
	}
	if (v5 && t >= 0.5f)
		*(int*) (a0 + 0x94) = *(int*) (v2 + 0x24);
	else
		*(int*) (a0 + 0x94) = 0;
L:
	*(float*) (a0 + 0x90) = (*(float*) (v2 + 0x28) - *(float*) (v1 + 0x28)) * t + *(float*) (v1 + 0x28);
	*(float*) (a0 + 0x98) = (*(float*) (v2 + 0x2c) - *(float*) (v1 + 0x2c)) * t + *(float*) (v1 + 0x2c);
	for (i = 0; i < 3; i++) {
		v14[i] = (*(float*) (v2 + i * 4) - *(float*) (v1 + i * 4)) * t + *(float*) (v1 + i * 4);
		*(float*) (a0 + 0x5c + i * 4) = (*(float*) (v2 + 0x18 + i * 4) - *(float*) (v1 + 0x18 + i * 4)) * t + *(float*) (v1 + 0x18 + i * 4);
		v15[i] = (*(float*) (v2 + 8 + i * 4) - *(float*) (v1 + 8 + i * 4)) * t + *(float*) (v1 + 8 + i * 4);
	}
	fcn_00438b40(a0, v14);
	fcn_00438cb0(a0, v15);
	return 1;
}
