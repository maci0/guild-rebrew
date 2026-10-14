void __cdecl fcn_0043d430(char* a, char* e, int v);

/* ADDRESS: GOLD 0x0043d630 */
char __cdecl fcn_0043d630(char* a, int* v)
{
	unsigned int i;

	if (*(char**) (a + 0x1ec) != 0) {
		for (i = 0; i < *(unsigned char*) (*(char**) (a + 0x1ec) + 0x96c); i++) {
			fcn_0043d430(a, *(char**) (a + 0x1ec) + i * 0x198 + 0xf4, *v);
		}
	}
	return 1;
}
