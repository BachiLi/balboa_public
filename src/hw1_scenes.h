#pragma once

struct Circle {
    Vector2 center;
    Real radius;
    Vector3 color;
};

struct CircleScene {
    Vector2i resolution;
    Vector3 background;
    std::vector<Circle> objects;
};

CircleScene hw1_2_scene_0 = {
    {640, 360}, // resolution
    {0.5, 0.5, 0.5}, // background
    { // center, radius, color
        {{320, 180}, 160, {0.3, 0.5, 0.8}},
        {{150,  80},  80, {0.8, 0.3, 0.5}},
        {{490,  80},  80, {0.8, 0.3, 0.5}},
    }
};

CircleScene hw1_2_scenes[] = {
    hw1_2_scene_0
};
