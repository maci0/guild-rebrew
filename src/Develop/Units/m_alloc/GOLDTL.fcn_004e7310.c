int __cdecl m_is_tracked(void* p);

/* ADDRESS: GOLDTL 0x004e7310 */
void __cdecl fcn_004e7310(char* p)
{
	char* inner;

	if (p == 0)
		return;
	if (!m_is_tracked(p)) {
		__asm { int 3 }
	}
	inner = *(char**) (p + 0x34);
	if (inner == 0)
		return;
	if (!m_is_tracked(inner)) {
		__asm { int 3 }
	}
}
