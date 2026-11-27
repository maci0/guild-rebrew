typedef void (__cdecl* CALLBACK)(int, int, int, int, int, int, int, int, int, int);
void __cdecl d3_FillDiamondAreaIfHeight(int, int, int, int, unsigned char*, int, int, int, int, int);
void __cdecl d3_RasterizeFlatHeightSpan(int, int, int, int, unsigned char*);

/* ADDRESS: GOLDTL 0x00455d30 */
void __cdecl fcn_00455d30(int count, int arg1, unsigned char flags, int arg3, int arg4)
{
	CALLBACK cb;
	int v6;
	int edgeInt;
	int i;
	int edge;

	i = 0;
	v6 = 0;
	if ((flags & 5) != 0) {
		if ((flags & 1) == 0) {
			v6 = 0xb;
		}
		if (flags & 2) {
			cb = (CALLBACK) 0x455e60;
		}
		else {
			cb = (CALLBACK) d3_FillDiamondAreaIfHeight;
		}
	}
	else {
		cb = (CALLBACK) d3_RasterizeFlatHeightSpan;
	}
	if (count <= 0)
		return;
	edge = *(int*) 0x1043290;
	do {
		edgeInt = (edge + 0xffff) >> 16;
		*(int*) 0x10529c0 = ((*(int*) 0x1043298 + 0xffff) >> 16) - edgeInt;
		if (*(int*) 0x10529c0 > 0) {
			cb(((((edgeInt << 16) - edge) * *(int*) 0x10529cc) >> 16) + *(int*) 0x1042a20,
			   *(int*) 0x10529cc, v6, *(int*) 0x10529c0,
			   *(int*) 0x1042580 + edgeInt, *(int*) 0x1040624, edgeInt,
			   i + arg4, arg1, *(int*) 0x1040620);
			edge = *(int*) 0x1043290;
		}
		*(int*) 0x1043298 += *(int*) 0x1042a2c;
		edge += *(int*) 0x1042a1c;
		*(int*) 0x1042a20 += *(int*) 0x1042a0c;
		i++;
		*(int*) 0x1043290 = edge;
		*(int*) 0x1042580 += arg1;
	} while (i < count);
}
