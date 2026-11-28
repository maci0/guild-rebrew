extern char he_EventCreateHandlers[];
extern char he_EventCreateHandlers[];
extern char he_EventDispatchHandlers[];
extern char he_EventDispatchHandlers[];

/* ADDRESS: GOLD 0x0053d860 */
/* ADDRESS: GOLDTL 0x00545580 */
int __cdecl he_RegisterHandler(int index, int a2, int a3)
{
	if (index < 0 || index >= 0xa7) {
		return 1;
	}
	((int*) he_EventCreateHandlers)[index] = a2;
	((int*) he_EventDispatchHandlers)[index] = a3;
	return 0;
}
