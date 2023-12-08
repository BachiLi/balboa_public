#pragma once

#include "balboa.h"

#include <chrono>
#include <ctime>

/// For measuring how long an operation takes.
/// C++ chrono unfortunately makes the whole type system very complicated.
struct Timer {
    std::chrono::time_point<std::chrono::system_clock> last;
};

inline Real tick(Timer &timer) {
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = now - timer.last;
    Real ret = elapsed.count();
    timer.last = now;
    return ret;
}

/*
Example usage:

Timer timer;
tick(timer);
std::cout << "Parsing and constructing scene " << filename << "." << std::endl;
Scene scene = parse_scene(filename, embree_device);
std::cout << "Done. Took " << tick(timer) << " seconds." << std::endl;
std::cout << "Rendering..." << std::endl;
Image3 img = render(scene);
std::cout << "Done. Took " << tick(timer) << " seconds." << std::endl;
*/
