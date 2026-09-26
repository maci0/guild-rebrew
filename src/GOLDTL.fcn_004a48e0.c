#include <math.h>
#include <string.h>

extern int g_6b8010;
extern char* g_773d78;

void __cdecl fcn_004432d0(int, int);
int __cdecl fcn_00597ff0(int, char*);
int __cdecl fcn_00598150(char*, char**);
unsigned short __cdecl fcn_0042e410(int);
void __cdecl fcn_00455350(char* src, char* pos, float* out);
float __cdecl gm_RandomFloat01(void);

// FUNCTION: GOLDTL 0x4a48e0
// SIZE: 718

/* Picks one entity of the list the key resolves to: the one nearest (with a
 * random weight) to the owner's or the player's reference entity, else a
 * random non-empty entry. */
char* __cdecl fcn_004a48e0(char* u, int key)
{
	char* list[0x100];
	char text[0x40];
	float p1[4];
	float p2[4];
	float dist;
	float d[4];
	float best;
	float score;
	char* ref;
	char* found;
	int saved;
	int n;
	int i;
	int cnt;

	saved = g_6b8010;
	fcn_004432d0(0, 1);
	if (fcn_00597ff0(key, text) != 0) {
		memset(list, 0, sizeof(list));
		n = fcn_00598150(text, list);
		if (n != 0) {
			if (*(char**) (u + 0x170) != 0 && *(char**) (*(char**) (u + 0x170) + 0x61) != 0 && fcn_0042e410(3) != 0) {
				ref = *(char**) (*(char**) (u + 0x170) + 0x61);
				fcn_00455350(ref, ref + 0x4c, p1);
				found = 0;
				best = 1.00000002e+21f;
				for (i = 0; i < n; i++) {
					if (list[i] != 0) {
						fcn_00455350(list[i], list[i] + 0x4c, p2);
						d[0] = p2[0] - p1[0];
						d[1] = p2[1] - p1[1];
						d[2] = p2[2] - p1[2];
						score = (gm_RandomFloat01() * 0.5f + 0.75f) * (dist = (float) sqrt(d[2] * d[2] + d[1] * d[1] + d[0] * d[0]));
						if (score < best) {
							best = score;
							found = list[i];
						}
					}
				}
				fcn_004432d0(saved, 1);
				return found;
			}
			if (g_773d78 != 0 && *(char**) (g_773d78 + 0x61) != 0) {
				ref = *(char**) (g_773d78 + 0x61);
				fcn_00455350(ref, ref + 0x4c, p1);
				found = 0;
				best = 1.00000002e+21f;
				for (i = 0; i < n; i++) {
					if (list[i] != 0) {
						fcn_00455350(list[i], list[i] + 0x4c, p2);
						d[0] = p2[0] - p1[0];
						d[1] = p2[1] - p1[1];
						d[2] = p2[2] - p1[2];
						score = (gm_RandomFloat01() * 0.5f + 0.75f) * (dist = (float) sqrt(d[2] * d[2] + d[1] * d[1] + d[0] * d[0]));
						if (score < best) {
							best = score;
							found = list[i];
						}
					}
				}
				fcn_004432d0(saved, 1);
				return found;
			}
			cnt = n;
			i = fcn_0042e410(n);
			do {
				if (list[i] != 0) {
					fcn_004432d0(saved, 1);
					return list[i];
				}
				i = (i + 1) % n;
			} while (--cnt != 0);
		}
	}
	fcn_004432d0(saved, 1);
	return 0;
}
