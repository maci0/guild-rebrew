

int __cdecl d3_ReleaseRenderVertexBuffers(void);

int __cdecl d3_FreeRenderVertexBuffers(void)
{
	return d3_ReleaseRenderVertexBuffers();
}
