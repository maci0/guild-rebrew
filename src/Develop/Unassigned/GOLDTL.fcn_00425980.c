#include <string.h>

#include "Develop/DieGildeAddOn/game/game_data.h"

char* __cdecl sbs_GetFirstRootSample(char* dst, int n);
char* __cdecl sbs_GetNextSample(char* p, char* dst, int n);
char* __cdecl sbs_GetFirstSet(char* dst, int n);
char* __cdecl sbs_GetFirstSetSample(char* dir, char* dst, int n);
char* __cdecl sbs_GetNextSet(char* p, char* dst, int n);
int __cdecl sbs_GetFileSize(char* name);


/* Loads every sample of the bank, substituting the language for "%lang". */
/* ADDRESS: GOLDTL 0x00425980 */
int __cdecl sbs_UpdateSampleSizes(char* lang)
{
	char* v;
	char name[0x100];
	char vname[0x100];
	char* s;
	char* p;

	if (sbs_BankManager != 0) {
		s = sbs_GetFirstRootSample(name, 0x100);
		*(int*) (sbs_BankManager + 0x34) = 0;
		while (s != 0) {
			p = strstr(name, "%lang");
			if (p != 0) {
				*p = 0;
				strcat(name, lang);
				strcat(name, s + (p - name) + 5);
			}
			*(int*) (s + 0x100) = sbs_GetFileSize(name);
			if (*(int*) (s + 0x100) == 0) {
				return -1;
			}
			*(int*) (sbs_BankManager + 0x34) += *(int*) (s + 0x100);
			s = sbs_GetNextSample(s, name, 0x100);
		}
		for (v = sbs_GetFirstSet(vname, 0x100); v != 0; v = sbs_GetNextSet(v, vname, 0x100)) {
			s = sbs_GetFirstSetSample(vname, name, 0x100);
			*(int*) (v + 0x34) = 0;
			while (s != 0) {
				p = strstr(name, "%lang");
				if (p != 0) {
					*p = 0;
					strcat(name, lang);
					strcat(name, s + (p - name) + 5);
				}
				*(int*) (s + 0x100) = sbs_GetFileSize(name);
				if (*(int*) (s + 0x100) == 0) {
					return -1;
				}
				*(int*) (sbs_BankManager + 0x34) += *(int*) (s + 0x100);
				*(int*) (v + 0x34) += *(int*) (s + 0x100);
				s = sbs_GetNextSample(s, name, 0x100);
			}
		}
		return 0;
	}
	return -1;
}
