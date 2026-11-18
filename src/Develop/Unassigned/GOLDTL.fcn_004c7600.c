

extern int g_77494c;

int __cdecl fcn_004c7600(unsigned char* command, char* result)
{
	g_77494c |= command[0x10];
	if (result != 0) {
		*result = 1;
	}
	return 0;
}
