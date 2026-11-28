


extern int nt_PacketStats[][4];

/* ADDRESS: GOLDDE 0x0041db00 */
void __cdecl nt_RecordPacketStats(unsigned char* p, unsigned int n, char flag)
{
	int k;

	if (p != 0 && n > *p && *p < 0x6a) {
		k = flag ? 0 : 2;
		nt_PacketStats[*p][k]++;
		nt_PacketStats[*p][k + 1] += n;
	}
}
