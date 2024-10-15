#include "hw1.h"
#include "hw1_scenes.h"

using namespace hw1;

Image3 hw_1_1(const std::vector<std::string> &params) {
    // Homework 1.1: render a circle at the specified
    // position, with the specified radius and color.

    Image3 img(640 /* width */, 480 /* height */);

    Vector2 center = Vector2{img.width / 2 + Real(0.5), img.height / 2 + Real(0.5)};
    Real radius = 100.0;
    Vector3 color = Vector3{1.0, 0.5, 0.5};

    for (int i = 0; i < (int)params.size(); i++) {
        if (params[i] == "-center") {
            Real x = std::stof(params[++i]);
            Real y = std::stof(params[++i]);
            center = Vector2{x, y};
        } else if (params[i] == "-radius") {
            radius = std::stof(params[++i]);
        } else if (params[i] == "-color") {
            Real r = std::stof(params[++i]);
            Real g = std::stof(params[++i]);
            Real b = std::stof(params[++i]);
            color = Vector3{r, g, b};
        }
    }
    
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            Real px = x + 0.5;
            Real py = y + 0.5;

            // Calculate the difference between the pixel center and the circle's center
            Real dx = px - center.x;
            Real dy = py - center.y;

            // Calculate the squared distance from the pixel center to the circle's center
            Real distance_squared = dx * dx + dy * dy;

            // Compare squared distance with the squared radius
            if (distance_squared <= radius * radius) {
                img(x, y) = color;  // Pixel center is inside the circle
            } else {
                img(x, y) = Vector3{0.5, 0.5, 0.5};  // Pixel center is outside the circle
            }
        }
    }
    return img;
}

Image3 hw_1_2(const std::vector<std::string> &params) {
    // Homework 1.2: render multiple circles
    if (params.size() == 0) {
        return Image3(0, 0);
    }

    int scene_id = std::stoi(params[0]);
    const CircleScene &scene = hw1_2_scenes[scene_id];

    Image3 img(scene.resolution.x, scene.resolution.y);

    std::vector<Real> min_distance_squared_buffer(img.width * img.height, std::numeric_limits<Real>::max());

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            img(x, y) = Vector3{0.5, 0.5, 0.5};
        }
    }

    for (const Circle &circle : scene.objects) {
        Vector2 center = circle.center;
        Real radius = circle.radius;
        Vector3 circle_color = circle.color;
        for (int y = 0; y < img.height; y++) {
            for (int x = 0; x < img.width; x++) {
                Real px = x + 0.5;
                Real py = y + 0.5;

                // Calculate the difference between the pixel center and the circle's center
                Real dx = px - center.x;
                Real dy = py - center.y;

                // Calculate the squared distance from the pixel center to the circle's center
                Real distance_squared = dx * dx + dy * dy;
                if (distance_squared <= radius * radius) {
                    // Calculate pixel index in the buffer

                    int pixel_index = y * img.width + x;

                    // If this circle is closer than the previously closest circle, update the pixel
                    if (distance_squared < min_distance_squared_buffer[pixel_index]) {
                        img(x, y) = circle_color;  // Overwrite pixel color
                        min_distance_squared_buffer[pixel_index] = distance_squared;  // Update the buffer with the new closest distance
                    }
                }
            }
        }
    }
    return img;
}

Image3 hw_1_3(const std::vector<std::string> &params) {
    // Homework 1.3: render multiple shapes
    if (params.size() == 0) {
        return Image3(0, 0);
    }

    Scene scene = parse_scene(params[0]);
    std::cout << scene << std::endl;

    Image3 img(scene.resolution.x, scene.resolution.y);

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            img(x, y) = Vector3{1, 1, 1};
        }
    }
    return img;
}

Image3 hw_1_4(const std::vector<std::string> &params) {
    // Homework 1.4: render transformed shapes
    if (params.size() == 0) {
        return Image3(0, 0);
    }

    Scene scene = parse_scene(params[0]);
    std::cout << scene << std::endl;

    Image3 img(scene.resolution.x, scene.resolution.y);

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            img(x, y) = Vector3{1, 1, 1};
        }
    }
    return img;
}

Image3 hw_1_5(const std::vector<std::string> &params) {
    // Homework 1.5: antialiasing
    if (params.size() == 0) {
        return Image3(0, 0);
    }

    Scene scene = parse_scene(params[0]);
    std::cout << scene << std::endl;

    Image3 img(scene.resolution.x, scene.resolution.y);

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            img(x, y) = Vector3{1, 1, 1};
        }
    }
    return img;
}

Image3 hw_1_6(const std::vector<std::string> &params) {
    // Homework 1.6: alpha blending
    if (params.size() == 0) {
        return Image3(0, 0);
    }

    Scene scene = parse_scene(params[0]);
    std::cout << scene << std::endl;

    Image3 img(scene.resolution.x, scene.resolution.y);

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            img(x, y) = Vector3{1, 1, 1};
        }
    }
    return img;
}
