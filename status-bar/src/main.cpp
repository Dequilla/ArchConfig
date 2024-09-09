#include <iostream>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <thread>
#include <ctime>

#define bright_blue "#DAE2E3"
#define sky_blue "#6995C6"
#define yellow "#DFAB48"
#define brown "#BC6927"
#define green "#546022"
#define white "#FFFFFF"
#define black "#000000"

const std::string json_entry_fmt = "\"{"
    "\"name\": \"Date and Time\","
    "\"full_text\": \" $date_formatted \","
    "\"color\": \"$black\","
    "\"background\": \"$sky_blue\","
    "\"border\": \"$sky_blue\","
    "\"separator\": false,"
    "\"separator_block_width\": 0"
    "}\"";

std::string get_date_json();
std::string get_kernel_json();
std::string get_battery_json();

int main(int argc, char** argv)
{
    const int32_t sleep = 1; // seconds
                             
    // Print protocol version, then start endless array, then print an empty entry to start
    std::cout << "{ \"version\": 1 }" << "[" << "[]" << std::endl;

    while(true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(sleep));

        std::cout << ",[";
        std::cout << get_date_json() << ",";
        std::cout << get_battery_json() << ",";
        std::cout << get_kernel_json() << ",";

        std::cout << "]" << std::endl;
    }

    return 0;
}

std::string get_date_json()
{
    std::stringstream ss;

    std::time_t time = std::time(nullptr);
    std::tm local = *std::localtime(&time);

    ss << "{";
    ss << "\"name\": \"Date and time\",";
    ss << "\"full_text\": \"" << std::put_time(&local, "%d-%m-%Y %H-%M-%S") << "\",";
    ss << "\"color\": \"" << bright_blue << "\",";
    ss << "\"background\": \"" << bright_blue << "\",";
    ss << "\"separator\": \"false\"";
    ss << "}";

    return ss.str();
}

std::string get_kernel_json()
{
    return "{}";
}

std::string get_battery_json()
{
    return "{}";
}

