/* fcn_00407690: e=m_alloc(0x14, 0x5f1a48); *(int*)(e+0x10)=a; return e. */

void* __cdecl m_alloc(int, void*);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x00407690 */
int __cdecl ch_AllocMap(int a)
{
	char* e;
	e = (char*) m_alloc(0x14, (void*) 0x5f1a48);
	*(int*) (e + 0x10) = a;
	return (int) e;
}
#else
/* ADDRESS: GOLDTL 0x00408220 */
/* ADDRESS: GOLDDE 0x004073c0 */
void __cdecl ch_AllocMap(int a1)
{
	void* p;

	p = m_alloc(0x14, "ch_map");
	*(int*) ((char*) p + 0x10) = a1;
}
#endif
