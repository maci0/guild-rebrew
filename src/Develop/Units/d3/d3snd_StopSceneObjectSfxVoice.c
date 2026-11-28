/* fcn_00515f30 — tail-call the notifier when the record is present. */

int __cdecl fcn_0064f170(int, int, int);
void __cdecl d3snd_StopSourceVoiceSafe(int);

/* ADDRESS: GOLDTL 0x00515f30 */
void __cdecl d3snd_StopSceneObjectSfxVoice(int record)
{
	if (fcn_0064f170(record, 0x6a1f7c, 4) != 0) {
		return;
	}
	if (*(int*) (record + 0x210) == 0) {
		return;
	}
	d3snd_StopSourceVoiceSafe(*(int*) (record + 0x210));
}
