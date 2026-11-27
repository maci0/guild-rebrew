

// fcn_005049c0 — boolean fcn_0050b010(arg).

int __cdecl gm_GetGuildHall(int);

int __cdecl gm_HasGuildHall(int guild)
{
	return gm_GetGuildHall(guild) != 0;
}
