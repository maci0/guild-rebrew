

int __cdecl rand(void);

/* ADDRESS: GOLDDE 0x0040b2b0 */
int __cdecl ecmd_Rnd(int* max_ptr)
{
	if (*max_ptr == 0) {
		return 0;
	}
	return rand() % *max_ptr;
}
