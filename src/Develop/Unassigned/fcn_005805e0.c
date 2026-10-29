extern int* g_665f08;

void __cdecl fcn_00471e30(int);

/* ADDRESS: GOLDTL 0x005805e0 */
void __cdecl fcn_005805e0(void)
{
	int h;

	h = *(int*) (((char*) g_665f08) + 0x68);
	if (h != -1) {
		fcn_00471e30(h);
		*(int*) (((char*) g_665f08) + 0x68) = -1;
	}
}
