#pragma once

#include <fstream>
#include <mutex>

extern std::ofstream dbgFile;
extern std::mutex dbgFileMutex;