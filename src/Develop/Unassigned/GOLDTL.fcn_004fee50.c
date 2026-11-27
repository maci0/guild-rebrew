void __cdecl cm_BeginPacketFieldDelta(char* base, int entity_id);
void __cdecl cm_AppendPacketFieldDelta(unsigned char size, unsigned char count, unsigned short off, char* src);
void __cdecl cm_RequestChangeFloat(int id, int kind, float value);
void __cdecl cm_RequestChangeAttribute(void);

extern unsigned int g_773d48;

/* ADDRESS: GOLDTL 0x004fee50 */
void __cdecl gm_SetEntityAge(char* o, int v)
{
	float f;
	float x;
	float s;
	float t;
	int n;

	if (o != 0) {
		f = (float) (v & 0xffff);
		if (f <= *(float*) (o + 0x20)) {
			cm_RequestChangeFloat(*(int*) (o + 4), 0x1c, *(float*) (o + 0x18) - *(float*) (o + 0x1c));
		} else {
			x = *(float*) (o + 0x18);
			s = *(float*) (o + 0x14);
			for (n = (int) (f - *(float*) (o + 0x20)); n > 0; n--) {
				t = s / x;
				x = x - s + t;
			}
			cm_RequestChangeFloat(*(int*) (o + 4), 0x1c, x - *(float*) (o + 0x1c));
		}
		cm_BeginPacketFieldDelta(o, *(int*) (o + 4));
		cm_AppendPacketFieldDelta(2, 1, 10, (char*) &v);
		cm_RequestChangeAttribute();
		g_773d48++;
	}
}
