


// fcn_00404e40 — eax=0; if(si) eax = fcn_005de784() % (si&0xffff); return eax.

int __cdecl fcn_005de784(void);

int __cdecl fcn_00404e40(unsigned short si)
{
	int r;
	r = 0;
	if (si != 0) {
		r = fcn_005de784() % (si & 0xffff);
	}
	return r;
}

