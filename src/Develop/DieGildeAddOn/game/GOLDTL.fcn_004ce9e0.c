


extern char* lpObjektePROT;
extern char g_68b7ac[];

int* __cdecl fcn_004ce610(char*);
char* __cdecl fcn_0066080a(char*);
int __cdecl fcn_0064d41a(char*, char*, ...);
int __cdecl fcn_0065f220(char*, char*);
void __cdecl fcn_00407800(char*, int, char*);

void __cdecl fcn_004ce9e0(char* e)
{
	char buf[0x80];
	int* r;
	int k;
	char* name;

	r = fcn_004ce610(e);
	if (r != 0 && *r != 0) {
		k = *r;
		name = lpObjektePROT + k * 0x40 + k;
		if (*(char**) (e + 0x184) == 0)
			return;
		fcn_0064d41a(buf, g_68b7ac, fcn_0066080a(name + 1));
		if (*(char**) (*(char**) (e + 0x184) + 0x64) != 0 &&
		    fcn_0065f220(*(char**) (*(char**) (e + 0x184) + 0x64), buf) == 0)
			return;
		if (*(char**) (*(char**) (e + 0x184) + 0x64) != 0)
			fcn_00407800(*(char**) (e + 0x184), 2, 0);
		fcn_00407800(*(char**) (e + 0x184), 2, buf);
		return;
	}
	if (*(char**) (e + 0x184) != 0 && *(char**) (*(char**) (e + 0x184) + 0x64) != 0)
		fcn_00407800(*(char**) (e + 0x184), 2, 0);
}
