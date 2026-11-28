#include <stdio.h>

#ifndef REBREW_GOLD
extern char str_he_AllocNone_Invalid_HE_Type[];
extern char gm_EntityNameField[];
#endif

void __cdecl he_AllocNone(void* a1)
{
	char buf[0x100];
	unsigned int idx;

	idx = *(unsigned short*) ((char*) a1 + 8);
#ifdef REBREW_GOLD
	sprintf(buf, (const char*) 0x626680, *(unsigned char*) a1, (char*) 0x770bb0 + idx * 0x21c);
#else
	sprintf(buf, str_he_AllocNone_Invalid_HE_Type, *(unsigned char*) a1, gm_EntityNameField + idx * 0x21c);
#endif
}
