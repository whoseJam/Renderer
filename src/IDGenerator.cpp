
#include <mutex>
#include "IDGenerator.h"
#include "Define.h"

namespace {
    FuncID IDGeneratorCurrentID;
    std::mutex IDGeneratorLock;
}

FuncID IDGenerator::getFuncID() {
    std::lock_guard<std::mutex> guard(IDGeneratorLock);
    IDGeneratorCurrentID++;
    return IDGeneratorCurrentID;
}