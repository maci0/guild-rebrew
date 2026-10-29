extern int g_6b8010;
extern unsigned char* lpGebaeudeINST;



void __cdecl fcn_004432d0(int, int);
void __cdecl fcn_00446f70(int, int);

int __cdecl fcn_0051eb20(int a)
{
	int save;
	int i;
	char* e;

	save = g_6b8010;
	fcn_004432d0(0, 1);
	for (i = 0; i < 0x100; i++) {
		if (((char*)lpGebaeudeINST)[i * 0xa9] != 0 && *(char**) (((char*)lpGebaeudeINST) + i * 0xa9 + 0x61) != 0) {
			*(int*) (*(char**) (((char*)lpGebaeudeINST) + i * 0xa9 + 0x61) + 0x204) =
			    *(int*) (((char*)lpGebaeudeINST) + i * 0xa9 + 1);
		}
	}
	fcn_00446f70(0, a);
	for (i = 0; i < 0x100; i++) {
		e = ((char*)lpGebaeudeINST) + i * 0xa9;
		if (*e != 0 && *(char**) (e + 0x61) != 0) {
			*(char**) (*(char**) (e + 0x61) + 0x204) = e;
		}
	}
	fcn_004432d0(save, 1);
	return 1;
}
unsigned char _dpad_869480[674836];
