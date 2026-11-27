

void* __cdecl gm_LookupEntityRecordById(int);
void __cdecl io_FormatTextBuffer(void*, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, int);

int __cdecl gm_HandleMsg43PostNews(void* record)
{
	char buf[0x200];
	void* p;
	unsigned len;

	p = gm_LookupEntityRecordById(*(int*) record);
	if (p == 0) {
		return 1;
	}
	io_FormatTextBuffer(buf, *(unsigned short*) ((char*) record + 4) + 0x12e7);
	len = (unsigned) strlen(buf);
	he_PostEntityMessage(*(int*) ((char*) p + 4), *(int*) ((char*) p + 4), buf,
	    len > 0x100, 0x603, 0);
	return 0;
}
