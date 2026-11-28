
void __cdecl gm_FindObjektPrototypeByName(int value);

/* ADDRESS: GOLDDE 0x004da120 */
void __cdecl ahm_FindObjektByObName(int value)
{
	value += 3;
	gm_FindObjektPrototypeByName(value);
}
