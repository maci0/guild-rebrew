/* Each record stores a kind and nine float adjustments (40 bytes). */
struct TypeAdjustment {
    int kind;
    float adjustments[9];
};

// GLOBAL: SERVER 0x10025340
const struct TypeAdjustment g_type_adjustments[15] = {
    {11, {0.0f, -3.0f, -5.0f, -3.0f, -8.0f, -8.0f, -12.0f, 0.0f, -15.0f}},
    {12, {0.0f, -3.0f, -5.0f, -3.0f, -8.0f, -8.0f, -12.0f, 0.0f, -15.0f}},
    {13, {0.0f, -3.0f, -3.0f, -3.0f, -5.0f, -10.0f, -10.0f, 0.0f, -15.0f}},
    {14, {0.0f, -5.0f, -5.0f, -5.0f, -8.0f, -12.0f, -12.0f, 0.0f, -15.0f}},
    {1, {0.0f, 5.0f, 5.0f, 5.0f, 5.0f, 3.0f, 0.0f, 0.0f, -15.0f}},
    {2, {0.0f, 5.0f, 5.0f, 5.0f, 5.0f, 3.0f, 0.0f, 0.0f, -15.0f}},
    {3, {0.0f, 5.0f, 5.0f, 5.0f, 5.0f, 3.0f, 0.0f, 0.0f, -15.0f}},
    {15, {0.0f, 5.0f, 5.0f, 5.0f, 5.0f, 3.0f, 0.0f, 0.0f, -15.0f}},
    {7, {0.0f, 3.0f, 3.0f, -5.0f, -8.0f, 10.0f, 0.0f, 0.0f, -15.0f}},
    {4, {0.0f, 3.0f, 5.0f, 5.0f, 0.0f, -5.0f, -5.0f, 0.0f, -15.0f}},
    {8, {0.0f, 5.0f, -5.0f, 5.0f, 5.0f, -5.0f, -5.0f, 0.0f, -15.0f}},
    {6, {0.0f, 5.0f, 0.0f, -5.0f, 0.0f, -12.0f, -5.0f, 0.0f, -15.0f}},
    {5, {0.0f, 5.0f, 0.0f, 0.0f, 0.0f, -10.0f, -5.0f, 0.0f, -15.0f}},
    {9, {0.0f, 5.0f, 5.0f, 5.0f, 0.0f, -10.0f, -10.0f, 0.0f, -15.0f}},
    {10, {0.0f, 5.0f, 10.0f, 5.0f, 5.0f, 5.0f, 5.0f, 0.0f, -15.0f}},
};

// GLOBAL: SERVER 0x10025598
const int g_type_adjustments_count = 15;

// GLOBAL: SERVER 0x100255a0
const struct TypeAdjustment g_type_adjustments_secondary[5] = {
    {35, {-15.0f, -10.0f, -10.0f, -10.0f, 0.0f, -5.0f, 0.0f, 0.0f, 0.0f}},
    {36, {-15.0f, -10.0f, -10.0f, -10.0f, -5.0f, 0.0f, 0.0f, 0.0f, 0.0f}},
    {37, {-15.0f, -10.0f, -10.0f, -10.0f, -5.0f, -5.0f, 0.0f, 0.0f, 0.0f}},
    {39, {-20.0f, -15.0f, -15.0f, -15.0f, -10.0f, -5.0f, -5.0f, 0.0f, 0.0f}},
    {38, {-20.0f, -15.0f, -15.0f, -15.0f, -5.0f, -10.0f, -5.0f, 0.0f, 0.0f}},
};

// GLOBAL: SERVER 0x10025668
const int g_type_adjustments_secondary_count = 5;

// GLOBAL: SERVER 0x1002566c
const float g_type_multipliers[5] = {1.100000023841858f, 1.0499999523162842f, 1.0f, 0.949999988079071f, 0.8999999761581421f};
