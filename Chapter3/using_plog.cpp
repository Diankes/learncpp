#include <plog/Log.h>
#include <plog/Initializers/ConsoleInitializer.h>
#include <plog/Formatters/TxtFormatter.h>

int main()
{
    plog::init<plog::TxtFormatter>(plog::debug, plog::streamStdOut);

    std::cout << "Standard std::cout message.\n";

    PLOG_DEBUG << "Debug message";
    PLOG_INFO << "Info message";
    PLOG_ERROR << "Error message";

    return 0;
}
