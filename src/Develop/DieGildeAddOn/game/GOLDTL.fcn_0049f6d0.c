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

/* lpGebaeudePROT row (0x24d bytes). */
typedef struct {
	unsigned char type;
	char pad1[0x246];
	unsigned char level;
	char pad248[5];
} GebProt_49f6d0;

extern unsigned char* lpGebaeudePROT;
extern unsigned char* lpGebaeudeINST;

int __cdecl fcn_004eb220(char*);
int __cdecl fcn_00507910(int);
int __cdecl fcn_004a40c0(Calc*);
unsigned short __cdecl gm_RandomMod(int);

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x0049f6d0 */
unsigned int __cdecl ai_StartZunftPreismanipulation(int a0, unsigned short* a1, int* a2, char* a3)
{
	Calc calc[7];
	int matched[7];
	int total[7];
	int ids[7];
	float scores[7];
	unsigned char* ent;
	GebProt_49f6d0* rec;
	int off;
	int i;
	int kind;
	int idx;
	int bit_lo;
	int bit_hi;
	int k;
	int best;
	int tie;
	float score;
	int fn;
	int* fp;

	if (a0 != 0 || a2 != 0)
		return 0;
	if (fcn_004eb220((char*) a1) != 1)
		return 0;
	fn = sizeof(matched);
	fp = matched;
	__asm {
		mov edi, fp
		mov ebx, fn
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L63
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L63:
		add ecx, ebx
		rep stosb
	}
	fn = sizeof(total);
	fp = total;
	__asm {
		mov edi, fp
		mov ebx, fn
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L66
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L66:
		add ecx, ebx
		rep stosb
	}
	fn = sizeof(ids);
	fp = ids;
	__asm {
		mov edi, fp
		mov ebx, fn
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L69
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L69:
		add ecx, ebx
		rep stosb
	}
	for (off = 0; off < 0xa900; off += 0xa9) {
		ent = lpGebaeudeINST + off;
		if (ent[0] == 0)
			continue;
		if (*(unsigned short*) (ent + 0x27) == 0xffff)
			continue;
		idx = ent[0];
		rec = &((GebProt_49f6d0*) lpGebaeudePROT)[idx];
		bit_lo = 0;
		bit_hi = 0;
		if (rec->type > 0x1f)
			bit_hi = 1 << (rec->type - 0x20);
		else
			bit_lo = 1 << rec->type;
		if ((bit_lo & 0x744180) == 0 && (bit_hi & 0) == 0)
			continue;
		kind = fcn_00507910(rec->type);
		if (kind == 0 || kind > 7)
			continue;
		kind--;
		if (*(unsigned short*) (ent + 0x27) == a1[0])
			matched[kind] += rec->level;
		total[kind] += rec->level;
		if (ids[kind] == 0) {
			ids[kind] = idx;
		} else if (((GebProt_49f6d0*) lpGebaeudePROT)[ids[kind]].level < rec->level) {
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
			score = ((float) total[i] + 1.0f - (float) matched[i]) / (float) total[i] *
				((16.0f - (float) matched[i]) * 0.06666667f) *
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
		tie = (gm_RandomMod(4) & 0xffff) - 1;
	if (tie != -1 && tie != 1)
		return 0;
set_result:
	*a3 = 0x15;
	*(int*) (a3 + 4) = k + 1;
	*(int*) (a3 + 0x10) = tie;
	return 0x36;
}
