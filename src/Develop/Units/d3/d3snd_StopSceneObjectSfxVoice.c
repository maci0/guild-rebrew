extern char g_6a1f7c[];
/* fcn_00515f30 — tail-call the notifier when the record is present. */

int __cdecl fcn_0064f170(int, int, int);
void __cdecl d3snd_StopSourceVoiceSafe(int);

/* ADDRESS: GOLDTL 0x00515f30 */
/* ADDRESS: GOLDDE 0x005009a0 */
void __cdecl d3snd_StopSceneObjectSfxVoice(int record)
{
	if (fcn_0064f170(record, (int) &g_6a1f7c, 4) != 0) {
		return;
	}
	if (*(int*) (record + 0x210) == 0) {
		return;
	}
	d3snd_StopSourceVoiceSafe(*(int*) (record + 0x210));
}
