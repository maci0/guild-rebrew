// FUNCTION: GOLD 0x004ce270
// FUNCTION: GOLDTL 0x4cf0f0

// fcn_004ce270 — a[0x16c/4] != b[0x16c/4].

int __cdecl fcn_004ce270(char* a, char* b)
{
	return *(int*) (a + 0x16c) != *(int*) (b + 0x16c);
}

