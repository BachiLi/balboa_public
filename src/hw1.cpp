#include "hw1.h"

Image3 hw_1_1(const std::vector<std::string> &params) {
    Image3 img(640 /* width */, 480 /* height */);

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            img(x, y) = Vector3{1, 1, 1};
        }
    }
    return img;
}
