extern int g_67a370;

char __cdecl fcn_00438d40(char *scene, char *node, unsigned int flags, int cb, void *ctx);

/* ADDRESS: GOLD 0x004d0ca0 */
/* Caller 0x4d1510 pushes nothing and does not read the return.
 * 0x6f0d58 and 0x4d0a80 have no declaration, so they stay raw views. */
void __cdecl fcn_004d0ca0(void)
{
	char *scene;

	scene = (char *)g_67a370;
	*(int *)0x6f0d58 = 0;
	fcn_00438d40(scene, 0, 0x100, 0x4d0a80, 0);
}
