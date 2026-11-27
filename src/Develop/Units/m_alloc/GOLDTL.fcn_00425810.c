

void __cdecl sbs_FreeSampleBank(int);
void __cdecl sbs_UnloadSoundBanks(int);
void __cdecl m_FreeTracked(int);

int __cdecl sbs_DestroySB(void)
{
	int r = 0;

	if (*(int*) 0x6b7d68 != r) {
		sbs_FreeSampleBank(r);
		sbs_UnloadSoundBanks(r);
		m_FreeTracked(*(int*) 0x6b7d68);
		*(int*) 0x6b7d68 = r;
		*(int*) 0x6b7d6c = r;
	} else {
		r = -1;
	}
	return r;
}
