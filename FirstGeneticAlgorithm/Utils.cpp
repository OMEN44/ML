#include <random>
#include "Utils.h"

Utils::Utils() {
    srand(time(0));
}

float Utils::randF(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

float Utils::randF(float max) {
    return static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / max));
}

int Utils::randI(int min, int max) {
    return static_cast<int>(rand()) / (static_cast<int>(RAND_MAX / (max - min)));
}

int Utils::randI(int max) {
    return static_cast<int>(rand()) / (static_cast<int>(RAND_MAX / max));
}