void __cdecl fcn_0051af00(void* buffer, int format, ...);
void __cdecl fcn_005d86a0(void* rec, void* ctx);

/* ADDRESS: GOLDTL 0x004f97f0 */
int __cdecl fcn_004f97f0(char* rec, int* ctx)
{
	int action;

	action = *ctx;
	if (action == 3 || action == 1) {
		if (*(char*) (rec + 2) == 6) {
			fcn_0051af00(&ctx[5], 0x679060, 0x1de3);
		}
		if (*(char*) (rec + 0x166) != 0x1b) {
			return 1;
		}
		if (*(unsigned int*) (rec + 0x1c8) & 0x200) {
			return 9;
		}
		if (*ctx == 3) {
			fcn_005d86a0(rec, ctx);
		}
		return 2;
	}
	if (action == 4 || action == 2) {
		if (!(*(unsigned int*) (rec + 0x1c8) & 0x100) || !ctx[0x87]) {
			return 1;
		}
		if (*(char*) (*(int*) (ctx + 0x87) + 0x166) != 0x1b) {
			return 1;
		}
		if (action == 4) {
			fcn_005d86a0(rec, ctx);
			return 10;
		}
		if (*(char*) (rec + 2) == 6) {
			fcn_0051af00(&ctx[5], 0x679060, 0x1de3);
		}
		return 10;
	}
	return 1;
}
