#include <stdio.h>
#include <string.h>

#include "Develop/DieGildeAddOn/game/game_data.h"


/* Writes the sample bank as text, blanks in names replaced by '~'. */
/* ADDRESS: GOLDTL 0x00425310 */
int __cdecl sbs_WriteSampleBank(const char* file)
{
	int r;
	FILE* fp;
	char* p;
	char* s;
	char* v;

	r = 0;
	if (sbs_BankManager != 0 && (fp = fopen(file, "wt")) != 0) {
		for (p = strstr(sbs_BankManager, " "); p != 0; p = strstr(p, " ")) {
			*p++ = '~';
		}
		fprintf(fp, "%s\n", sbs_BankManager);
		for (s = *(char**) (sbs_BankManager + 0x38); s != 0; s = *(char**) (s + 0x104)) {
			for (p = strstr(s, " "); p != 0; p = strstr(p, " ")) {
				*p++ = '~';
			}
			fprintf(fp, "%s\n", s);
		}
		fprintf(fp, "{EndOfSamples}");
		for (v = *(char**) (sbs_BankManager + 0x3c); v != 0; v = *(char**) (v + 0x3c)) {
			for (p = strstr(v, " "); p != 0; p = strstr(p, " ")) {
				*p++ = '~';
			}
			fprintf(fp, "%s\n", v);
			for (s = *(char**) (v + 0x38); s != 0; s = *(char**) (s + 0x104)) {
				for (p = strstr(s, " "); p != 0; p = strstr(p, " ")) {
					*p++ = '~';
				}
				fprintf(fp, "%s\n", s);
			}
			fprintf(fp, "{EndOfVariation}");
		}
		fprintf(fp, "{EndOfSampleBank}");
		fclose(fp);
		g_6b7d6c = 0;
	} else {
		r = -1;
	}
	return r;
}
