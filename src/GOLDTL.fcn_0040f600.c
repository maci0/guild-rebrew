// FUNCTION: GOLDTL 0x40f600
// SIZE: 84

int __cdecl fcn_00414d20(int, int, int, int);
void __cdecl fcn_00425bf0(void*, int, char*);

int __cdecl fcn_0040f600(int* a1, int* a2, int* a3)
{
	if (fcn_00414d20(*a1 / 17, 2, *a2, *a3) == 0) {
		fcn_00425bf0(*(void**) 0x6b7e98, *(int*) ((char*) *(void**) 0x6b7e98 + 0x118), (char*) 0x676924);
	}
	return 1;
}
