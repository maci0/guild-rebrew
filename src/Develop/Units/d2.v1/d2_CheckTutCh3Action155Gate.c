


extern int* d2_TutorialState;

int __cdecl d2_CheckTutMsg1aNotCat12Node74(int* m);

int __cdecl d2_CheckTutCh3Action155Gate(int* m)
{
	if (m[0] == 0x20) {
		if (m[3] == 0x155 && d2_TutorialState[15] == 3) {
			return 1;
		}
		return 0;
	}
	return d2_CheckTutMsg1aNotCat12Node74(m);
}
