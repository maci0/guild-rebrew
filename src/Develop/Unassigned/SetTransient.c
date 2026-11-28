extern char g_6b7e98[];


// SIZE 0x217
typedef struct {
	char pad[0x216];
	unsigned char b0 : 2;
} S40fe50;

void __cdecl evt_LogScriptError(void*, int, char*);

/* ADDRESS: GOLDDE 0x0040ec50 */
int __cdecl SetTransient(S40fe50** a1, char* value)
{
	S40fe50* obj;

	obj = *a1;
	if (obj == 0) {
		evt_LogScriptError(*(void**) &g_6b7e98, *(int*) ((char*) *(void**) &g_6b7e98 + 0x118), "SetTransient: Illegal object...");
		return 0;
	}
	obj->b0 = *value;
	return 1;
}
