#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include <set>
#include <map>
#include <queue>


class timer {
public:
    timer(std::string point) : m_point{ point } {
        m_start_point = std::chrono::high_resolution_clock::now();
    }

    ~timer() {
        auto endclock = std::chrono::high_resolution_clock::now();
        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_start_point).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endclock).time_since_epoch().count();

        auto duration = end - start;
        double ms = duration * 0.001;

        std::cout << "time used by : " << m_point << " was : " << ms << " ms" << std::endl;

    }

private:
    std::string m_point;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start_point;
};


int8_t get_weight(uint16_t freq, uint16_t idx) {
    static int8_t arr[]{ 0,1,0,-1 };
    if (freq == 0) {
        return 0;
    }
    else {
        return arr[(idx / freq) % 4];
    }
}

void task_1(std::vector <int16_t> input) {

    std::vector<int16_t> tmp;
    input.insert(input.begin(), 0);

    tmp = input;

    for (uint8_t iter{}; iter < 100; ++iter) {
        for (uint16_t out_idx{ 1 }; out_idx < input.size(); ++out_idx) {
            int32_t sum{};

            for (uint16_t in_idx{ out_idx }; in_idx < input.size(); ++in_idx) {
                sum += input[in_idx] * get_weight(out_idx, in_idx);
            }
            tmp[out_idx] = std::abs(sum) % 10;
        }
        input = tmp;
    }

    input.erase(input.begin());
    std::cout << "task 1 first 8 digit are :";
    for (uint8_t idx{}; idx < 8; ++idx) {
        std::cout << input[idx];
    }
    std::cout << std::endl;


}

void task_2(std::vector <int16_t> p_input, uint32_t p_offest) {

    std::vector <int16_t> augmeneted_input{};

    for (uint16_t idx{}; idx < 10000; ++idx) {
        augmeneted_input.insert(augmeneted_input.end(), p_input.begin(), p_input.end());
    }

    for (uint16_t idx = 0; idx < 100; ++idx) {
        uint32_t partial_sum{};

        for (uint32_t accum{ p_offest }; accum < augmeneted_input.size(); ++accum) {
            partial_sum += augmeneted_input[accum];
        }

        for (uint32_t inner_idx{ p_offest }; inner_idx < augmeneted_input.size(); ++inner_idx) {
            auto temp = augmeneted_input[inner_idx];
            augmeneted_input[inner_idx] = partial_sum % 10;

            partial_sum -= temp;
        }
    }

    std::cout << "task 2 output is : ";
    for (uint8_t i = 0; i < 8; ++i){
        std::cout << static_cast<uint16_t>(augmeneted_input[p_offest+i]);
    }
    std::cout << std::endl;

}

int main() {

    std::ifstream input_fd{ "input\\day16_input.txt" };

    std::string tmp;
    input_fd >> tmp;
    //tmp = "03036732577212944063491565474664";
    std::vector <int16_t> input;

    auto offest = std::stoi(tmp.substr(0, 7));

    for (auto ch : tmp) {
        input.push_back(std::atoi(&ch));
    }

    {
        timer t1("task 1");
        task_1(input);
    }

    {
        timer t1("task 2");
        task_2(input, offest);
    }

    return 0;
}
