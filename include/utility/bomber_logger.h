#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include <iostream>

using namespace std;

#define LOG_FILE_NAME   "bombergwen.log"
#define LOGGER_NAME     "bomber_logger"

typedef shared_ptr<spdlog::logger> TBomberLogger;

class BomberLogger {
public:
    BomberLogger() 
    {
        create_logger();
    }
    ~BomberLogger() {}
    
    static TBomberLogger get_instance() {
        return INSTANCE;
    }

    static bool create_logger();
private:
    static TBomberLogger INSTANCE;
};

