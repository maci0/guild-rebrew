

extern int g_77494c;

int __cdecl cm_OrCommandFlags(unsigned char* command, char* result)
{
	g_77494c |= command[0x10];
	if (result != 0) {
		*result = 1;
	}
	return 0;
}
