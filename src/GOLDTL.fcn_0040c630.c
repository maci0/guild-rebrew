extern char* g_6b7ebc;
extern char* g_6b7e98;
extern int g_6b7fac;

/* Sleep. While this command is the one in progress, wait until the
 * clock reaches the stored base plus the tick count divided by 14.
 * A count of -1 waits forever. The first entry records the clock. */
// FUNCTION: GOLDTL 0x40c630

int __cdecl fcn_0040c630(int* ticks)
{
	char* vm;
	int n;

	if (g_6b7ebc != 0 && *(void**) (g_6b7ebc + 0x44) == (void*) fcn_0040c630) {
		vm = g_6b7e98;
		n = *ticks;
		if (n != -1 && (unsigned) g_6b7fac >= (unsigned) (n / 14 + *(int*) (vm + 0xc88))) {
			return 0;
		}
		*(void**) (vm + 0xc60) = (void*) fcn_0040c630;
		return 0;
	}
	*(void**) (g_6b7e98 + 0xc60) = (void*) fcn_0040c630;
	/* The clock is read again through volatile so this load stays in
	 * eax and the VM is reloaded into ecx. */
	*(int*) (g_6b7e98 + 0xc88) = *(volatile int*) &g_6b7fac;
	return 1;
}
