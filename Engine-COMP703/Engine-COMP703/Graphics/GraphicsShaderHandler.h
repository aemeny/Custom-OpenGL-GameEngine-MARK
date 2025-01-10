/*
 *  File: GraphicsShaderHandler.h
 *  Author: Alex Emeny
 *  Date: November 14th, 2024 (Last Edited)
 *  Description: This file contains the ShaderHandler struct,
 *               which is responsible for compiling, linking, and managing shaders.
 *               The ShaderHandler also provides methods for rendering models with textures.
 */

#pragma once
#include "GraphicsModelHandler.h"
#include "GraphicsTextureHandler.h"
#include "GraphicsRenderTextureHandler.h"
#include "Vao.h"

namespace GraphicsRenderer
{
    struct ShaderHandler
    {
        /* Compiles fragment and vertex shaders from passed addresses and links attributes */
        ShaderHandler(std::string _vFileAddress, std::string _fFileAddress);
        /* Handles detaching and destroying no longer needed shader objects */
        ~ShaderHandler();

        /* Takes in a model and texture and instructs OpenGL to draw to the screen */
        void renderModel(std::shared_ptr<ModelHandler> _model, std::shared_ptr<TextureHandler> _texture);
        /* Takes in a model and a render texture and instructs OpenGL to draw to the screen */
        void renderModel(std::shared_ptr<ModelHandler> _model, std::weak_ptr<RenderTextureHandler> _renderTexture);
        /* Takes in a Vao from LineRenderer and instruct OpenGL to draw to the screen */
        void renderDebugLine(std::shared_ptr<Vao> _Vao, int _numOfLines);
        /* Takes in a Vao and texture and instructs OpenGL to draw to the screen */
        void renderQuad(std::shared_ptr<Vao> _Vao, std::shared_ptr<TextureHandler> _texture);

        /* Binds matrix with passed shader type */
        void bindShader(glm::mat4 _matrix, const GLchar* _type);

    private:
        // Held IDs
        GLuint m_programID;
        GLuint m_fragShaderID;
        GLuint m_vertShaderID;

        /* Links attributes to the shader program and sets their location */
        void linkAttributes();

        /* Creates and compiles the passed shader from given address.
           Returns generated ID from the created shader */
        GLuint compileShader(std::string _fileAddress, GLuint _shaderType);

        /* Makes use of fstream to open and read the passed shader file. 
           Converts data into a string to be given to OpenGL */
        std::string readFile(std::string _fileAddress);
    };
}