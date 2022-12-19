#include "Loader.h"
#include "Image.h"

TextureID Loader::loadTexture(const std::string& path) {
    TextureID tmp;
    glGenTextures(1, &tmp);
    glBindTexture(GL_TEXTURE_2D, tmp);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    Image image(path);
    if (image.getChannels() == 1) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, image.getWidth(), image.getHeight(), 0, GL_RED, GL_UNSIGNED_BYTE, image.data());
    }
    if (image.getChannels() == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.getWidth(), image.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.data());
    }
    if (image.getChannels() == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
    }
    glGenerateMipmap(GL_TEXTURE_2D);
    return tmp;
}