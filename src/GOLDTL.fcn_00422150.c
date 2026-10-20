extern int g_6b7d7c;
extern int g_6b7e8c;
extern int g_6b7e88;
extern int g_6b7e90;
extern int g_678de8;
extern int g_678dec;
extern int g_6b7fac;

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
    int i;
    int n;
    int now;
    int off;
    int next;
    int keep;
    PART *p;
    unsigned int value;

    if (g_6b7d7c == 0)
        return;
    if (g_6b7e90 != 0)
    {
        i = 0;
        keep = 1;
        if (g_6b7e8c > 0)
        {
            do
            {
                p = (PART *)(g_6b7e88 + i * 0x30);
                if (p->ptr04 != 0 && fcn_0042aaa0(p->obj) == 4)
                {
                    keep = 0;
                    value = (unsigned int)(g_6b7fac * 8 + g_6b7fac * 4 + g_6b7fac) - (unsigned int)p->start10;
                    if (value >= (unsigned int)g_678dec)
                        fcn_004237f0(p, 0);
                    else
                        fcn_0042a920(p->obj,
                            (int)((float)value / g_678dec * p->speed24));
                }
                i++;
            } while (i < g_6b7e8c);
        }
        g_6b7e90 = keep == 0 ? 0 : 1;
        return;
    }
    if (g_678de8 == 0)
        return;
    keep = 0;
    now = g_6b7fac * 8 + g_6b7fac * 4 + g_6b7fac;
    if (g_6b7e8c <= 0)
        return;
    off = 0;
    next = 0;
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
                    if ((unsigned int)(now - p->start10) < (unsigned int)g_678de8)
                    {
                        if (p->flags14 & 1)
                            value = (unsigned int)((float)(unsigned int)(now - p->start10) / g_678de8 * p->speed24);
                        else
                            value = (unsigned int)((float)(unsigned int)(p->start10 - now + g_678de8) / g_678de8 * p->speed24);
                        fcn_0042a920(p->obj, (int)value);
                    }
                    else if (p->flags14 & 2)
                    {
                        fcn_0042a880(p->obj);
                        p->flags14 = (p->flags14 | 8) & 0xfc;
                        p->start10 = 0;
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
        keep++;
        off = next + 0x30;
        next = off;
    } while (keep < g_6b7e8c);
}
