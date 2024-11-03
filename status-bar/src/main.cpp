#include <filesystem>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
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
std::vector<std::string> get_cpu_load_per_core_json();

int main(int argc, char** argv)
{
    const int32_t sleep = 1; // seconds
                             
    // Print protocol version, then start endless array, then print an empty entry to start
    std::cout << "{ \"version\": 1 }\n" << "[\n" << "[]" << std::endl;

    while(true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(sleep));

        std::cout << ",[";

        //std::vector<std::string> cpu_stats_json_vec = get_cpu_load_per_core_json(); 
        //for( const std::string& cpu_stats_json : cpu_stats_json_vec )
        //{
        //    std::cout << cpu_stats_json << ",";
        //}

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

std::vector<std::string> split(const std::string& str, const char delim)
{
    std::stringstream ss(str);
    std::string next;
    std::vector<std::string> elements;
    while( std::getline(ss, next, delim) )
    {
        elements.push_back(next);
    }

    return elements;
}

std::vector<std::string> get_cpu_load_per_core_json()
{
    // LINK: https://stackoverflow.com/questions/3017162/how-to-get-total-cpu-usage-in-linux-using-c

    // 1. Read /proc/stat
    const std::filesystem::path procstat = "/proc/stat";
    std::ifstream proc_file(procstat);

    // 2. Read all rows starting with cpu[x]
    std::string line;
    std::vector<std::string> cpu_lines;
    while( std::getline(proc_file, line) )
    {
        if( line.at(0) != 'c' && line.at(1) != 'p' && line.at(2) != 'u' ) continue;
        
        cpu_lines.push_back(line);
    }

    // 3. Read each value on line
    struct CPUStat
    {
        uint64_t total = 0;
        uint64_t work = 0;
    };

    std::vector<CPUStat> cpu_stats;
    static std::vector<CPUStat> cpu_stats_prev;
    for( std::string& cpu_line : cpu_lines )
    {
        std::vector<std::string> values = split(cpu_line, ' ');
        
        CPUStat cpu_stat;
        uint8_t counter = 0;
        for( const std::string& svalue : values )
        {
            uint64_t val = 0;
            try
            {
                val = std::stoll(svalue);
            }
            catch(...)
            {
                // TODO: Could do some logging of some sort to indicate that somethings up...
                val = 0;
            }
            cpu_stat.total += val;
            if( counter < 3 )
            {
                cpu_stat.work += val;
            }
            counter += 1;
        }
        
        cpu_stats.push_back(cpu_stat);
    }

    // 5. Compare jiffies after some time (next time this function is called)
    if( cpu_stats_prev.empty() ) 
    {
        cpu_stats_prev = cpu_stats; // First time we directly set prev, next time calculate
        return std::vector<std::string>();
    }
    
    // TODO: Check if cpu_stats and cpu_stats_prev are equal size 

    std::vector<std::string> json;
    for( uint64_t index = 0; index < cpu_stats.size() && index < cpu_stats_prev.size(); index++ )
    {
        uint64_t total_over_period = cpu_stats[index].total - cpu_stats_prev[index].total;
        uint64_t work_over_period = cpu_stats[index].work - cpu_stats_prev[index].work;

        double cpu_percentage = (static_cast<double>(work_over_period) / static_cast<double>(total_over_period)) * 100;

        std::stringstream cpu_aligned;
        cpu_aligned << std::setprecision(2) << std::setfill(' ') << std::setw(4) << std::fixed << " " << cpu_percentage << "% ";

        std::stringstream ss;
        ss << "{";
        ss << "\"name\": \"CPU " << index << "\",";
        ss << "\"full_text\": \"" << cpu_aligned.str() << "\",";
        ss << "\"color\": \"" << black << "\",";
        ss << "\"background\": \"" << bright_blue << "\",";
        ss << "\"separator\": true,";
        ss << "\"separator_block_width\": 0";
        ss << "}";

        json.push_back(ss.str());
    }

    // 6. Save to static memory
    cpu_stats_prev = cpu_stats;

    return json;
}

