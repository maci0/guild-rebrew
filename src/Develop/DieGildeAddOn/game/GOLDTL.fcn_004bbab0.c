

void* __cdecl gm_LookupEntityRecordById(int);
void __cdecl io_FormatTextBuffer(void*, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, int);

int __cdecl fcn_004bbab0(void* a1)
{
	char buf[0x200];
	void* p;
	unsigned len;

	p = gm_LookupEntityRecordById(*(int*) a1);
	if (p == 0) {
		return 1;
	}
	io_FormatTextBuffer(buf, *(unsigned short*) ((char*) a1 + 4) + 0x12e7);
	len = (unsigned) strlen(buf);
	fcn_00545d40(*(int*) ((char*) p + 4), *(int*) ((char*) p + 4), buf,
	    len > 0x100, 0x603, 0);
	return 0;
}
