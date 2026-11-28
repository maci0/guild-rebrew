

int __cdecl rand(void);

int __cdecl ecmd_Rnd(int* max_ptr)
{
	if (*max_ptr == 0) {
		return 0;
	}
	return rand() % *max_ptr;
}
