typedef struct Query_4522a0 {
	char* ref;
	unsigned int count;
	char** list;
	unsigned char flag;
} Query_4522a0;

void __cdecl d3_NormalizeVector(float* v);
void __cdecl d3_CalculateTriangleNormal(float* a, float* b, float* c, float* n);
void __cdecl fcn_00458d90(char* source, char* view, int flags, float* out);

/* ADDRESS: GOLD 0x004522a0 */
char __cdecl fcn_004522a0(char* o, Query_4522a0* q)
{
	int* mesh;
	unsigned int i;
	unsigned int sunStart;
	int j;
	char* light;
	float* vert;
	float* normSrc;
	char* ltBase;
	float* face;
	float falloff;
	float intensity;
	float radiusSq;
	float distSq;
	float dot;
	float att;
	float invScale;
	float minY;
	int idx;
	float vec[3];
	float delta[3];
	float mat[16];
	float lt[3];
	float accum[3];
	float triNorm[3];

	mesh = *(int**) (o + 0x1cc);
	if (mesh == 0) {
		return 1;
	}
	for (i = 0; i < q->count; i++) {
		light = q->list[i];
		if (*(int*) (light + 0x218) == 7) {
			continue;
		}
		falloff = *(float*) (light + 0x98);
		intensity = *(float*) (*(char**) (o + 0x1ec) + 0x958) * *(float*) (light + 0x94) * 10.0f;
		radiusSq = *(float*) (light + 0x90) * *(float*) (light + 0x90);
		if (q->flag != 0) {
			vert = (float*) mesh[0];
			for (j = 0; j < mesh[2]; j++, vert += 20) {
				vec[0] = vert[0] - *(float*) (light + 0x1d8);
				vec[1] = vert[1] - *(float*) (light + 0x1dc);
				vec[2] = vert[2] - *(float*) (light + 0x1e0);
				distSq = vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2];
				if (distSq < radiusSq) {
					d3_NormalizeVector(vec);
					dot = vec[0] * vert[8] + vec[1] * vert[9] + vec[2] * vert[10];
					if (dot < 0.0) {
						idx = (int) (dot * -1023.0f);
						att = (1.0f / (distSq * falloff)) * intensity * ((float*) 0xfb9940)[idx];
						delta[0] = att * *(float*) (light + 0x5c);
						delta[1] = att * *(float*) (light + 0x60);
						delta[2] = att * *(float*) (light + 0x64);
						vert[12] += delta[0];
						vert[13] += delta[1];
						vert[14] += delta[2];
					}
				}
			}
		} else {
			vert = (float*) mesh[0];
			for (j = 0; j < mesh[2]; j++, vert += 20) {
				vec[0] = vert[0] - *(float*) (light + 0x1d8);
				vec[1] = vert[1] - *(float*) (light + 0x1dc);
				vec[2] = vert[2] - *(float*) (light + 0x1e0);
				distSq = vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2];
				if (distSq < radiusSq) {
					att = (1.0f / (distSq * falloff)) * intensity;
					delta[0] = att * *(float*) (light + 0x5c);
					delta[1] = att * *(float*) (light + 0x60);
					delta[2] = att * *(float*) (light + 0x64);
					vert[12] += delta[0];
					vert[13] += delta[1];
					vert[14] += delta[2];
				}
			}
		}
	}
	for (sunStart = 0; sunStart < q->count; sunStart++) {
		if (*(int*) (q->list[sunStart] + 0x218) == 7) {
			break;
		}
	}
	if (sunStart >= q->count) {
		return 1;
	}
	if (*(int*) (o + 0x220) == 1) {
		fcn_00458d90(o, (*(unsigned char*) (o + 0x210) & 0x80) ? 0 : *(char**) 0xfc2dec, 1, mat);
		invScale = 20.0f / *(float*) (mesh[4] + 0x1d4);
		minY = *(float*) (mesh[4] + 0x6c);
		for (i = sunStart; i < q->count; i++) {
			light = q->list[i];
			if (*(int*) (light + 0x218) != 7) {
				continue;
			}
			intensity = *(float*) (*(char**) (o + 0x1ec) + 0x958) * *(float*) (light + 0x94) * 0.01f;
			lt[0] = *(float*) (*(char**) (light + 0x1e8) + 0x188);
			lt[1] = *(float*) (*(char**) (light + 0x1e8) + 0x18c);
			lt[2] = *(float*) (*(char**) (light + 0x1e8) + 0x190);
			vert = (float*) mesh[0] + 12;
			for (j = 0; j < mesh[2]; j++, vert += 20) {
				normSrc = *(float**) (vert + 6);
				vec[0] = normSrc[0];
				vec[1] = normSrc[1];
				vec[2] = normSrc[2];
				vec[1] = (vec[1] - minY) * invScale;
				delta[0] = mat[0] * vec[0] + mat[4] * vec[1] + mat[8] * vec[2];
				delta[1] = mat[1] * vec[0] + mat[5] * vec[1] + mat[9] * vec[2];
				delta[2] = mat[2] * vec[0] + mat[6] * vec[1] + mat[10] * vec[2];
				d3_NormalizeVector(delta);
				dot = delta[0] * lt[0] + delta[1] * lt[1] + delta[2] * lt[2];
				if (dot < 0.0) {
					idx = (int) (dot * -1023.0f);
					att = intensity * ((float*) 0xfb9940)[idx];
					vert[0] += att * *(float*) (light + 0x5c);
					vert[1] += att * *(float*) (light + 0x60);
					vert[2] += att * *(float*) (light + 0x64);
				}
			}
		}
	} else {
		face = (float*) mesh[1];
		for (j = 0; j < mesh[3]; j++, face += 10) {
			d3_CalculateTriangleNormal(*(float**) face, *(float**) (face + 1), *(float**) (face + 2), triNorm);
			accum[0] = 0.0f;
			accum[1] = 0.0f;
			accum[2] = 0.0f;
			for (i = sunStart; i < q->count; i++) {
				light = q->list[i];
				if (*(int*) (light + 0x218) == 7) {
					ltBase = *(char**) (light + 0x1e8);
					intensity = *(float*) (*(char**) (o + 0x1ec) + 0x958) * *(float*) (light + 0x94) * 0.001f;
					dot = triNorm[0] * *(float*) (ltBase + 0x188) + triNorm[1] * *(float*) (ltBase + 0x18c) + triNorm[2] * *(float*) (ltBase + 0x190);
					if (dot < 0.0f) {
						idx = (int) (dot * -1023.0f);
						att = intensity * ((float*) 0xfb9940)[idx];
						accum[0] += att * *(float*) (light + 0x5c);
						accum[1] += att * *(float*) (light + 0x60);
						accum[2] += att * *(float*) (light + 0x64);
					}
				}
			}
			for (i = 0; i < 3; i++) {
				*(float*) (*(char**) (face + i) + 0x30) += accum[0];
				*(float*) (*(char**) (face + i) + 0x34) += accum[1];
				*(float*) (*(char**) (face + i) + 0x38) += accum[2];
			}
		}
	}
	return 1;
}
