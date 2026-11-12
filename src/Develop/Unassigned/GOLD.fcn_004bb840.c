
// fcn_004bb840 — if([0x6f0738]) { fcn_00422620(h); [0x6f0738]=0; }.

int __cdecl m_FreeTracked(int);

void __cdecl fcn_004bb840(void)
{
	int h;
	h = *(int*) 0x6f0738;
	if (h != 0) {
		m_FreeTracked(h);
		*(int*) 0x6f0738 = 0;
	}
}
