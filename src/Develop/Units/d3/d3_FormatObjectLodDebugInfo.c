extern char d3_ObjectLodDebugFmt[];


void __cdecl fcn_0064d41a(void*, void*, void*, int, int, int);

char __cdecl d3_FormatObjectLodDebugInfo(void* context)
{
	char buf[0x100];

	fcn_0064d41a(buf, d3_ObjectLodDebugFmt, context, *(int*) ((char*) context + 0x1cc),
	    *(int*) ((char*) context + 0x218), *(int*) ((char*) context + 0x21c));
	return 1;
}
