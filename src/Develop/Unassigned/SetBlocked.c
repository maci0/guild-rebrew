extern char g_6b7e98[];


// SIZE 0x217
typedef struct {
	char pad[0x216];
	unsigned char b0 : 2;
	unsigned char b2 : 1;
} S40fe00;

void __cdecl evt_LogScriptError(void*, int, char*);

/* ADDRESS: GOLDDE 0x0040ec00 */
int __cdecl SetBlocked(S40fe00** a1, char* blocked)
{
	S40fe00* p;

	p = *a1;
	if (p == 0) {
		evt_LogScriptError(*(void**) &g_6b7e98, *(int*) ((char*) *(void**) &g_6b7e98 + 0x118), "SetBlocked: Illegal object...");
		return 0;
	}
	p->b2 = *blocked;
	return 1;
}
