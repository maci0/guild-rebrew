#include <string.h>

extern char g_7f4ca0[];

char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl atoi(char*);
int __cdecl fcn_004ae130(int);
void __cdecl fcn_004c54c0(int, int, int, int);


/* ADDRESS: GOLD 0x004b04a0 */
/* ADDRESS: GOLDTL 0x004b05e0 */
int __cdecl hst_HandleAnsehenBeiAmtstraegern(int* record, int index, char* text)
{
	char* e;
	int n;
	int i;

	if (record == 0 || index >= 8)
		return 0;
	e = gm_LookupEntityRecordById(record[index * 2 + 1]);
	if (e == 0)
		return 0;
	if (*text != '-')
		return 0;
	{
		int sign[2] = { -1, 1 };
		char names[2][6] = { "MINUS", "PLUS" };

		text++;
		for (i = 0; i < 2; i++) {
			if (memcmp(text, names[i], strlen(names[i])) == 0)
				break;
		}
		if (i >= 2)
			return 0;
		text += strlen(names[i]);
		if (*text != '_')
			return 0;
		text++;
		n = atoi(text) * sign[i] * 2;
	}
	for (i = 0; i < 768; i++) {
		if (fcn_004ae130(i) != 0
		    && (g_7f4ca0[i * 540 + 0x166] != 0 || g_7f4ca0[i * 540 + 0x169] != 0))
			fcn_004c54c0(*(int*) (e + 4), *(int*) (g_7f4ca0 + i * 540 + 4), n, 1);
	}
	return 1;
}
