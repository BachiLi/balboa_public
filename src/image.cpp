#include "image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "3rdparty/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "3rdparty/stb_image_write.h"
#include "flexception.h"
#include <algorithm>
#include <fstream>

using std::string;
using std::vector;

// Stolen from https://github.com/halide/Halide/blob/c6529edb23b9fab8b406b28a4f9ea05b08f81cfe/src/Util.cpp#L253
inline bool ends_with(const string &str, const string &suffix) {
    if (str.size() < suffix.size()) {
        return false;
    }
    size_t off = str.size() - suffix.size();
    for (size_t i = 0; i < suffix.size(); i++) {
        if (str[off + i] != suffix[i]) {
            return false;
        }
    }
    return true;
}

Image1 imread1(const fs::path &filename) {
    Image1 img;
    std::string extension = to_lowercase(filename.extension().string());
    // JPG, PNG, TGA, BMP, PSD, GIF, HDR, PIC
    if (extension == ".jpg" ||
          extension == ".png" ||
          extension == ".tga" ||
          extension == ".bmp" ||
          extension == ".psd" ||
          extension == ".gif" ||
          extension == ".hdr" ||
          extension == ".pic") {
        int w, h, n;
        float* data = stbi_loadf(filename.string().c_str(), &w, &h, &n, 1);
        img = Image1(w, h);
        if (data == nullptr) {
            Error(std::string("Failure when loading image: ") + filename.string());
        }
        for (int i = 0; i < w * h; i++) {
            img(i) = data[i];
        }
        stbi_image_free(data);
    } else {
        Error(std::string("Unsupported image format: ") + filename.string());
    }
    return img;
}

Image3 imread3(const fs::path &filename) {
    Image3 img;
    std::string extension = to_lowercase(filename.extension().string());
    // JPG, PNG, TGA, BMP, PSD, GIF, HDR, PIC
    if (extension == ".jpg" ||
          extension == ".png" ||
          extension == ".tga" ||
          extension == ".bmp" ||
          extension == ".psd" ||
          extension == ".gif" ||
          extension == ".hdr" ||
          extension == ".pic") {
        int w, h, n;
        float* data = stbi_loadf(filename.string().c_str(), &w, &h, &n, 3);
        img = Image3(w, h);
        if (data == nullptr) {
            Error(std::string("Failure when loading image: ") + filename.string());
        }
        int j = 0;
        for (int i = 0; i < w * h; i++) {
            img(i)[0] = data[j++];
            img(i)[1] = data[j++];
            img(i)[2] = data[j++];
        }
        stbi_image_free(data);
    } else {
        Error(std::string("Unsupported image format: ") + filename.string());
    }
    return img;
}

void imwrite(const fs::path &filename, const Image3 &image) {
    if (image.data.empty()) {
        return;
    }

    std::string extension = to_lowercase(filename.extension().string());
    if (extension == ".png" ||
            extension == ".bmp" ||
            extension == ".tga" ||
            extension == ".jpg") {
        int w = image.width;
        int h = image.height;
        Image3uc image_uc(w, h);
        for (int i = 0; i < (int)image.data.size(); i++) {
            Real rf = image.data[i].x;
            Real gf = image.data[i].y;
            Real bf = image.data[i].z;
            uint8_t r = (uint8_t)std::clamp(
                int(std::pow(rf, (Real)(1/2.2)) * 255 + Real(0.5)),
                0, 255);
            uint8_t g = (uint8_t)std::clamp(
                int(std::pow(gf, (Real)(1/2.2)) * 255 + Real(0.5)),
                0, 255);
            uint8_t b = (uint8_t)std::clamp(
                int(std::pow(bf, (Real)(1/2.2)) * 255 + Real(0.5)),
                0, 255);
            image_uc.data[i] = Vector3uc{r, g, b};
        }
        if (extension == ".png") {
            int stride_in_bytes = 3 * image.width;
            stbi_write_png(filename.string().c_str(), w, h, 3 /* comp */,
                           image_uc.data.data(), stride_in_bytes);
        } else if (extension == ".bmp") {
            stbi_write_bmp(filename.string().c_str(), w, h, 3 /* comp */,
                           image_uc.data.data());
        } else if (extension == ".tga") {
            stbi_write_tga(filename.string().c_str(), w, h, 3 /* comp */,
                           image_uc.data.data());
        } else if (extension == ".jpg") {
            stbi_write_jpg(filename.string().c_str(), w, h, 3 /* comp */,
                           image_uc.data.data(), 100 /* quality */);
        }
    } else {
        Error(std::string("Unsupported image format: ") + filename.string());
    }
}
