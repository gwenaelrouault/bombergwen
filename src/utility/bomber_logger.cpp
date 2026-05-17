#include "bomber_logger.h"

TBomberLogger BomberLogger::INSTANCE = nullptr;

bool BomberLogger::create_logger()
{
    try
    {
        INSTANCE = spdlog::basic_logger_mt(LOGGER_NAME, LOG_FILE_NAME);
        INSTANCE->set_level(spdlog::level::info);
        INSTANCE->flush_on(spdlog::level::info);
        return true;
    }
    catch (const spdlog::spdlog_ex &ex)
    {
        std::cout << "Log init failed: " << ex.what() << std::endl;
    }
    return false;
}