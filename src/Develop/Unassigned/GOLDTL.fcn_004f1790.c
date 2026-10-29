typedef struct {
	int kind;
	char pad[16];
} Elem4f1790;
// SIZE 0x14

/* ADDRESS: GOLDTL 0x004f1790 */
int __cdecl fcn_004f1790(char* a, Elem4f1790* e)
{
	if (e->kind == 0) {
		return e - *(Elem4f1790**) (a + 8);
	}
	if (e->kind == 1) {
		return e - *(Elem4f1790**) (a + 0xc);
	}
	if (e->kind == 2) {
		return e - *(Elem4f1790**) (a + 0x10);
	}
	if (e->kind == 3) {
		return e - *(Elem4f1790**) (a + 0x14);
	}
	return -1;
}
