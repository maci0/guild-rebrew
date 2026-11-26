

void* __cdecl gm_LookupEntityRecordById(int);
void __cdecl io_FormatTextBuffer(void*, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, int);

int __cdecl fcn_004bbb40(void* request)
{
	char buf[0x200];
	void* entity;
	unsigned len;

	entity = gm_LookupEntityRecordById(*(int*) request);
	if (entity == 0) {
		return 1;
	}
	io_FormatTextBuffer(buf, *(unsigned short*) ((char*) request + 4) + 0x12e7);
	len = (unsigned) strlen(buf);
	he_PostEntityMessage(*(int*) ((char*) entity + 4), *(int*) ((char*) entity + 4), buf,
	    len > 0x100, 0x603, 0);
	return 0;
}
