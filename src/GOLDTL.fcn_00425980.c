#include <string.h>

extern char* g_6b7d68;

char* __cdecl fcn_00424760(char* dst, int n);
char* __cdecl fcn_00424790(char* p, char* dst, int n);
char* __cdecl fcn_00424810(char* dst, int n);
char* __cdecl fcn_004247c0(char* dir, char* dst, int n);
char* __cdecl fcn_00424840(char* p, char* dst, int n);
int __cdecl fcn_00423920(char* name);

/* ADDRESS: GOLDTL 0x00425980 */

/* Loads every sample of the bank, substituting the language for "%lang". */
int __cdecl fcn_00425980(char* lang)
{
	char* v;
	char name[0x100];
	char vname[0x100];
	char* s;
	char* p;

	if (g_6b7d68 != 0) {
		s = fcn_00424760(name, 0x100);
		*(int*) (g_6b7d68 + 0x34) = 0;
		while (s != 0) {
			p = strstr(name, "%lang");
			if (p != 0) {
				*p = 0;
				strcat(name, lang);
				strcat(name, s + (p - name) + 5);
			}
			*(int*) (s + 0x100) = fcn_00423920(name);
			if (*(int*) (s + 0x100) == 0) {
				return -1;
			}
			*(int*) (g_6b7d68 + 0x34) += *(int*) (s + 0x100);
			s = fcn_00424790(s, name, 0x100);
		}
		for (v = fcn_00424810(vname, 0x100); v != 0; v = fcn_00424840(v, vname, 0x100)) {
			s = fcn_004247c0(vname, name, 0x100);
			*(int*) (v + 0x34) = 0;
			while (s != 0) {
				p = strstr(name, "%lang");
				if (p != 0) {
					*p = 0;
					strcat(name, lang);
					strcat(name, s + (p - name) + 5);
				}
				*(int*) (s + 0x100) = fcn_00423920(name);
				if (*(int*) (s + 0x100) == 0) {
					return -1;
				}
				*(int*) (g_6b7d68 + 0x34) += *(int*) (s + 0x100);
				*(int*) (v + 0x34) += *(int*) (s + 0x100);
				s = fcn_00424790(s, name, 0x100);
			}
		}
		return 0;
	}
	return -1;
}
