#include <stdio.h>
#include <string.h>

extern char* g_6b7d68;
extern int g_6b7d6c;

// FUNCTION: GOLDTL 0x425310

/* Writes the sample bank as text, blanks in names replaced by '~'. */
int __cdecl fcn_00425310(const char* file)
{
	int r;
	FILE* fp;
	char* p;
	char* s;
	char* v;

	r = 0;
	if (g_6b7d68 != 0 && (fp = fopen(file, "wt")) != 0) {
		for (p = strstr(g_6b7d68, " "); p != 0; p = strstr(p, " ")) {
			*p++ = '~';
		}
		fprintf(fp, "%s\n", g_6b7d68);
		for (s = *(char**) (g_6b7d68 + 0x38); s != 0; s = *(char**) (s + 0x104)) {
			for (p = strstr(s, " "); p != 0; p = strstr(p, " ")) {
				*p++ = '~';
			}
			fprintf(fp, "%s\n", s);
		}
		fprintf(fp, "{EndOfSamples}");
		for (v = *(char**) (g_6b7d68 + 0x3c); v != 0; v = *(char**) (v + 0x3c)) {
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
