#include <string.h>

extern double g_6628a0;

typedef struct PathRec {
	char name[0x40];
	int flag;
	float target[3];
	float pos[3];
	char pad[0x44];
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
	float trail[4][0x29];
	float path[0x8a];
	float left[0xc];
	float right[0xc];
	float out[4];
	float v[3];
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
		memset(rec, 0, sizeof(rec));
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
				names = (unsigned char*) plan + 0x2a0;
				j = -1;
				for (k = 0; k < count; k++) {
					if (strcmp(rec[k].name, (char*) cand) == 0) {
						j = k;
						break;
					}
				}
				if (j < 0) {
					if (count >= 4) {
						continue;
					}
					strcpy(rec[count].name, (char*) cand);
					j = count;
					for (k = 0; k < *names; k++) {
						if (strcmp((char*) plan + 0x74 + k * 0x58, (char*) cand) == 0) {
							rec[j].target[0] = *(float*) ((char*) plan + k * 0x58 + 0xb4);
							rec[j].target[1] = *(float*) ((char*) plan + k * 0x58 + 0xb8);
							rec[j].target[2] = *(float*) ((char*) plan + k * 0x58 + 0xbc);
							break;
						}
					}
					count++;
				}
				edge = (Edge*) (nblock + 0x40 + lane * 0x40);
				node = (int*) *(int*) ((char*) plan + 0x15c);
				t = (float) edge->weight / *(int*) ((char*) node + edge->from * 0xc0 + 4);
				fcn_00451340((float*) ((char*) node + (edge->from * 8 + lane) * 0x18 + 0x54), (float*) ((char*) node + (edge->to * 8 + lane) * 0x18 + 0x54), t, out);
				v[0] = out[0] - rec[j].pos[0];
				v[1] = out[1] - rec[j].pos[1];
				v[2] = out[2] - rec[j].pos[2];
				rec[j].target[0] = edge->k * v[0] + rec[j].pos[0];
				rec[j].target[1] = edge->k * v[1] + rec[j].pos[1];
				rec[j].target[2] = edge->k * v[2] + rec[j].pos[2];
				fcn_00451900((float*) ((char*) node + (edge->from * 8 + lane) * 0x18 + 0x60), left);
				fcn_00451900((float*) ((char*) node + (edge->to * 8 + lane) * 0x18 + 0x60), right);
				for (k = 0; k < 3; k++) {
					fcn_00451340(left + k * 4, right + k * 4, t, out);
					trail[j][k * 4 + 0] = out[0] + trail[j][k * 4 + 0];
					trail[j][k * 4 + 1] = out[1] + trail[j][k * 4 + 1];
					trail[j][k * 4 + 2] = out[2] + trail[j][k * 4 + 2];
					trail[j][k * 4 + 3] = out[3] + trail[j][k * 4 + 3];
				}
				rec[j].flag = 1;
			}
		}
		if (count != 0) {
			for (i = 0; i < count; i++) {
				w = (float) (g_6628a0 / trail[i][0]);
				for (k = 0; k < 3; k++) {
					trail[i][k * 4 + 0] = w * trail[i][k * 4 + 0];
					trail[i][k * 4 + 1] = w * trail[i][k * 4 + 1];
					trail[i][k * 4 + 2] = w * trail[i][k * 4 + 2];
					trail[i][k * 4 + 3] = w * trail[i][k * 4 + 3];
				}
				fcn_004519d0(&rec[i].pos[0], out);
				for (k = 0; k < 4; k++) {
					path[i * 0x29 + k] = trail[i][k];
				}
				for (nblock = *(int*) (obj + 0x200); nblock != 0; nblock = *(int*) (nblock + 500)) {
					if (*(int*) (nblock + 0x1ec) != 0) {
						if (strcmp((char*) (*(int*) (nblock + 0x1ec) + 0xb4), rec[i].name) == 0) {
							fcn_00438b40(nblock, &rec[i].pos[0]);
							fcn_00438cb0(nblock, &path[i * 0x29]);
						}
					}
				}
			}
			return;
		}
	}
	for (nblock = *(int*) (obj + 0x200); nblock != 0; nblock = *(int*) (nblock + 500)) {
		plan = (int*) *(int*) (nblock + 0x1ec);
		if (plan == 0) {
			continue;
		}
		if (*(char*) ((char*) plan + 0xb4) == 0) {
			continue;
		}
		names = (unsigned char*) (*(int*) ((char*) plan + 0x40c) + 0x2a0);
		cand = (unsigned char*) (*(int*) ((char*) plan + 0x40c) + 0x74);
		for (k = 0; k < *names; k++) {
			if (strcmp((char*) cand, (char*) plan + 0xb4) == 0) {
				fcn_00438b40(nblock, (float*) (cand + 0xb4 - 0x74));
				fcn_00438cb0(nblock, (float*) (cand + 0xc0 - 0x74));
				break;
			}
			cand += 0x58;
		}
	}
}
