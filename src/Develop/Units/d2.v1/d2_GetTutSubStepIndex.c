extern char d2_TutorialState[];
/* ADDRESS: GOLDTL 0x0057fbb0 */
/* ADDRESS: GOLDDE 0x00565950 */
int __cdecl d2_GetTutSubStepIndex(void)
{
	return *(int*) (*(int*) &d2_TutorialState + 0x38);
}
