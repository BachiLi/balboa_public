//zhengyu huang
#include "hw1.h"
#include "hw1_scenes.h"



using namespace hw1;


bool inCircle(Real x, Real y, Vector2 center, Real radius){
    return sqrt(pow(x - center.x, 2) + pow(y - center.y, 2)) < radius; // distance formula
}

bool inRectangle(Real x, Real y, Vector2 p_min, Vector2 p_max){
    return (x <= p_max.x && y <= p_max.y) && (x >= p_min.x && y >= p_min.y);
}

//return true if positive half otherwise false
bool halfPlane (Vector2 p0, Vector2 p1, Vector2 q){
    Vector2 p01 = p1 - p0;
    Vector2 n01 = Vector2{p01.y, -p01.x};
    return dot((q - p0), n01) <= 0;
}

bool inTriangle(Real x, Real y, Vector2 p0, Vector2 p1, Vector2 p2){
    Vector2 q = Vector2{x, y};
    return (halfPlane(p0, p1, q) &&  halfPlane(p1, p2, q) &&  halfPlane(p2, p0, q)) ||
            (! halfPlane(p0, p1, q) &&  ! halfPlane(p1, p2, q) &&  !halfPlane(p2, p0, q));
}


void paintCanvas(Image3* imgPtr,Real width, Real height, Vector3 color){
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            (*imgPtr)(x, y) = color;
        }
    }
}



