extern char g_68d538[];


void __cdecl fcn_0064d41a(void*, void*, void*, int, int, int);

char __cdecl fcn_004e46e0(void* context)
{
	char buf[0x100];

	fcn_0064d41a(buf, g_68d538, context, *(int*) ((char*) context + 0x1cc),
	    *(int*) ((char*) context + 0x218), *(int*) ((char*) context + 0x21c));
	return 1;
}
