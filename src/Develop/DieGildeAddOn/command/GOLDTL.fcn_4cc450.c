

int __cdecl amt_ApplyOfficeAssignment(void*);

/* ADDRESS: GOLDDE 0x004b9c30 */
int __cdecl fcn_004cb910(char* a, char* b)
{
	int r;
	r = amt_ApplyOfficeAssignment(a + 0x10);
	if (b != 0) {
		b[1] = 0;
		b[0] = (char) ((r == 0) + 1);
		*(int*) (b + 6) = 0;
	}
	return r == 0;
}
