
/* Set the field on the record found by its packed key. */

char* __cdecl fcn_005b1a80(int);

void __cdecl fcn_005a8a50(char* a, int b)
{
	int* e;
	e = (int*) fcn_005b1a80(*(int*) (a + 1));
	if (e != 0) {
		e[0x44 / 4] = b;
	}
}
