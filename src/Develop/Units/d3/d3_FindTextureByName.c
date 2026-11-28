#include <string.h>

extern char* d3_TextureBank;
extern unsigned int d3_TextureBankCount;

int __cdecl fcn_0065f220(const char* a, const char* b);

/* ADDRESS: GOLDTL 0x0045bde0 */
/* ADDRESS: GOLDDE 0x00450ea0 */
char* __cdecl d3_FindTextureByName(const char* name)
{
	char buf[0x40];
	unsigned int i;
	char* p;

	strcpy(buf, name);
	p = d3_TextureBank;
	for (i = 0; i < d3_TextureBankCount; i++, p += 0x70) {
		if (*(int*) (p + 0x40) > 0 && fcn_0065f220(buf, p) == 0) {
			return p;
		}
	}
	return 0;
}
