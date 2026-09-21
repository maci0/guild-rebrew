// FUNCTION: GOLDTL 0x465750
// SIZE: 64
// ahm_ResetEntityState

int __cdecl ahm_ResetEntityState(char* a, int* p2, int* p3)
{
	*p3 = 0;
	*p2 = 0;
	if (a == 0 || *(int*) (a + 0x18) == 0 || *(int*) (a + 0x7c) != 0) {
		return 0xffffff9a;
	}
	*p2 = *(int*) (a + 0x14);
	*p3 = *(int*) (a + 0x10);
	return 0;
}
