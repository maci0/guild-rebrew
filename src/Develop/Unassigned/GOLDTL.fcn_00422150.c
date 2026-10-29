extern int g_6b7d7c;
extern int g_6b7e8c;
extern int g_6b7e88;
extern int g_6b7e90;
extern int g_678de8;
extern int g_678dec;
extern volatile int g_6b7fac;

extern int __cdecl fcn_0042aaa0(int a0);
extern void __cdecl fcn_0042a920(int a0, int a1);
extern void __cdecl fcn_0042a880(int a0);
extern void __cdecl fcn_004237f0(void *a0, int a1);
extern void __cdecl fcn_00423670(void *a0, int a1, int a2);

typedef struct
{
    int obj;
    int ptr04;
    int ptr08;
    int count0c;
    int start10;
    int flags14;
    int limit18;
    int stamp1c;
    int pad20;
    int speed24;
    int pad28;
    void (__cdecl *callback)(void *self);
} PART;

/* ADDRESS: GOLDTL 0x00422150 */
void __cdecl fcn_00422150(void)
{
    int now;
    PART *p;
    int i;
    int off;
    unsigned int value;
    int dt;

    if (g_6b7d7c == 0)
        return;
    if (g_6b7e90 == 0)
    {
        if (g_678de8 == 0)
            return;
        now = g_6b7fac * 8 + g_6b7fac * 4 + g_6b7fac;
        i = 0;
        if (g_6b7e8c <= 0)
            return;
        off = 0;
        do
        {
            p = (PART *)(g_6b7e88 + off);
            if (p->ptr04 != 0)
            {
                if (p->flags14 & 0x10)
                {
                    *(int *)(p->ptr04 + 0x3c) = now;
                    p->ptr08 = now;
                }
                if (fcn_0042aaa0(p->obj) == 4)
                {
                    if (p->flags14 & 3)
                    {
                        dt = now - p->start10;
                        if ((unsigned int)dt < (unsigned int)g_678de8)
                        {
                            if (p->flags14 & 1)
                                fcn_0042a920(p->obj, (int)((float)(unsigned int)dt / g_678de8 * p->speed24));
                            else
                                fcn_0042a920(p->obj, (int)((float)(unsigned int)(p->start10 - now + g_678de8) / g_678de8 * p->speed24));
                        }
                        else if (p->flags14 & 2)
                        {
                            fcn_0042a880(p->obj);
                            p->flags14 = p->flags14 | 8;
                            p->start10 = 0;
                            p->flags14 = p->flags14 & 0xfc;
                        }
                        else
                        {
                            fcn_0042a920(p->obj, p->speed24);
                            p->flags14 = p->flags14 & 0xfc;
                            p->start10 = 0;
                        }
                    }
                }
                else if (p->limit18 != 0 && p->count0c != 1 && (p->flags14 & 0xe) == 0)
                {
                    if (p->stamp1c == 0)
                        p->stamp1c = g_6b7fac * 8 + g_6b7fac * 4 + g_6b7fac;
                    else if ((unsigned int)(p->stamp1c + p->limit18) <
                             (unsigned int)(g_6b7fac * 8 + g_6b7fac * 4 + g_6b7fac))
                    {
                        if (p->count0c != 0)
                            p->count0c--;
                        fcn_00423670(p, 0, p->limit18);
                    }
                }
                else if (p->callback != 0)
                {
                    p->callback(p);
                    p->callback = 0;
                }
            }
            i++;
            off = off + 0x30;
        } while (i < g_6b7e8c);
    }
    else
    {
        now = g_6b7fac * 8 + g_6b7fac * 4 + g_6b7fac;
        i = 0;
        value = 1;
        if (g_6b7e8c > 0)
        {
            off = 0;
            do
            {
                p = (PART *)(g_6b7e88 + off);
                if (p->ptr04 != 0 && fcn_0042aaa0(p->obj) == 4)
                {
                    value = 0;
                    now = g_6b7fac * 8 + g_6b7fac * 4 + g_6b7fac;
                    value = (unsigned int)(now - p->start10);
                    if (value < (unsigned int)g_678dec)
                        fcn_0042a920(p->obj,
                            (int)((float)value / g_678dec * p->speed24));
                    else
                        fcn_004237f0(p, 0);
                }
                i++;
                off = off + 0x30;
            } while (i < g_6b7e8c);
        }
        g_6b7e90 = value == 0 ? 1 : 0;
    }
}
