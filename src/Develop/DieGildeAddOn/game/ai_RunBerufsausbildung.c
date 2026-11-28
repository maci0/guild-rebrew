void __cdecl cm_SendCopyEntityData(char* msg);

/* ADDRESS: GOLDTL 0x004a0da0 */
/* ADDRESS: GOLDDE 0x0048f7d0 */
int __cdecl ai_RunBerufsausbildung(char* actor, char* x, char* y)
{
	char msg[0xf8];

	if (x[0] == 7 && y[0] == 0x17) {
		*(int*) (msg + 8) = *(int*) (x + 4);
		msg[0x36] = 0x12;
		*(int*) (msg + 0x58) = *(int*) (actor + 4);
		msg[4] = 0x5e;
		*(int*) (msg + 0xc) = -1;
		msg[0x5c] = y[4];
		*(int*) (msg + 0x60) = *(int*) (y + 0x10);
		cm_SendCopyEntityData(msg);
		return 0x3a;
	}
	return 0;
}
