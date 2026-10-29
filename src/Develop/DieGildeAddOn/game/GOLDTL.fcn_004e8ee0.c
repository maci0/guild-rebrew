// SIZE 0x18
typedef struct {
	unsigned char id;
	char pad1[3];
	int holder;
	unsigned char type;
	char pad9[3];
	int count;
	unsigned char state;
	char pad11[7];
} Slot;

// SIZE 0x18
typedef struct {
	int x0;
	int x4;
	unsigned char rank;
	char pad9[15];
} Tmpl;

// SIZE 0xc
typedef struct {
	int type;
	float score;
	unsigned char rank;
	char pad9[3];
} Pick;

#include "client_types.h"
extern Rec18_68da68 g_9a9220[42];
extern Rec18_68da68 g_68da68[];

#include "Develop/DieGildeAddOn/game/aemter.h"


/* ADDRESS: GOLDTL 0x004e8ee0 */
int __cdecl fcn_004e8ee0(char* who, int n, Pick* picks, int* full_out)
{
	int count;
	int len;
	int i;
	int j;
	int k;
	int t;
	int better;
	int full;

	count = 0;
	full = 0;
	if (n <= 0)
		return 0;
	len = n * 4;
	__asm {
		mov edi, picks
		mov ebx, len
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
	for (j = n - 1; j >= 0; j--) {
		picks[j].score = -100.0f;
		picks[j].type = 0;
		picks[j].rank = 0;
	}
	for (i = 0; i < 30; i++) {
		float score;

		if (((Slot*)g_9a9220)[i].state != 3)
			continue;
		t = ((Slot*)g_9a9220)[i].type;
		if (amt_GetOfficeAffinity((unsigned char*) who, t, &score) == 0)
			continue;
		if (((Slot*)g_9a9220)[i].count >= 4) {
			full = 1;
			continue;
		}
		better = 0;
		for (j = n - 1; j >= 0; j--) {
			if (better)
				break;
			if (picks[j].type == t)
				better = 1;
		}
		if (better)
			continue;
		better = 0;
		for (j = n - 1; j >= 0; j--) {
			if (picks[j].rank < ((Tmpl*)g_68da68)[t].rank)
				continue;
			if (picks[j].rank != ((Tmpl*)g_68da68)[t].rank || !(picks[j].score <= score)) {
				better = 1;
				break;
			}
		}
		if (j == -1) {
			j = 0;
			if (picks[0].rank < ((Tmpl*)g_68da68)[t].rank ||
			    (picks[0].rank == ((Tmpl*)g_68da68)[t].rank && picks[0].score <= score))
				better = 1;
		}
		if (better) {
			count++;
			for (k = n - 1; k > j; k--) {
				picks[k].rank = picks[k - 1].rank;
				picks[k].score = picks[k - 1].score;
				picks[k].type = picks[k - 1].type;
			}
			picks[j].rank = ((Tmpl*)g_68da68)[((Slot*)g_9a9220)[i].type].rank;
			picks[j].score = score;
			picks[j].type = ((Slot*)g_9a9220)[i].type;
		}
	}
	if (full_out != 0)
		*full_out = full;
	if (count < n)
		return count;
	return n;
}
