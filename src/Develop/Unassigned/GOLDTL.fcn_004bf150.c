#ifdef REBREW_GOLD
#define d2_DestroyElement d2_DestroyGuiElement
#endif
void __cdecl d2_DestroyElement(int);


/* ADDRESS: GOLDTL 0x004bf150 */
void __cdecl d2_DestroyElementTriple(int* p)
{
	if (p[0] != -1)
		d2_DestroyElement(p[0]);
	if (p[1] != -1)
		d2_DestroyElement(p[1]);
	if (p[2] != -1)
		d2_DestroyElement(p[2]);
	p[0] = -1;
	p[1] = -1;
	p[2] = -1;
}
