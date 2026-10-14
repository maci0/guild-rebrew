extern char s_67ead8[];

void __cdecl fcn_004c4eb0(char* s);
void __cdecl fcn_004c5530(char* msg);
void __cdecl fcn_004c4ef0(char* s);

/* ADDRESS: GOLD 0x0049c6f0 */
/* ADDRESS: GOLDTL 0x0049c130 */
int __cdecl fcn_0049c130(char* a1, char* x)
{
	char msg[0xf8];

	if (x[0] != 7) {
		return 0;
	}
	msg[4] = 0x18;
	msg[0x36] = 2;
	*(int*) (msg + 8) = *(int*) (a1 + 4);
	*(int*) (msg + 0xc) = -1;
	if (*(char**) (a1 + 0x170)) {
		*(int*) (msg + 0x58) = *(int*) (*(char**) (a1 + 0x170) + 1);
	} else {
		*(int*) (msg + 0x58) = -1;
	}
	*(int*) (msg + 0x70) = *(int*) (x + 4);
	*(int*) (msg + 0x90) = *(int*) (x + 0x10);
	fcn_004c4eb0(s_67ead8);
	fcn_004c5530(msg);
	fcn_004c4ef0(s_67ead8);
	return 0x25;
}
