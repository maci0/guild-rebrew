void __cdecl d2_Plot(int, int, int, int, int);

/* ADDRESS: GOLD 0x004764e0 */
void __cdecl d2_DrawLine(int x, int y, int x1, int y1, int red, int green, int blue)
{
    int dx, dy;
    int sx, sy;
    int error, straight;
    int diagonal, t;

    if (y == y1) {
        if (x1 < x) { t = x - x1;
            for (; t > 0; t--) { d2_Plot(x1++, y, red, green, blue); }
        } else { t = x1 - x;
            for (; t > 0; t--) { d2_Plot(x++, y, red, green, blue); }
        }
        return;
    }
    if (x == x1) {
        if (y1 < y) { t = y - y1;
            for (; t > 0; t--) { d2_Plot(x, y1++, red, green, blue); }
        } else { t = y1 - y;
            for (; t > 0; t--) { d2_Plot(x, y++, red, green, blue); }
        }
        return;
    }
    if (x < x1) { dx = x1; sx = 1; dx -= x; }
    else { dx = x; sx = -1; dx -= x1; }
    if (y < y1) { sy = 1; dy = y1; dy -= y; }
    else { dy = y; sy = -1; dy -= y1; }
    d2_Plot(x, y, red, green, blue);
    if (dx > dy) {
        diagonal = dy - dx;
        straight = dy + dy;
        error = straight - dx; diagonal += diagonal;
        do {
            x += sx;
            if (error >= 0) { y += sy; error += diagonal; }
            else error += straight;
            d2_Plot(x, y, red, green, blue);
        } while (x != x1);
    } else {
        diagonal = dx - dy;
        straight = dx + dx;
        error = straight - dy; diagonal += diagonal;
        do {
            y += sy;
            if (error >= 0) { x += sx; error += diagonal; }
            else error += straight;
            d2_Plot(x, y, red, green, blue);
        } while (y != y1);
    }
}
