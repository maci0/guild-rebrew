

int __cdecl fcn_0065f220(int, int);
void __cdecl d3_RemoveObjectAnimation(char*, int);
void __cdecl d3_InvalidateSubTreeFlags(char*, int);

int __cdecl d3_ClearSlotAnimation(char* p, int a2)
{
	int i;
	char* q;
	int e;

	for (i = 0; i < 3; i++) {
		q = *(char**) (p + 0x1ec);
		if (q != 0) {
			e = *(int*) (q + i * 0x7c + 0x484);
			if (e != 0 && fcn_0065f220(e, a2) == 0) {
				d3_RemoveObjectAnimation(*(char**) (p + 0x1ec) + 0xf4, a2);
				d3_InvalidateSubTreeFlags(p, 0);
			}
		}
	}
	return 1;
}
