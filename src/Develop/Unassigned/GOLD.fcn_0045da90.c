void __cdecl fcn_0045d7f0(char* owner, char* node);
void __cdecl m_FreeTracked(void* p);

/* ADDRESS: GOLD 0x0045da90 */
void __cdecl fcn_0045da90(char* owner)
{
	char* node;
	if (owner == 0) {
		return;
	}
	while ((node = *(char**) (owner + 0xac0)) != 0) {
		fcn_0045d7f0(owner, node);
	}
	m_FreeTracked(owner);
}
