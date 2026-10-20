#include <string.h>

/* SIZE 0xb4; recipe calculation record (see fcn_004a40c0). */
typedef struct Calc {
	int id;
	int count;
	int goods[10];
	int need[10];
	int price[10];
	float ratio[10];
	float avg;
	int best;
	int worst;
} Calc;

extern char* g_entity_type_table;
extern unsigned char g_90e094[];

int __cdecl fcn_004eb220(char*);
int __cdecl fcn_00507910(int);
int __cdecl fcn_004a40c0(Calc*);
int __cdecl fcn_0042e410(int);

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x0049f6d0 */
unsigned int __cdecl fcn_0049f6d0(int a0, unsigned short* a1, int* a2, char* a3)
{
	Calc calc[7];
	int matched[7];
	int total[7];
	int ids[7];
	float scores[7];
	unsigned char* ent;
	unsigned char* rec;
	int off;
	int i;
	int kind;
	int idx;
	int bit;
	int k;
	int best;
	int tie;
	float score;

	if (a0 != 0 || a2 != 0)
		return 0;
	if (fcn_004eb220((char*) a1) != 1)
		return 0;
	memset(matched, 0, sizeof(matched));
	memset(total, 0, sizeof(total));
	memset(ids, 0, sizeof(ids));
	for (off = 0; off < 0xa900; off += 0xa9) {
		ent = g_90e094 + off;
		if (ent[0] == 0)
			continue;
		if (*(unsigned short*) (ent + 0x27) == 0xffff)
			continue;
		idx = ent[0];
		rec = (unsigned char*) (g_entity_type_table + idx * 0x24d);
		if (rec[0] < 0x20)
			bit = 1 << (rec[0] & 0x1f);
		else
			bit = 1 << ((rec[0] - 0x20) & 0x1f);
		if ((bit & 0x744180) == 0)
			continue;
		kind = fcn_00507910(rec[0]);
		if (kind == 0 || kind > 7)
			continue;
		kind--;
		if (*(unsigned short*) (ent + 0x27) == a1[0])
			matched[kind] += rec[0x247];
		total[kind] += rec[0x247];
		if (ids[kind] == 0) {
			ids[kind] = idx;
		} else if (g_entity_type_table[ids[kind] * 0x24d + 0x247] < rec[0x247]) {
			ids[kind] = idx;
		}
	}
	k = -1;
	best = -1;
	for (i = 0; i < 7; i++) {
		int count;
		int need;
		int have;

		scores[i] = -1.0f;
		calc[i].id = ids[i];
		calc[i].count = 0;
		count = total[i];
		if (count > 0xf)
			count = 0xf;
		have = matched[i];
		if (have > 0xf)
			have = 0xf;
		total[i] = count;
		matched[i] = have;
		if (count >= 1 && fcn_004a40c0(&calc[i])) {
			score = (16.0f - (float) matched[i]) * 0.06666667f *
				(((float) total[i] + 1.0f) - (float) matched[i]) / (float) total[i] *
				calc[i].avg;
			scores[i] = score;
			if (k != -1) {
				if (score < scores[k])
					k = 1;
			} else {
				k = i;
			}
			if (best == -1 || scores[best] < score)
				best = i;
		}
	}
	if (k == -1 || best == -1 || k == best)
		return 0;
	tie = 0;
	if (calc[k].avg > 1.0f || matched[k] == 0) {
		if (calc[best].avg < 1.0f)
			return 0;
		if (matched[best] * 2 + 1 >= total[best])
			return 0;
		tie = -1;
	}
	if (calc[best].avg < 1.0f)
		goto check_target;
	if (matched[best] * 2 + 1 < total[best])
		goto random_tie;
check_target:
	if (calc[k].avg > 1.0f)
		return 0;
	if (matched[k] == 0)
		return 0;
	tie = 1;
	goto set_result;
random_tie:
	if (tie == 0)
		tie = (fcn_0042e410(4) & 0xffff) - 1;
	if (tie != -1 && tie != 1)
		return 0;
set_result:
	*a3 = 0x15;
	*(int*) (a3 + 4) = k + 1;
	*(int*) (a3 + 0x10) = tie;
	return 0x36;
}
