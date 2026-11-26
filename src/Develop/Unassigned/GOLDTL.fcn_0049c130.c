extern char s_67ead8[];

void __cdecl cm_SendLogAction(char* s);
void __cdecl cm_SendCopyEntityData(char* msg);
void __cdecl cm_SendTraceEnd(char* s);

/* ADDRESS: GOLDTL 0x0049c130 */
int __cdecl ai_RunSpionage(char* a1, char* x)
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
	cm_SendLogAction(s_67ead8);
	cm_SendCopyEntityData(msg);
	cm_SendTraceEnd(s_67ead8);
	return 0x25;
}
