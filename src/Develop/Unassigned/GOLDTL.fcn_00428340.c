
extern void* g_6b7ea0;
extern int* g_14cb8f0;
extern int g_6b7eb0;

int __cdecl evt_ParseScript(int a0);
int __cdecl evt_FindDefinition(int a0, char* a1);
void __cdecl evt_LogScriptError(int a0, int a1, char* a2);
void __cdecl fcn_00428720(int a0);
void __cdecl evt_EnterFunction(int a0, int a1);
int __cdecl sprintf(char* a0, const char* a1, ...);
char* __cdecl strcpy(char* a0, const char* a1);

/* ADDRESS: GOLDTL 0x00428340 */
int __cdecl fcn_00428340(char* scriptCtx, int a1, ...)
{
	int obj;
	int i;
	int kind; int* kinds; char* text;
	int* argp;

	if (scriptCtx == 0) {
		return 0;
	}
	if (evt_ParseScript((int) scriptCtx) == 0) {
		return 0;
	}
	obj = evt_FindDefinition((int) scriptCtx, (char*) 0x679608);
	if (obj == 0) {
		evt_LogScriptError((int) scriptCtx, 0, (char*) 0x6795d0);
		return 0;
	}
	if (a1 != *(char*) (obj + 0x24)) {
		evt_LogScriptError((int) scriptCtx, 0, (char*) 0x679610);
		fcn_00428720((int) scriptCtx);
		return 0;
	}
	argp = &a1;
	for (i = 0, kinds = (int*) (obj + 0x28), text = (char*) 0x14cb540; i < *(char*) (obj + 0x24); i++, kinds++, text += 0x60) {
		kind = *kinds;
		if (kind == 6) {
			strcpy(text, (char*) *(argp + 1));
			argp++;
		} else if (kind == 1) {
			((int*) g_6b7ea0)[kinds - (int*) (obj + 0x28)] = *(argp + 1);
			argp++;
		} else if (kind == 2) {
			((int*) g_6b7ea0)[kinds - (int*) (obj + 0x28)] = *(char*) (argp + 1);
			argp++;
		}
	}
	evt_EnterFunction((int) scriptCtx, obj);
	*(int*) (scriptCtx + 0x124) = *(int*) (scriptCtx + 0x124) | 1;
	*(int*) (scriptCtx + 0xc28) = (int) scriptCtx + 0x128;
	sprintf((char*) &g_14cb8f0[g_6b7eb0 * 0x21 + 1], (char*) 0x6795c0, scriptCtx);
	g_14cb8f0[g_6b7eb0 * 0x21] = 0;
	g_6b7eb0 = g_6b7eb0 + 1;
	if (g_6b7eb0 > 0x1e) {
		g_6b7eb0 = 0;
	}
	return 1;
}
