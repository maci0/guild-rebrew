
void __cdecl gm_FindObjektPrototypeByName(int value);

void __cdecl ahm_FindObjektByObName(int value)
{
	value += 3;
	gm_FindObjektPrototypeByName(value);
}
