


void* __cdecl gm_FindBuildingOwner(void*);
void  __cdecl io_FormatTextBuffer(void*, int, ...);
int   __cdecl fcn_00526120(void*, int);

int __cdecl d2_CheckOwnerBlocked(void* entity)
{
	char buf[0x100];
	void* p;

	p = gm_FindBuildingOwner(entity);
	if (p != 0 && (*(unsigned char*) ((char*) p + 0x1b4) & 1)) {
		io_FormatTextBuffer(buf, 0x78, *(unsigned short*) p);
		fcn_00526120(buf, 0x100);
		return 1;
	}
	return 0;
}
