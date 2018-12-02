#pragma once

struct LemonToken {
    LemonToken() = default;
    int type = 0;
    char* id = nullptr;
    double value = 0;
};

typedef struct LemonToken LemonToken;