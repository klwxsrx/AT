#pragma once

struct LemonToken {
    unsigned type = 0;
    char* id = nullptr;
    double value = 0;
};

typedef struct LemonToken LemonToken;