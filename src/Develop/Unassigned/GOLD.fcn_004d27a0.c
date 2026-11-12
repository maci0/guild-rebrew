#include <string.h>
/* DATA TODO: 0x9300a0, .data virtual tail, 0x2d0 zero-filled bytes. */
/* ADDRESS: GOLD 0x004d27a0 */
void __cdecl fcn_004d27a0(void)
{
    float *p, *q, scaled;
    int rows, column, group, row, start, remain;
    memset((void*) 0x9300a0, 0, 0x2d0);
	*(float*) 0x9300a0 = 10.0f;
	*(float*) 0x9300a4 = 10.0f;
	*(float*) 0x9300b0 = 30.0f;
	*(float*) 0x9300b4 = 50.0f;
	*(float*) 0x9300b8 = 40.0f;
	*(float*) 0x9300bc = 20.0f;
	*(float*) 0x9300c8 = 20.0f;
	*(float*) 0x9300cc = 20.0f;
	*(float*) 0x9300d0 = 80.0f;
	*(float*) 0x9300d4 = 20.0f;
	*(float*) 0x9300e0 = 0.0f;
	*(float*) 0x9300e4 = 0.0f;
	*(float*) 0x9300e8 = 70.0f;
	*(float*) 0x9300ec = 30.0f;
	*(float*) 0x9300f8 = 0.0f;
	*(float*) 0x9300fc = 0.0f;
	*(float*) 0x930100 = 50.0f;
	*(float*) 0x930104 = 50.0f;
	*(float*) 0x930110 = 0.0f;
	*(float*) 0x930114 = 0.0f;
	*(float*) 0x930118 = 10.0f;
	*(float*) 0x93011c = 10.0f;
	*(float*) 0x930128 = 30.0f;
	*(float*) 0x93012c = 50.0f;
	*(float*) 0x930130 = 80.0f;
	*(float*) 0x930134 = 20.0f;
	*(float*) 0x930140 = 0.0f;
	*(float*) 0x930144 = 0.0f;
	*(float*) 0x930148 = 80.0f;
	*(float*) 0x93014c = 20.0f;
	*(float*) 0x930158 = 0.0f;
	*(float*) 0x93015c = 0.0f;
	*(float*) 0x930160 = 60.0f;
	*(float*) 0x930164 = 40.0f;
	*(float*) 0x930170 = 0.0f;
	*(float*) 0x930174 = 0.0f;
	*(float*) 0x930178 = 50.0f;
	*(float*) 0x93017c = 50.0f;
	*(float*) 0x930188 = 0.0f;
	*(float*) 0x93018c = 0.0f;
	*(float*) 0x930190 = 5.0f;
	*(float*) 0x930198 = 5.0f;
	*(float*) 0x9301a0 = 20.0f;
	*(float*) 0x9301a4 = 70.0f;
	*(float*) 0x9301a8 = 50.0f;
	*(float*) 0x9301b0 = 10.0f;
	*(float*) 0x9301b8 = 20.0f;
	*(float*) 0x9301bc = 20.0f;
	*(float*) 0x9301c0 = 80.0f;
	*(float*) 0x9301c8 = 20.0f;
	*(float*) 0x9301d0 = 0.0f;
	*(float*) 0x9301d4 = 0.0f;
	*(float*) 0x9301d8 = 70.0f;
	*(float*) 0x9301e0 = 30.0f;
	*(float*) 0x9301e8 = 0.0f;
	*(float*) 0x9301ec = 0.0f;
	*(float*) 0x9301f0 = 50.0f;
	*(float*) 0x9301f8 = 50.0f;
	*(float*) 0x930200 = 0.0f;
	*(float*) 0x930204 = 0.0f;
	*(float*) 0x930208 = 20.0f;
	*(float*) 0x930210 = 80.0f;
	*(float*) 0x930218 = 0.0f;
	*(float*) 0x93021c = 0.0f;
	*(float*) 0x930220 = 30.0f;
	*(float*) 0x930228 = 70.0f;
	*(float*) 0x930230 = 0.0f;
	*(float*) 0x930234 = 0.0f;
	*(float*) 0x930238 = 40.0f;
	*(float*) 0x930240 = 60.0f;
	*(float*) 0x930248 = 0.0f;
	*(float*) 0x93024c = 0.0f;
	*(float*) 0x930250 = 60.0f;
	*(float*) 0x930260 = 0.0f;
	*(float*) 0x930264 = 0.0f;
	*(float*) 0x930278 = 0.0f;
	*(float*) 0x93027c = 0.0f;
	*(float*) 0x930288 = 0.0f;
	*(float*) 0x9302a0 = 0.0f;
	*(float*) 0x9302b8 = 0.0f;
	*(float*) 0x9302c0 = 0.0f;
	*(float*) 0x9302c4 = 0.0f;
	*(float*) 0x9302d0 = 0.0f;
	*(float*) 0x9302d8 = 0.0f;
	*(float*) 0x9302dc = 0.0f;
	*(float*) 0x9302e8 = 0.0f;
	*(float*) 0x9302f0 = 0.0f;
	*(float*) 0x9302f4 = 0.0f;
	*(float*) 0x930300 = 0.0f;
	*(float*) 0x930318 = 0.0f;
	*(float*) 0x930330 = 0.0f;
	*(float*) 0x930338 = 0.0f;
	*(float*) 0x93033c = 0.0f;
	*(float*) 0x930348 = 0.0f;
	*(float*) 0x930350 = 0.0f;
	*(float*) 0x930354 = 0.0f;
	*(float*) 0x930360 = 0.0f;
	*(float*) 0x930368 = 0.0f;
	*(float*) 0x93036c = 0.0f;
	*(float*) 0x930258 = 40.0f;
	*(float*) 0x930268 = 70.0f;
	*(float*) 0x930270 = 30.0f;
	*(float*) 0x930280 = 20.0f;
	*(float*) 0x930290 = 10.0f;
	*(float*) 0x930294 = 70.0f;
	*(float*) 0x930298 = 30.0f;
	*(float*) 0x9302a8 = 20.0f;
	*(float*) 0x9302ac = 50.0f;
	*(float*) 0x9302b0 = 100.0f;
	*(float*) 0x9302c8 = 100.0f;
	*(float*) 0x9302e0 = 100.0f;
	*(float*) 0x9302f8 = 20.0f;
	*(float*) 0x930308 = 10.0f;
	*(float*) 0x93030c = 70.0f;
	*(float*) 0x930310 = 30.0f;
	*(float*) 0x930320 = 20.0f;
	*(float*) 0x930324 = 50.0f;
	*(float*) 0x930328 = 100.0f;
	*(float*) 0x930340 = 100.0f;
	*(float*) 0x930358 = 100.0f;
    p = (float*) 0x9300a0;
    do {
        rows = 5;
        do {
            column = 0;
            do {
                scaled = (float) (*p * 0.01);
                *p = scaled;
                if (column)
                    *p = scaled + p[-1];
                ++column;
                ++p;
            } while (column < 6);
        } while (--rows);
    } while ((int) p < 0x930370);
    for (group = 0; group < 30; group += 5) {
        for (row = 0; row < 5; ++row) {
            for (start = 1; start <= 6; ++start) {
                if (start < 6) {
                    p = (float*) 0x9300a0 + (group + row) * 6 + start;
                    q = p - 1;
                    remain = 6 - start;
                    do {
                        if (*p == *q)
                            *p = 0.0f;
                        ++p;
                    } while (--remain);
                }
            }
        }
    }
}
