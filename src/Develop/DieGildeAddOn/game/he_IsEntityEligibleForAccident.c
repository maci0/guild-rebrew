


int __cdecl gm_IsEntityHomeInLocalShard(unsigned short*);

/* ADDRESS: GOLDDE 0x0053ab70 */
int __cdecl he_IsEntityEligibleForAccident(unsigned short* e)
{
	int ok;
	char* c;

	ok = 1;
	if (*e == 0xffff) {
		ok = 0;
	}
	c = (char*) e;
	if (c[8] == 0) {
		ok = 0;
	}
	if (c[2] == 0 && ok && *(int*) (c + 0x16c) != 0 && *(int*) (c + 0x184) != 0 &&
	    *(int*) (*(int*) (c + 0x184) + 0x2c) == *(int*) (*(int*) (c + 0x16c) + 1)) {
		return gm_IsEntityHomeInLocalShard(e);
	}
	return 0;
}
