#include <string.h>



typedef struct PathRec {
	char name[0x40];
	int flag;
	float target[4];
	float pos[4];
	float mat[3][4];
	char pad94[0x10];
} PathRec;
/* SIZE 0xa4 */

typedef struct Edge {
	int from;
	int to;
	int weight;
	char pad[0x34];
	float k;
} Edge;

void __cdecl d3_LerpVec3(float* a, float* b, float t, float* out);
void __cdecl d3_BuildEulerRotationMatrix(float* a, float* out);
void __cdecl d3_MatrixToEulerAngles(float* a, float* b);
void __cdecl d3_SetNodePosition(int obj, float* v);
void __cdecl d3_SetObjectRotation(int obj, float* v);
int __cdecl strcmp(const char* a, const char* b);
char* __cdecl strcpy(char* a, const char* b);

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x004316c0 */
void __cdecl fcn_004316c0(int obj)
{
	PathRec rec[4];
	float left[0xc];
	float right[0x10];
	float out[4];
	float q[4];
	float w;
	float t;
	int* plan;
	int* node;
	unsigned char* sec;
	unsigned char* cand;
	unsigned char* names;
	Edge* edge;
	int nblock;
	int count;
	int lane;
	int i;
	int j;
	int k;
	int id;
	char* fd;
	int fn;

	if (obj == 0) {
		return;
	}
	plan = (int*) *(int*) (obj + 0x1ec);
	if (plan == 0) {
		return;
	}
	if (*(int*) ((char*) plan + 0x40c) == 0) {
		return;
	}
	count = 0;
	if (*(char*) ((char*) plan + 0x594) != 0) {
		fd = (char*) rec;
		fn = sizeof(rec);
		/* Reviewed original operand-homed fill (inline fill/copy block). */
		__asm {
			mov edi, fd
			mov ebx, fn
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L1
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L1:
			add ecx, ebx
			rep stosb
		}
		for (i = 0; i < 0x174; i += 0x7c) {
			sec = (unsigned char*) *(int*) (obj + 0x1ec) + i + 0x41c;
			nblock = *(int*) (sec + 0x68);
			if (nblock == 0) {
				continue;
			}
			for (lane = 0; lane < 4; lane++) {
				id = sec[0x78 + lane];
				if (id == 0xff) {
					continue;
				}
				cand = (unsigned char*) (nblock + (id + 1) * 0x40);
				for (j = 0; j < count; j++) {
					if (strcmp(rec[j].name, (char*) cand) == 0) {
						break;
					}
				}
				edge = (Edge*) sec;
				node = (int*) *(int*) (nblock + 0x15c);
				if (j >= count) {
					if (count >= 4) {
						continue;
					}
					names = (unsigned char*) *(int*) (*(int*) (obj + 0x1ec) + 0x40c);
					strcpy(rec[count].name, (char*) cand);
					for (k = 0; k < names[0x2a0]; k++) {
						if (strcmp((char*) names + 0x74 + k * 0x58, (char*) cand) == 0) {
							rec[count].pos[0] = *(float*) ((char*) names + k * 0x58 + 0xb4);
							rec[count].pos[1] = *(float*) ((char*) names + k * 0x58 + 0xb8);
							rec[count].pos[2] = *(float*) ((char*) names + k * 0x58 + 0xbc);
							break;
						}
					}
					t = (float) edge->weight / *(int*) ((char*) node + edge->from * 0xc0 + 4);
					d3_LerpVec3((float*) ((char*) node + (id + edge->from * 8) * 0x18 + 0x54),
					    (float*) ((char*) node + (id + edge->to * 8) * 0x18 + 0x54), t, out);
					out[0] -= rec[count].pos[0];
					out[1] -= rec[count].pos[1];
					out[2] -= rec[count].pos[2];
					rec[count].target[0] = edge->k * out[0];
					rec[count].target[1] = edge->k * out[1];
					rec[count].target[2] = edge->k * out[2];
					rec[count].target[0] += rec[count].pos[0];
					rec[count].target[1] += rec[count].pos[1];
					rec[count].target[2] += rec[count].pos[2];
					d3_BuildEulerRotationMatrix((float*) ((char*) node + (id + edge->from * 8) * 0x18 + 0x60), left);
					d3_BuildEulerRotationMatrix((float*) ((char*) node + (id + edge->to * 8) * 0x18 + 0x60), right);
					for (k = 0; k < 3; k++) {
						d3_LerpVec3(left + k * 4, right + k * 4, t, rec[count].mat[k]);
					}
					rec[count].flag = 1;
					count++;
				} else {
					t = (float) edge->weight / *(int*) ((char*) node + edge->from * 0xc0 + 4);
					d3_LerpVec3((float*) ((char*) node + (id + edge->from * 8) * 0x18 + 0x54),
					    (float*) ((char*) node + (id + edge->to * 8) * 0x18 + 0x54), t, out);
					out[0] -= rec[j].target[0];
					out[1] -= rec[j].target[1];
					out[2] -= rec[j].target[2];
					rec[j].target[0] = edge->k * out[0] + rec[j].target[0];
					rec[j].target[1] = edge->k * out[1] + rec[j].target[1];
					rec[j].target[2] = edge->k * out[2] + rec[j].target[2];
					d3_BuildEulerRotationMatrix((float*) ((char*) node + (id + edge->from * 8) * 0x18 + 0x60), left);
					d3_BuildEulerRotationMatrix((float*) ((char*) node + (id + edge->to * 8) * 0x18 + 0x60), right);
					for (k = 0; k < 3; k++) {
						d3_LerpVec3(left + k * 4, right + k * 4, t, out);
						rec[j].mat[k][0] = out[0] + rec[j].mat[k][0];
						rec[j].mat[k][1] = out[1] + rec[j].mat[k][1];
						rec[j].mat[k][2] = out[2] + rec[j].mat[k][2];
					}
					rec[j].flag++;
				}
			}
		}
	}
	if (count == 0) {
		names = (unsigned char*) *(int*) (*(int*) (obj + 0x1ec) + 0x40c);
		for (nblock = *(int*) (obj + 0x200); nblock != 0; nblock = *(int*) (nblock + 0x1f4)) {
			cand = (unsigned char*) *(int*) (nblock + 0x1ec);
			if (cand == 0 || cand[0xb4] == 0) {
				continue;
			}
			for (k = 0; k < names[0x2a0]; k++) {
				if (strcmp((char*) names + 0x74 + k * 0x58, (char*) cand + 0xb4) == 0) {
					break;
				}
			}
			if (k < names[0x2a0]) {
				d3_SetNodePosition(nblock, (float*) (names + k * 0x58 + 0xb4));
				d3_SetObjectRotation(nblock, (float*) (names + k * 0x58 + 0xc0));
			}
		}
	} else {
		for (i = 0; i < count; i++) {
			w = 1.0f / (float) rec[i].flag;
			for (k = 0; k < 3; k++) {
				rec[i].mat[k][0] = w * rec[i].mat[k][0];
				rec[i].mat[k][1] = w * rec[i].mat[k][1];
				rec[i].mat[k][2] = w * rec[i].mat[k][2];
			}
			d3_MatrixToEulerAngles(rec[i].mat[0], q);
			for (nblock = *(int*) (obj + 0x200); nblock != 0; nblock = *(int*) (nblock + 0x1f4)) {
				if (*(int*) (nblock + 0x1ec) != 0
				    && strcmp(rec[i].name, (char*) (*(int*) (nblock + 0x1ec) + 0xb4)) == 0) {
					d3_SetNodePosition(nblock, rec[i].target);
					d3_SetObjectRotation(nblock, q);
				}
			}
		}
	}
}
