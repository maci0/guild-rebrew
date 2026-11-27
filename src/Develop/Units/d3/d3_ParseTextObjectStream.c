

void __cdecl d3_ParseTextBlock(void*, int, int, int);

void __cdecl d3_ParseTextObjectStream(void* stream, int ctx)
{
	d3_ParseTextBlock(stream, 0x67b400, 5, ctx);
}
