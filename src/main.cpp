#include "hw1.h"
#include "hw2.h"
#include "hw3.h"
#include "timer.h"
#include <vector>
#include <string>

int main(int argc, char *argv[]) {
    std::vector<std::string> parameters;
    std::string hw_num;
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-hw") {
            hw_num = std::string(argv[++i]);
        } else {
            parameters.push_back(std::string(argv[i]));
        }
    }

    if (hw_num == "1_1") {
        Image3 img = hw_1_1(parameters);
        imwrite("hw_1_1.png", img);
    } else if (hw_num == "1_2") {
        Timer timer;
        tick(timer);
        Image3 img = hw_1_2(parameters);
        std::cout << "hw_1_2 took " << tick(timer) << " seconds." << std::endl;
        imwrite("hw_1_2.png", img);
    } else if (hw_num == "1_3") {
        Image3 img = hw_1_3(parameters);
        imwrite("hw_1_3.png", img);
    } else if (hw_num == "1_4") {
        Image3 img = hw_1_4(parameters);
        imwrite("hw_1_4.png", img);
    } else if (hw_num == "1_5") {
        Image3 img = hw_1_5(parameters);
        imwrite("hw_1_5.png", img);
    } else if (hw_num == "1_6") {
        Image3 img = hw_1_6(parameters);
        imwrite("hw_1_6.png", img);
    } else if (hw_num == "2_1") {
        Image3 img = hw_2_1(parameters);
        imwrite("hw_2_1.png", img);
    } else if (hw_num == "2_2") {
        Image3 img = hw_2_2(parameters);
        imwrite("hw_2_2.png", img);
    } else if (hw_num == "2_3") {
        Image3 img = hw_2_3(parameters);
        imwrite("hw_2_3.png", img);
    } else if (hw_num == "2_4") {
        Image3 img = hw_2_4(parameters);
        imwrite("hw_2_4.png", img);
    } else if (hw_num == "3_1") {
        hw_3_1(parameters);
    } else if (hw_num == "3_2") {
        hw_3_2(parameters);
    } else if (hw_num == "3_3") {
        hw_3_3(parameters);
    } else if (hw_num == "3_4") {
        hw_3_4(parameters);
    }

    return 0;
}
