int __cdecl fcn_00466190(int);
int __cdecl fcn_0047cb60(int, int);

/* ADDRESS: GOLD 0x00472c70 */
void __cdecl fcn_00472c70(int obj, int *out_b, int *out_a)
{
	int s;
	int p;

	if ((*(unsigned char *)(obj + 0xc) & 4) != 0) {
		s = fcn_00466190(*(int *)(obj + 0x278));
		p = fcn_0047cb60(s, 4);
		*out_a = *(unsigned short *)(p + 0xa);
		p = fcn_0047cb60(s, 6);
		*out_b = *(unsigned short *)(p + 6);
	} else {
		*out_a = 0;
		*out_b = 0;
	}
}
