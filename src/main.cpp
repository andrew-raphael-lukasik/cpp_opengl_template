#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

int main ()
{
    auto file_logger = spdlog::basic_logger_mt("file_logger", "log.txt");
    spdlog::set_default_logger(file_logger);
    spdlog::info("log.txt file created");

    spdlog::info("Hello spdlog!");
}
