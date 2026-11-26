

void* __cdecl fcn_00445600(int a, int b, int c, int d);
void* __cdecl sb_PrepareVoice(int a, int b);
int __cdecl d3snd_AttachSoundSource(void* a, void* b, int c, int d);

int __cdecl fcn_00418d20(int a1, int a2, int a3, int a4)
{
	void* p;
	void* q;
	int result;

	result = 0;
	p = fcn_00445600(0, 0x140, 0, a2);
	if (p != 0) {
		q = sb_PrepareVoice(0, a1);
		if (q != 0) {
			result = d3snd_AttachSoundSource(q, p, a3, a4);
		}
	}
	return result;
}
