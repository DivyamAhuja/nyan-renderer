#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Texture::Texture(const char *filename, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
    type = texType;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *bytes = stbi_load(
        filename,
        &imgWidth,
        &imgHeight,
        &numColorChannels,
        STBI_rgb_alpha);
    if (bytes == nullptr)
    {
        std::cerr << "Failed to load texture\n";
        throw("Failed to load Texture");
    }

    glGenTextures(1, &ID);

    glActiveTexture(slot);
    glBindTexture(texType, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(texType, 0, GL_RGBA8, imgWidth, imgHeight, 0, format, pixelType, bytes);
    glGenerateMipmap(texType);

    stbi_image_free(bytes);

    glBindTexture(texType, 0);
}

void Texture::texUnit(Shader &shader, const char *uniform, GLuint unit)
{
    GLuint texUni = glGetUniformLocation(shader.ID, uniform);
    shader.Activate();
    glUniform1i(texUni, unit);
}

void Texture::bind()
{
    glBindTexture(type, ID);
}

void Texture::unbind()
{
    glBindTexture(type, 0);
}

void Texture::Delete()
{
    if (ID) {
        glDeleteTextures(1, &ID);
        ID = 0;
    }
}

Texture::~Texture() {
    this->Delete();
}