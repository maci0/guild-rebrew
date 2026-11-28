

extern int nt_NetSyncFlags;

/* ADDRESS: GOLDDE 0x004b4de0 */
int __cdecl cm_OrCommandFlags(unsigned char* command, char* result)
{
	nt_NetSyncFlags |= command[0x10];
	if (result != 0) {
		*result = 1;
	}
	return 0;
}
