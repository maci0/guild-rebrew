#include <stdlib.h>
#include <string.h>

extern int ai_FeudTargetEntity;

unsigned short __cdecl gm_RandomMod(unsigned short);
int __cdecl gm_MatchesTargetFilter(unsigned short, unsigned short, void*, int);
float __cdecl gm_CalcEntityFavor(unsigned int, unsigned int, unsigned int);
int __cdecl amt_GetRoleLevel(int);

/* ADDRESS: GOLDTL 0x004a5c40 */
unsigned int __cdecl ai_CollectEligibleEntities(unsigned short* source, unsigned int count, unsigned int actionKind,
				  float minFavor, float maxFavor, int range, unsigned short* out)
{
	unsigned int query[20];
	int step;
	int base;
	int checkFavor;
	unsigned int have;
	unsigned int tries;
	int cand;
	int hit;
	int diff;
	float favor;

	step = *(int*) ((gm_RandomMod(0x10) & 0xffff) * 4 + 0x664398);
	memset(query, 0, 0x50);
	memset((char*) query + 0x1c, 0xff, 0x20);
	*(int*) ((char*) query + 0x14) = 2;
	checkFavor = 0;
	have = 0;
	if (ai_FeudTargetEntity != 0) {
		query[1] = actionKind;
		query[16] = 0;
		if (gm_MatchesTargetFilter(*source, *(unsigned short*) ai_FeudTargetEntity, query, 0) != 0) {
			have = 1;
			*out = *(unsigned short*) ai_FeudTargetEntity;
		}
	}
	if ((minFavor > *(double*) 0x662950 || maxFavor < *(double*) 0x662c38) && minFavor < maxFavor) {
		checkFavor = 1;
	}
	base = amt_GetRoleLevel(*(unsigned char*) ((char*) source + 0x166));
	if (have < count) {
		do {
			query[1] = actionKind;
			if (have != 0) {
				*(unsigned short*) ((char*) query + 0x1c + have * 2) = out[have - 1];
			} else {
				*(unsigned short*) ((char*) query + 0x1c) = *source;
			}
			tries = 0x300;
			hit = 0;
			cand = gm_RandomMod(0x300);
			for (; hit == 0; tries--, cand = (cand + step) % 0x300) {
				if (tries == 0) {
					break;
				}
				if (gm_MatchesTargetFilter(*source, cand, query, 0) != 0) {
					if (checkFavor != 0) {
						favor = gm_CalcEntityFavor(cand, *source, 1);
						if (favor < minFavor || favor > maxFavor) {
							continue;
						}
					}
					diff = abs(base - amt_GetRoleLevel(
								     *(unsigned char*) (cand * 0x21c +
										0x7f4e06)));
					if (diff <= range) {
						hit = 1;
						out[have] = cand;
					}
				}
			}
			if (hit == 0) {
				return have;
			}
			have++;
		} while (have < count);
	}
	return have;
}
