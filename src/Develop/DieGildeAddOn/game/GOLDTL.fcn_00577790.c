extern char g_6a7e90[];

void* __cdecl gm_LookupEntityRecordById(int);
void  __cdecl io_FormatTextBuffer(void*, int, ...);
void  __cdecl fcn_00545d40(int, int, void*, int, int, void*);
void  __cdecl fcn_00546190(void*);


/* ADDRESS: GOLDTL 0x00577790 */
void __cdecl fcn_00577790(void* a1)
{
	char buf[0x100];
	void* p1;
	void* p2;

	if (*(int*) ((char*) a1 + 0x70) != 0) {
		goto done;
	}
	p1 = gm_LookupEntityRecordById(*(int*) ((char*) a1 + 0xac));
	p2 = gm_LookupEntityRecordById(*(int*) ((char*) a1 + 0xb0));
	if (p1 != 0) {
		io_FormatTextBuffer(buf, 0x4035);
		fcn_00545d40(*(int*) ((char*) a1 + 0xac), -1, buf, 1, 0x5fb, g_6a7e90);
	}
	if (p2 != 0) {
		io_FormatTextBuffer(buf, 0x4036, *(unsigned short*) p1);
		fcn_00545d40(*(int*) ((char*) a1 + 0xb0), -1, buf, 1, 0x5fa, 0);
	}
done:
	fcn_00546190(a1);
}
