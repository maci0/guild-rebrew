/* ADDRESS: GOLDTL 0x00455f80 */
void __cdecl d3_FillDiamondAreaIfHeight(int value, int unused, int storeval, int count,
	unsigned char* p, int base, int centerX, int centerY, int stride, int areaRadius)
{
	int v;
	int row;
	int rowOffset;
	int maxRow;
	int dy;
	int i;
	int end;

	if (count <= 0) {
		return;
	}
	v = value >> 16;
	do {
		if ((unsigned char) v >= *p) {
			row = centerY - areaRadius;
			row = row < 0 ? 0 : row;
			rowOffset = row * stride;
			maxRow = centerY + areaRadius;
			dy = centerY - row;
			while (row <= (maxRow < stride - 1 ? maxRow : stride - 1)) {
				end = centerX + (areaRadius - (dy < 0 ? -dy : dy));
				i = centerX - (areaRadius - (dy < 0 ? -dy : dy));
				i = i < 0 ? 0 : i;
				while (i <= (end < stride - 1 ? end : stride - 1)) {
					((int*) base)[(rowOffset + i) * 7] = storeval;
					i++;
				}
				row++;
				dy--;
				rowOffset += stride;
			}
		}
		p++;
		count--;
	} while (count != 0);
}
