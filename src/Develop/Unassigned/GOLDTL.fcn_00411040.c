

int __cdecl sb_StopVoice(int, int);

int __cdecl StopSample(int* p)
{
	sb_StopVoice(*p, 0);
	return 0;
}
