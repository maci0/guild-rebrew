/* ADDRESS: GOLD 0x0045cdf0 */
void __cdecl fcn_0045cdf0(char* object)
{
	int offset;

	if (object[0x211] & 4) {
		if (*(int*) (object + 0x1ec) != 0) {
			for (offset = 0; offset < 0x200; offset += 0x80) {
				if (*(int*) (*(char**) (object + 0x1ec) + offset + 0x754) != 0) {
					*(int*) (*(char**) (object + 0x1ec) + offset + 0x76c) = 0;
					*(int*) (*(char**) (object + 0x1ec) + offset + 0x770) = 0;
					*(int*) (*(char**) (object + 0x1ec) + offset + 0x774) = 0;
				}
			}
		}
	}
}
