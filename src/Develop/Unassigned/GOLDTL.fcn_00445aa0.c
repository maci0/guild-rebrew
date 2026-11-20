char __cdecl fcn_00438b40(char*, float*);
char __cdecl d3_SetObjectRotation(char*, float*);

/* ADDRESS: GOLDTL 0x00445aa0 */
char __cdecl fcn_00445aa0(char* interpObj, unsigned int keyIndex, float keyFraction)
{
	float newPosition[4];
	float newRotation[4];
	char* keyframes;
	float t;
	char* firstFrame;
	char* nextFrame;
	unsigned int idx;
	unsigned int idx2;
	int flag;
	int v4;
	int v5;
	unsigned int i;

	if (interpObj == 0 || keyIndex >= 7 || !(keyFraction >= 0.0f) || !(keyFraction <= 1.0f) || *(int*) (interpObj + 0x218) < 5 || (keyframes = *(char**) (interpObj + 0x1e8)) == 0)
		return 0;
	t = keyFraction + *(float*) (keyframes + 0x1a4);
	if (t > 1.0f) {
		t = t - 1.0f;
		idx = (keyIndex + 1) % 7;
	} else if (t < -1.0f) {
		t = t + 1.0f;
		idx = (keyIndex - 1) % 7;
	} else {
		idx = keyIndex;
	}
	idx2 = (idx + 1) % 7;
	flag = (*(float*) (keyframes + 0x24 + ((idx - 1) % 7) * 0x38) != 0.0f) || (*(int*) (interpObj + 0x218) == 8);
	firstFrame = keyframes + idx * 0x38;
	v4 = 0;
	if (*(float*) (firstFrame + 0x24) != 0.0f || *(int*) (interpObj + 0x218) == 8)
		v4 = 1;
	nextFrame = keyframes + idx2 * 0x38;
	v5 = 0;
	if (*(float*) (nextFrame + 0x24) != 0.0f || *(int*) (interpObj + 0x218) == 8)
		v5 = 1;
	if (flag && v4 && v5) {
		*(float*) (interpObj + 0x94) = (*(float*) (nextFrame + 0x24) - *(float*) (firstFrame + 0x24)) * t + *(float*) (firstFrame + 0x24);
		goto L;
	}
	if (v4 && t < 0.5f) {
		*(int*) (interpObj + 0x94) = *(int*) (firstFrame + 0x24);
		goto L;
	}
	if (v5 && t >= 0.5f)
		*(int*) (interpObj + 0x94) = *(int*) (nextFrame + 0x24);
	else
		*(int*) (interpObj + 0x94) = 0;
L:
	*(float*) (interpObj + 0x90) = (*(float*) (nextFrame + 0x28) - *(float*) (firstFrame + 0x28)) * t + *(float*) (firstFrame + 0x28);
	*(float*) (interpObj + 0x98) = (*(float*) (nextFrame + 0x2c) - *(float*) (firstFrame + 0x2c)) * t + *(float*) (firstFrame + 0x2c);
	for (i = 0; i < 12; i += 4) {
		*(float*) ((char*) newPosition + i) = (*(float*) (nextFrame + i) - *(float*) (firstFrame + i)) * t + *(float*) (firstFrame + i);
		*(float*) (interpObj + 0x5c + i) = (*(float*) (nextFrame + 0x18 + i) - *(float*) (firstFrame + 0x18 + i)) * t + *(float*) (firstFrame + 0x18 + i);
		*(float*) ((char*) newRotation + i) = (*(float*) (nextFrame + 0xc + i) - *(float*) (firstFrame + 0xc + i)) * t + *(float*) (firstFrame + 0xc + i);
	}
	fcn_00438b40(interpObj, newPosition);
	d3_SetObjectRotation(interpObj, newRotation);
	return 1;
}
