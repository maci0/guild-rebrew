
// fcn_004176f0 — if([0x631130]) fcn_00422620([0x631130]); [0x631130]=0.

int __cdecl m_FreeTracked(int);

void __cdecl d3_FreeBuffer6b5d08(void)
{
	int h;
	h = *(int*) 0x631130;
	if (h != 0) {
		m_FreeTracked(h);
	}
	*(int*) 0x631130 = 0;
}
