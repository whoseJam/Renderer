#pragma once

#include <vector>
#include <string>

class Resource {
public:
    Resource(const std::string& name);
    void setName(const std::string& name);
    std::string getName() const;

    virtual void showUI() = 0;
private:
    std::string name;
};