Image3 hw_1_1(const std::vector<std::string> &params) {
    // Homework 1.1: render a circle at the specified
    // position, with the specified radius and color.

    
    Image3 img(640 /* width */, 480 /* height */);

    Vector2 center = Vector2{img.width / 2 + Real(0.5), img.height / 2 + Real(0.5)};
    Real radius = 100.0;
    Vector3 color = Vector3{0.5, 0.5, 0.5};
    Vector3 canvasColor = color;
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

    paintCanvas(&img, img.width, img.height, canvasColor);
    //if pixel center in circle, paint in in color
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            if (inCircle(x,y,center,radius)){
                img(x, y) = color;
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
    std::vector<Circle> primitives = scene.objects;

    paintCanvas(&img,scene.resolution.x, scene.resolution.y, scene.background);
    

    //render circles using rasterization style
    for (Circle circle : primitives){
        Vector2 center = circle.center;
        Real radius = circle.radius;
        Vector3 color = circle.color;
        // bounding box
        for (int y = center.y - radius; y < center.y + radius; y++){
            for (int x = center.x - radius; x < center.x + radius; x++){
                if(x >= 0 && y >= 0 && inCircle(x,y,center,radius)){
                    img(x,y) = color;
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
    std::vector<Shape> shapes = scene.shapes;
    
    Image3 img(scene.resolution.x, scene.resolution.y);
    paintCanvas(&img,scene.resolution.x, scene.resolution.y, scene.background);


    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            for (auto shape : shapes){
                if (auto *circle = std::get_if<Circle>(&shape)) {
                    if (inCircle(x, y, circle->center, circle->radius)){
                        img(x,y) = circle->color;
                    }
                } 
                else if (auto *rectangle = std::get_if<Rectangle>(&shape)) {
                    if (inRectangle(x, y, rectangle->p_min, rectangle->p_max)){
                        img(x, y) = rectangle->color;
                    }
                }
                else if (auto *triangle = std::get_if<Triangle>(&shape)) {
                    if (inTriangle(x, y, triangle->p0, triangle->p1, triangle->p2)){
                        img(x, y) = triangle->color;
                    }
                }
            }
        }
    }
    return img;
}

Vector3 coordObjSpace(Real x, Real y, Matrix3x3 transform){
    transform = inverse(transform);
    return transform * Vector3{x, y, 1.0};

}

Image3 hw_1_4(const std::vector<std::string> &params) {
    // Homework 1.4: render transformed shapes
    if (params.size() == 0) {
        return Image3(0, 0);
    }

    Scene scene = parse_scene(params[0]);
    std::cout << scene << std::endl;

    Image3 img(scene.resolution.x, scene.resolution.y);

    paintCanvas(&img,scene.resolution.x, scene.resolution.y, scene.background);
    auto shapes = scene.shapes;
        for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            for (auto shape : shapes){
                if (auto *circle = std::get_if<Circle>(&shape)) {
                    Vector3 objSpaceP = coordObjSpace(x, y, circle->transform);
                    if (inCircle(objSpaceP.x, objSpaceP.y, circle->center, circle->radius)){
                        img(x,y) = circle->color;
                    }
                } 
                else if (auto *rectangle = std::get_if<Rectangle>(&shape)) {
                    Vector3 objSpaceP = coordObjSpace(x, y, rectangle->transform);
                    if (inRectangle(objSpaceP.x, objSpaceP.y, rectangle->p_min, rectangle->p_max)){
                        img(x, y) = rectangle->color;
                    }
                }
                else if (auto *triangle = std::get_if<Triangle>(&shape)) {
                    Vector3 objSpaceP = coordObjSpace(x, y, triangle->transform);
                    if (inTriangle(objSpaceP.x, objSpaceP.y, triangle->p0, triangle->p1, triangle->p2)){
                        img(x, y) = triangle->color;
                    }
                }
            }
        }
    }
    return img;
}

// take a vector of color vectors and return the average color of all pixels
Vector3 averageColor(std::vector<Vector3> colorVector){
    int numSubpixel = size(colorVector);
    Real r = 0; Real g = 0; Real b = 0;
    for (auto color : colorVector){
        r += color.x;
        g += color.y;
        b += color.z;
    }
    return Vector3{r/numSubpixel, g/numSubpixel, b/numSubpixel};
}

// Homework 1.5: antialiasing
Image3 hw_1_5(const std::vector<std::string> &params) {
    if (params.size() == 0) {
        return Image3(0, 0);
    }

    Scene scene = parse_scene(params[0]);
    std::cout << scene << std::endl;

    Image3 img(scene.resolution.x, scene.resolution.y);

    //logic copied from 1_4
    paintCanvas(&img,scene.resolution.x, scene.resolution.y, scene.background);
    const int SSAA_X_FACTOR = 4;
    const int SSAA_Y_FACTOR = 4;
    auto shapes = scene.shapes;
    std::vector<Vector3> subPixels;
    Vector3 subPixel;
    for (Real y = 0; y < img.height; y++) {
    for (Real x = 0; x < img.width; x++) {
        // in this case, divide a pixel in to a 4x4 mosaic
        for (Real subY = y; subY< y + 1; subY += (1.0 / SSAA_Y_FACTOR)){
        for (Real subX = x; subX< x + 1; subX += (1.0 / SSAA_X_FACTOR)){
            subPixel = scene.background;
            for (auto shape : shapes){
                Vector3 objSpaceP;
                if (auto *circle = std::get_if<Circle>(&shape)) {
                    objSpaceP = coordObjSpace(subX, subY, circle->transform);
                    if (inCircle(objSpaceP.x, objSpaceP.y, circle->center, circle->radius)){
                        subPixel = circle->color;
                    }
                } 
                else if (auto *rectangle = std::get_if<Rectangle>(&shape)) {
                    objSpaceP = coordObjSpace(subX, subY, rectangle->transform);
                    if (inRectangle(objSpaceP.x, objSpaceP.y, rectangle->p_min, rectangle->p_max)){
                        subPixel = rectangle->color;
                    }
                }
                else if (auto *triangle = std::get_if<Triangle>(&shape)) {
                    objSpaceP = coordObjSpace(subX, subY, triangle->transform);
                    if (inTriangle(objSpaceP.x, objSpaceP.y, triangle->p0, triangle->p1, triangle->p2)){
                        subPixel = triangle->color;
                    }
                }
            }
            subPixels.push_back(subPixel);
        }}
        img(x, y) = averageColor(subPixels);
        subPixels.clear();
    }}
    
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

    //copied from 1_5
    paintCanvas(&img,scene.resolution.x, scene.resolution.y, scene.background);
    const int SSAA_X_FACTOR = 4;
    const int SSAA_Y_FACTOR = 4;
    auto shapes = scene.shapes;
    std::vector<Vector3> subPixels;
    Vector3 subPixel;
    for (Real y = 0; y < img.height; y++) {
    for (Real x = 0; x < img.width; x++) {
        // in this case, divide a pixel in to a 4x4 mosaic
        for (Real subY = y; subY< y + 1; subY += (1.0 / SSAA_Y_FACTOR)){
        for (Real subX = x; subX< x + 1; subX += (1.0 / SSAA_X_FACTOR)){
            subPixel = scene.background;
            for (auto shape : shapes){
                Vector3 objSpaceP;
                if (auto *circle = std::get_if<Circle>(&shape)) {
                    objSpaceP = coordObjSpace(subX, subY, circle->transform);
                    if (inCircle(objSpaceP.x, objSpaceP.y, circle->center, circle->radius)){
                        subPixel = circle->alpha * circle->color + (1 - circle->alpha) * subPixel;
                    }
                } 
                else if (auto *rectangle = std::get_if<Rectangle>(&shape)) {
                    objSpaceP = coordObjSpace(subX, subY, rectangle->transform);
                    if (inRectangle(objSpaceP.x, objSpaceP.y, rectangle->p_min, rectangle->p_max)){
                        subPixel = rectangle->alpha * rectangle->color + (1 - rectangle->alpha) * subPixel;
                    }
                }
                else if (auto *triangle = std::get_if<Triangle>(&shape)) {
                    objSpaceP = coordObjSpace(subX, subY, triangle->transform);
                    if (inTriangle(objSpaceP.x, objSpaceP.y, triangle->p0, triangle->p1, triangle->p2)){
                        subPixel = triangle->alpha * triangle->color + (1 - triangle->alpha) * subPixel;
                    }
                }
            }
            subPixels.push_back(subPixel);
        }}
        img(x, y) = averageColor(subPixels);
        subPixels.clear();
    }}
    
    return img;
}
