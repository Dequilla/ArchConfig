#include <filesystem>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <thread>
#include <ctime>

#include <sys/utsname.h>

#define bright_blue "#dae2e3"
#define sky_blue "#6995c6"
#define yellow "#dfab48"
#define brown "#bc6927"
#define green "#546022"
#define white "#ffffff"
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
    std::cout << "{ \"version\": 1 }\n" << "[\n" << "[]" << std::endl;

    while(true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(sleep));

        std::cout << ",[";

        std::cout << get_kernel_json() << ",";
        std::cout << get_battery_json() << ",";
        std::cout << get_date_json();

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
    ss << "\"full_text\": \" " << std::put_time(&local, "%A %d-%m-%Y %H:%M:%S") << " \",";
    ss << "\"color\": \"" << black << "\",";
    ss << "\"background\": \"" << bright_blue << "\",";
    ss << "\"separator\": true,";
    ss << "\"separator_block_width\": 0";
    ss << "}";

    return ss.str();
}

std::string get_kernel_json()
{
    utsname info;
    if(uname(&info) == 0)
    {
        std::string version(info.release);
        version = version.substr(0, version.find_first_of('-'));

        std::stringstream ss;
        ss << "{";
        ss << "\"name\": \"Version\",";
        ss << "\"full_text\": \" " << version << " \",";
        ss << "\"color\": \"" << black << "\",";
        ss << "\"background\": \"" << bright_blue << "\",";
        ss << "\"separator\": true,";
        ss << "\"separator_block_width\": 0";
        ss << "}";

        return ss.str();
    }
    else
    {
        return "Kernal Unknown.";
    }
}

std::string get_battery_json()
{
    const std::filesystem::path status = "/sys/class/power_supply/BAT0/status";
    const std::filesystem::path capacity = "/sys/class/power_supply/BAT0/capacity";

    std::ifstream status_s(status);
    std::ifstream capaci_s(capacity);

    std::string status_str;
    if(status_s.is_open())
    {
        std::getline(status_s, status_str);
    }

    std::string capacity_str;
    if(capaci_s.is_open())
    {
        std::getline(capaci_s, capacity_str);
    }
    
    std::stringstream ss;
    ss << "{";
    ss << "\"name\": \"Battery status\",";
    ss << "\"full_text\": \" " << status_str << " at " << capacity_str << "%" << " \",";
    ss << "\"color\": \"" << black << "\",";
    ss << "\"background\": \"" << bright_blue << "\",";
    ss << "\"separator\": true,";
    ss << "\"separator_block_width\": 0";
    ss << "}";

    return ss.str();
}

std::vector<std::string> get_cpu_load_per_core()
{
    // 1. Read /proc/stat
    // 2. Read all rows starting with cpu[x]
    // 3. Save to static memory
    // 4. Compare after x time
    // LINK: https://stackoverflow.com/questions/3017162/how-to-get-total-cpu-usage-in-linux-using-c
}

