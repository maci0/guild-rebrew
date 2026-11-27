void __cdecl d3_RemoveObjectAnimation(char* sounds, char* name);
/* Inferred views, also evidenced by Gold0x52f740. */
typedef struct GOLD_REFRESH_PAGE { char unknown00[0x68]; char* name; char unknown6c[0x10]; } GOLD_REFRESH_PAGE;
typedef struct GOLD_REFRESH_PAGES { char unknown00[0xf4]; char sounds[0x1c]; GOLD_REFRESH_PAGE pages[3]; } GOLD_REFRESH_PAGES;

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x00411b70 */
int __cdecl d3_RemoveObjectAnim(char* model)
{
	GOLD_REFRESH_PAGES* pages;
	char* name;
	int i;
	for (i = 0; i < 3; i++) {
		pages = *(GOLD_REFRESH_PAGES**) (model + 0x1ec);
		if (pages != 0) {
			name = pages->pages[i].name;
			if (name != 0) d3_RemoveObjectAnimation(pages->sounds, name);
		}
	}
	return 1;
}
#else
/* ADDRESS: GOLDTL 0x00413120 */
int __cdecl d3_RemoveObjectAnim(char* p)
{
	int i;
	char* q;

	for (i = 0; i < 3; i++) {
		q = *(char**) (p + 0x1ec);
		if (q != 0 && *(int*) (q + i * 0x7c + 0x484) != 0) {
			d3_RemoveObjectAnimation(q + 0xf4, (char*) *(int*) (q + i * 0x7c + 0x484));
		}
	}
	return 1;
}
#endif
