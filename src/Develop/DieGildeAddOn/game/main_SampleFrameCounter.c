extern int main_FrameCounter;
extern float main_FrameRate;


/* ADDRESS: GOLDTL 0x00525e90 */
/* ADDRESS: GOLDDE 0x0050f150 */
void __cdecl main_SampleFrameCounter(void)
{
	float f;

	f = (float) main_FrameCounter;
	main_FrameCounter = 0;
	main_FrameRate = f;
}
