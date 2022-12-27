#include "image.h"

int main() {
    const int imh = 100, imw = 100;
    image im(imh, imw);
    for (int y = 0; y < imh; y++) {
        for (int x = 0; x < imw; x++) {
            im(y, x) = {(real)y / imh, (real)x / imw, 0};
        }
    }
    im.write_png("image.png");
}
