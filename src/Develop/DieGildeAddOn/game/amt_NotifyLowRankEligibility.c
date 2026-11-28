char str_fmt_s_dollar_A[] = "%s$A";
extern char str_fmt_s_dollar_A[];



#include <string.h>

int __cdecl amt_SelectOfficeCandidates(void*, int, void*);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);

void __cdecl amt_NotifyLowRankEligibility(void* entity)
{
	char items[0x48];
	char buf[0x800];
	int n;
	int i;

	if (*(unsigned char*) ((char*) entity + 0xd) < 2) {
		return;
	}
	n = amt_SelectOfficeCandidates(entity, 6, items);
	if (n == 0) {
		return;
	}
	memset(buf, 0, 0x800);
	io_FormatTextBuffer(buf, 0x13ac);
	if (n > 0) {
		for (i = 0; i < n; i++) {
			io_FormatTextBuffer(buf + strlen(buf), (int) str_fmt_s_dollar_A,
			    *(int*) (items + i * 0xc) + 0x253);
		}
	}
	he_PostEntityMessage(*(int*) ((char*) entity + 4), -1, buf, 1, 0x5ec, (void*) 0);
}
