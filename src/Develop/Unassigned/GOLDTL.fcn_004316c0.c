#include <string.h>

extern double g_6628a0;

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

void __cdecl fcn_00451340(float* a, float* b, float t, float* out);
void __cdecl fcn_00451900(float* a, float* out);
void __cdecl fcn_004519d0(float* a, float* b);
void __cdecl fcn_00438b40(int obj, float* v);
void __cdecl fcn_00438cb0(int obj, float* v);
int __cdecl strcmp(const char* a, const char* b);
char* __cdecl strcpy(char* a, const char* b);

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x004316c0 */
void __cdecl fcn_004316c0(int obj)
{
	PathRec rec[4];
	float left[0xc];
	float right[0xc];
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
		fn = sizeof(rec);
		fd = (char*) rec;
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
		count = 0;
		for (i = 0; i <= 0x173; i += 0x7c) {
			sec = (unsigned char*) plan + i + 0x41c;
			nblock = *(int*) ((char*) plan + i + 0x484);
			if (nblock == 0) {
				continue;
			}
			for (lane = 0; lane < 4; lane++) {
				id = sec[0x78 + lane];
				if (id == 0xff) {
					continue;
				}
				cand = (unsigned char*) (nblock + (id + 1) * 0x40);
				names = (unsigned char*) *(int*) ((char*) plan + 0x40c);
				j = -1;
				for (k = 0; k < count; k++) {
					if (strcmp(rec[k].name, (char*) cand) == 0) {
						j = k;
						break;
					}
				}
				edge = (Edge*) sec;
				node = (int*) *(int*) ((char*) plan + 0x15c);
				if (j < 0) {
					if (count >= 4) {
						continue;
					}
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
					fcn_00451340((float*) ((char*) node + (id + edge->from * 8) * 0x18 + 0x54),
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
					fcn_00451900((float*) ((char*) node + (id + edge->from * 8) * 0x18 + 0x60), left);
					fcn_00451900((float*) ((char*) node + (id + edge->to * 8) * 0x18 + 0x60), right);
					for (k = 0; k < 3; k++) {
						fcn_00451340(left + k * 4, right + k * 4, t, rec[count].mat[k]);
					}
					rec[count].flag = 1;
					count++;
				} else {
					t = (float) edge->weight / *(int*) ((char*) node + edge->from * 0xc0 + 4);
					fcn_00451340((float*) ((char*) node + (id + edge->from * 8) * 0x18 + 0x54),
					    (float*) ((char*) node + (id + edge->to * 8) * 0x18 + 0x54), t, out);
					out[0] -= rec[j].pos[0];
					out[1] -= rec[j].pos[1];
					out[2] -= rec[j].pos[2];
					rec[j].target[0] = edge->k * out[0] + rec[j].target[0];
					rec[j].target[1] = edge->k * out[1] + rec[j].target[1];
					rec[j].target[2] = edge->k * out[2] + rec[j].target[2];
					fcn_00451900((float*) ((char*) node + (id + edge->from * 8) * 0x18 + 0x60), left);
					fcn_00451900((float*) ((char*) node + (id + edge->to * 8) * 0x18 + 0x60), right);
					for (k = 0; k < 3; k++) {
						fcn_00451340(left + k * 4, right + k * 4, t, out);
						rec[j].mat[k][0] = out[0] + rec[j].mat[k][0];
						rec[j].mat[k][1] = out[1] + rec[j].mat[k][1];
						rec[j].mat[k][2] = out[2] + rec[j].mat[k][2];
					}
					rec[j].flag++;
				}
			}
		}
		if (count != 0) {
			for (i = 0; i < count; i++) {
				w = (float) g_6628a0 / (float) rec[i].flag;
				for (k = 0; k < 3; k++) {
					rec[i].mat[k][0] = w * rec[i].mat[k][0];
					rec[i].mat[k][1] = w * rec[i].mat[k][1];
					rec[i].mat[k][2] = w * rec[i].mat[k][2];
				}
				fcn_004519d0(rec[i].mat[0], q);
				for (nblock = *(int*) (obj + 0x200); nblock != 0; nblock = *(int*) (nblock + 0x1f4)) {
					if (*(int*) (nblock + 0x1ec) != 0
					    && strcmp(rec[i].name, (char*) (*(int*) (nblock + 0x1ec) + 0xb4)) == 0) {
						fcn_00438b40(nblock, rec[i].target);
						fcn_00438cb0(nblock, q);
					}
				}
			}
			return;
		}
	}
	names = (unsigned char*) *(int*) ((char*) plan + 0x40c);
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
			fcn_00438b40(nblock, (float*) (names + k * 0x58 + 0xb4));
			fcn_00438cb0(nblock, (float*) (names + k * 0x58 + 0xc0));
		}
	}
}
