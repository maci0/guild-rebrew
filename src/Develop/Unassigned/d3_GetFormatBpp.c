
/* ADDRESS: GOLDTL 0x0041a950 */
int __cdecl d3_GetFormatBpp(int format)
{
	if (format < 0x14 || format > 0x1f) {
		return 0;
	}
	return ((int*) 0x662ba8)[format];
}
