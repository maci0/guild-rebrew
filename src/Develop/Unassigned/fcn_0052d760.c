extern char* d3_ActiveCamera;

/* ADDRESS: GOLDTL 0x0052d760 */
void __cdecl fcn_0052d760(char* out)
{
	if (d3_ActiveCamera == 0) {
		return;
	}
	*(int*) (out + 0x00) = *(int*) (d3_ActiveCamera + 0x4c);
	*(int*) (out + 0x04) = *(int*) (d3_ActiveCamera + 0x50);
	*(int*) (out + 0x08) = *(int*) (d3_ActiveCamera + 0x54);
	*(int*) (out + 0x10) = *(int*) (d3_ActiveCamera + 0x84);
	*(int*) (out + 0x14) = *(int*) (d3_ActiveCamera + 0x88);
	*(int*) (out + 0x18) = *(int*) (d3_ActiveCamera + 0x8c);
}
