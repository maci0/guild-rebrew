#include <stdio.h>

#ifndef REBREW_GOLD
extern char g_6a56d0[];
extern char g_7f4cd0[];
#endif

void __cdecl he_AllocNone(void* a1)
{
	char buf[0x100];
	unsigned int idx;

	idx = *(unsigned short*) ((char*) a1 + 8);
#ifdef REBREW_GOLD
	sprintf(buf, (const char*) 0x626680, *(unsigned char*) a1, (char*) 0x770bb0 + idx * 0x21c);
#else
	sprintf(buf, g_6a56d0, *(unsigned char*) a1, g_7f4cd0 + idx * 0x21c);
#endif
}
