

int __cdecl d3_ReleaseRenderVertexBuffers(void);

/* ADDRESS: GOLDDE 0x00416940 */
int __cdecl d3_FreeRenderVertexBuffers(void)
{
	return d3_ReleaseRenderVertexBuffers();
}
