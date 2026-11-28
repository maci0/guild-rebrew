

// fcn_005049c0 — boolean fcn_0050b010(arg).

int __cdecl gm_GetGuildHall(int);

/* ADDRESS: GOLDDE 0x004f2b90 */
int __cdecl gm_HasGuildHall(int guild)
{
	return gm_GetGuildHall(guild) != 0;
}
