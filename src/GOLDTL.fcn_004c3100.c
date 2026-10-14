


extern char g_679888[];
extern char g_68a500[];
extern char g_68a4f4[];

int __cdecl fcn_0064d41a(char*, char*, ...);
int __cdecl fcn_00422dc0(char*, int);

int __cdecl fcn_004c3100(char* name, int x)
{
	char buf[0x104];
	int r;

	fcn_0064d41a(buf, g_68a500, g_679888, name);
	r = fcn_00422dc0(buf, x);
	if (r == 0) {
		fcn_0064d41a(buf, g_68a4f4, name);
		r = fcn_00422dc0(buf, x);
	}
	return r;
}
