


char* __cdecl he_StartHandlungSearch(int, int, int, ...);
char* __cdecl he_fn_Handlung(void);

int __cdecl fcn_0055c140(unsigned short* e, char* b, int* out)
{
	int n;
	char* r;

	n = 0;
	r = he_StartHandlungSearch(2, 2, *e, n, 0x35);
	while (r != 0) {
		if (*(int*) (b + 4) == *(int*) (r + 0xbc)) {
			return 0;
		}
		r = he_fn_Handlung();
		n++;
	}
	if (out != 0) {
		*out = n;
	}
	return 1;
}
