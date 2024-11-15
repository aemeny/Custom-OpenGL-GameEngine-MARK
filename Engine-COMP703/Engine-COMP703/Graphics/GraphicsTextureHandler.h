#pragma once

namespace GraphicsRenderer
{
    struct TextureHandler
    {
        TextureHandler();

        GLuint getID() { return textureID; }

    private:
        GLuint textureID;
    };
}