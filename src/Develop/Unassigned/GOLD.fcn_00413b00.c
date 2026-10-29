
// fcn_00413b00 — fcn_0043dbc0(a); for(p=a[0x1fc]; p; p=p[0x1f0]) fcn_00413b00(p).

int __cdecl fcn_0043dbc0(void*);

void __cdecl fcn_00413b00(void* a)
{
	char* p;
	fcn_0043dbc0(a);
	p = *(char**) ((char*) a + 0x1fc);
	while (p != 0) {
		fcn_00413b00(p);
		p = *(char**) (p + 0x1f0);
	}
}
