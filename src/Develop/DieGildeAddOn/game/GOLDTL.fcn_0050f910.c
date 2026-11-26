extern unsigned char g_773d75;



char* __cdecl gm_GetGuildHall(int);
char* __cdecl fcn_00502cd0(int, int, int, ...);
void __cdecl fcn_004c51a0(int, int, char, int);

void __cdecl gm_CreditCityTreasury(int amount)
{
	char* e;
	char* r;

	e = gm_GetGuildHall(1);
	r = fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x115);
	fcn_004c51a0(-1, *(int*) (r + 2), (*(char*)&g_773d75), amount);
}
