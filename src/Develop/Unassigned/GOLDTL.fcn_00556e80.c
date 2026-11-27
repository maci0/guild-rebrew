


int __cdecl gm_IsEntityHomeInLocalShard(unsigned short*);
int __cdecl gm_IsLocalSimEntity(unsigned short*);

int __cdecl he_IsEntityEligibleForIllness(unsigned short* e)
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
	if (gm_IsEntityHomeInLocalShard(e)) {
		return 1;
	}
	return gm_IsLocalSimEntity(e) != 0;
}
