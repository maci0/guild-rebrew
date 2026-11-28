extern char d3_ActiveScene[];

int __cdecl d3_VisitSceneObjectsUntilStopped(int, int, int, int, int);
void __cdecl d3_VisitSceneObjects(int, int, int, int, int);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x0043d690 */
void __cdecl d3_VisitObjectAttachments(int a, int b)
{
	if (a != 0) {
		d3_VisitSceneObjectsUntilStopped(*(int*) 0x5fb5b0, a, 0x240, 0x43d630, b);
	}
}
#else
/* ADDRESS: GOLDTL 0x0043a5a0 */
void __cdecl d3_VisitObjectAttachments(int a1, int a2)
{
	if (a1 == 0) {
		return;
	}
	d3_VisitSceneObjects(*(int*) &d3_ActiveScene, a1, 0x240, 0x43a540, a2);
}
#endif
