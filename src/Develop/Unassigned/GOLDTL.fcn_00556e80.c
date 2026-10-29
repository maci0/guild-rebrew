


int __cdecl fcn_0047dcf0(unsigned short*);
int __cdecl fcn_0047dca0(unsigned short*);

int __cdecl fcn_00556e80(unsigned short* e)
{
	if (*e == 0xffff) {
		return 0;
	}
	if (((char*) e)[8] == 0) {
		return 0;
	}
	if (((unsigned char*) e)[2] >= 10) {
		return 0;
	}
	if (fcn_0047dcf0(e)) {
		return 1;
	}
	return fcn_0047dca0(e) != 0;
}
