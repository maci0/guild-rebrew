char* __cdecl fcn_00508e40(int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_00529160(char*, int, int, char*);
int __cdecl fcn_00500bb0(char*, int, int, int);
int __cdecl fcn_00546190(char*);

/* ADDRESS: GOLDTL 0x0057a260 */
int __cdecl fcn_0057a260(char* p)
{
	int v;
	char* s;
	char* e;

	v = 0;
	s = (char*) fcn_00508e40(*(int*)(p + 0xac));
	if (s == 0)
		goto tail;
	if (*(char**)(s + 0x17c) != 0 && *(unsigned char*)*(char**)(s + 0x17c) == 0x8f)
		goto tail;
	e = (char*) gm_StartFilteredEntitySearch(*(int*)(p + 0x10), 1, 1);
	if (e == 0)
		goto tail;
	if (*(int*)(p + 0xb4) != -1)
		v = fcn_00502cd0(*(int*)(e + 0x5d), 2, 6, 1, *(int*)(p + 0xb4));

	*(int*)(p + 0x52) = *(int*)0x7f4c00;
	*(int*)(p + 0x56) = *(int*)0x7f4c04;
	*(int*)(p + 0x5a) = *(int*)0x7f4c08;
	*(short*)(p + 0x5e) = *(short*)0x7f4c0c;
	*(int*)(p + 0x44) = *(int*)0x7f4c00;
	*(int*)(p + 0x48) = *(int*)0x7f4c04;
	*(int*)(p + 0x4c) = *(int*)0x7f4c08;
	*(short*)(p + 0x50) = *(short*)0x7f4c0c;

	if (v)
		fcn_00529160(e, v, *(unsigned short*)s, p);
	else
		fcn_00529160(e, 0, *(unsigned short*)s, p);

	*(int*)(p + 0x60) = *(int*)0x7f4c00;
	*(int*)(p + 0x64) = *(int*)0x7f4c04;
	*(int*)(p + 0x68) = *(int*)0x7f4c08;
	*(short*)(p + 0x6c) = *(short*)0x7f4c0c;

	fcn_00500bb0(p + 0x52, 0, 0x1e, 0);

	*(int*)(p + 0xb8) = *(int*)(p + 0x52);
	*(int*)(p + 0xbc) = *(int*)(p + 0x56);
	*(int*)(p + 0xc0) = *(int*)(p + 0x5a);
	*(short*)(p + 0xc4) = *(short*)(p + 0x5e);

	return fcn_00500bb0(p + 0xb8, 3, 0, 0);

tail:
	return fcn_00546190(p);
}
