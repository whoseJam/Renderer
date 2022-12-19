#include "Resource.h"

using namespace std;

Resource::Resource(const string& name) {
    this->name = name;
}

void Resource::setName(const string& name) {
    this->name = name;
}

string Resource::getName() const {
    return name;
}
