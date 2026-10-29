void __cdecl fcn_00456b10(void* entry);

/* ADDRESS: GOLDTL 0x00456d50 */
char __cdecl fcn_00456d50(char* this, int id)
{
	int i;

	if ((*(unsigned char*) (this + 0x215) & 1) != 0 && *(int*) (this + 0x1ec) != 0) {
		for (i = 0; i < 0x270; i += 0x9c) {
			if (*(int*) (*(int*) (this + 0x1ec) + i + 0x1384) != 0 &&
			    *(int*) (*(int*) (this + 0x1ec) + i + 0x138c) == id) {
				fcn_00456b10((void*) (*(int*) (this + 0x1ec) + i + 0x1384));
				*(int*) (*(int*) (this + 0x1ec) + i + 0x138c) = 0;
				*(int*) (*(int*) (this + 0x1ec) + i + 0x13a0) = 0;
				*(int*) (*(int*) (this + 0x1ec) + i + 0x13a4) = 0;
				*(int*) (*(int*) (this + 0x1ec) + i + 0x13a8) = 0;
			}
		}
	}
	return 1;
}
