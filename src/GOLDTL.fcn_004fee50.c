void __cdecl fcn_004c4510(char* base, int entity_id);
void __cdecl fcn_004c4570(unsigned char size, unsigned char count, unsigned short off, char* src);
void __cdecl fcn_004c5480(int id, int kind, float value);
void __cdecl fcn_004c5360(void);

extern unsigned int g_773d48;

/* ADDRESS: GOLDTL 0x004fee50 */
void __cdecl fcn_004fee50(char* o, int v)
{
	float f;
	float x;
	float s;
	float t;
	int n;

	if (o != 0) {
		f = (float) (v & 0xffff);
		if (f <= *(float*) (o + 0x20)) {
			fcn_004c5480(*(int*) (o + 4), 0x1c, *(float*) (o + 0x18) - *(float*) (o + 0x1c));
		} else {
			x = *(float*) (o + 0x18);
			s = *(float*) (o + 0x14);
			for (n = (int) (f - *(float*) (o + 0x20)); n > 0; n--) {
				t = s / x;
				x = x - s + t;
			}
			fcn_004c5480(*(int*) (o + 4), 0x1c, x - *(float*) (o + 0x1c));
		}
		fcn_004c4510(o, *(int*) (o + 4));
		fcn_004c4570(2, 1, 10, (char*) &v);
		fcn_004c5360();
		g_773d48++;
	}
}
