extern int g_772ea4;



int __cdecl gm_LookupEntityRecordById(int);
void __cdecl io_FormatTextBuffer(void*, int, int);
void __cdecl fcn_00533a40(void*);

void __cdecl fcn_004d87b0(void* a1)
{
	char buf[0x100];

	g_772ea4 = gm_LookupEntityRecordById(*(int*) a1);
	io_FormatTextBuffer(buf, 0x11b7, *(unsigned short*) g_772ea4);
	fcn_00533a40(buf);
}
