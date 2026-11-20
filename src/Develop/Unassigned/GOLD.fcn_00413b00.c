
// fcn_00413b00 — fcn_0043dbc0(a); for(p=a[0x1fc]; p; p=p[0x1f0]) fcn_00413b00(p).

int __cdecl d3_InflateObject(void*);

void __cdecl d3_InflateObjectTree(void* a)
{
	char* p;
	d3_InflateObject(a);
	p = *(char**) ((char*) a + 0x1fc);
	while (p != 0) {
		d3_InflateObjectTree(p);
		p = *(char**) (p + 0x1f0);
	}
}
