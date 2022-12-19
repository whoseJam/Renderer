#define STB_IMAGE_IMPLEMENTATION
#include "Image.h"

using namespace std;

Image::Image(const string& path) {
	dataPtr = stbi_load(path.c_str(), &width, &height, &channels, 0);
}

unsigned char* Image::data() const {
	return dataPtr;
}

Image::~Image() {
	stbi_image_free(dataPtr);
}

int Image::getHeight() const {
	return height;
}

int Image::getWidth() const {
	return width;
}

int Image::getChannels() const {
	return channels;
}