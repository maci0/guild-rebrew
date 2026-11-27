void __cdecl d3_UnlinkSkyLayer(char* owner, char* node);
void __cdecl m_FreeTracked(void* p);

/* ADDRESS: GOLD 0x0045da90 */
void __cdecl d3_DestroySky(char* owner)
{
	char* node;
	if (owner == 0) {
		return;
	}
	while ((node = *(char**) (owner + 0xac0)) != 0) {
		d3_UnlinkSkyLayer(owner, node);
	}
	m_FreeTracked(owner);
}
