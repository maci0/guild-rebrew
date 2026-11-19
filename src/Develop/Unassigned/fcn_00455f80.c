/* ADDRESS: GOLDTL 0x00455f80 */
void __cdecl fcn_00455f80(int value, int unused, int storeval, int count,
	unsigned char* p, int base, int centerX, int centerY, int stride, int areaRadius)
{
	int v;
	int v2;
	int v5;
	int local0;
	int edi;
	int i;
	int end;

	if (count <= 0) {
		return;
	}
	v = value >> 16;
	do {
		if ((unsigned char) v >= *p) {
			v2 = centerY - areaRadius;
			v2 = v2 < 0 ? 0 : v2;
			v5 = v2 * stride;
			local0 = centerY + areaRadius;
			edi = centerY - v2;
			while (v2 <= (stride - 1 < local0 ? stride - 1 : local0)) {
				end = centerX + (areaRadius - (edi < 0 ? -edi : edi));
				i = centerX - (areaRadius - (edi < 0 ? -edi : edi));
				i = i < 0 ? 0 : i;
				while (i <= (end < stride - 1 ? end : stride - 1)) {
					((int*) base)[(v5 + i) * 7] = storeval;
					i++;
				}
				v2++;
				edi--;
				v5 += stride;
			}
		}
		p++;
		count--;
	} while (count != 0);
}
