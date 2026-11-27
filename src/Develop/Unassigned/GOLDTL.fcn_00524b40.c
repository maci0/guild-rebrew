int __cdecl ls_LoadAvatarStates(void);

/* ADDRESS: GOLDTL 0x00524b40 */
int __cdecl ls_ReloadAvatarStatesWrapper(void)
{
	return ls_LoadAvatarStates();
}
