

extern int (__stdcall *g_66234c)(int);

void __cdecl fcn_00402320(void)
{
	int h;

	h = *(int*) 0x675170;
	if (h != -1) {
		g_66234c(h);
		*(int*) 0x675170 = -1;
	}
}
