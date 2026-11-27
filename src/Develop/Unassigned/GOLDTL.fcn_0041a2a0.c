

void __cdecl d3_RemoveDisplayAdapter(int);

void __cdecl d3_ClearDisplayAdapterList(void)
{
	while (*(unsigned*) 0x6b5de8 > 0) {
		d3_RemoveDisplayAdapter(0);
	}
}
