
// fcn_004fdfb0 — if([0x6f1b94]) { fcn_00422620(h); [0x6f1b94]=0; }.

int __cdecl m_FreeTracked(int);

void __cdecl fcn_004fdfb0(void)
{
	int h;
	h = *(int*) 0x6f1b94;
	if (h != 0) {
		m_FreeTracked(h);
		*(int*) 0x6f1b94 = 0;
	}
}
