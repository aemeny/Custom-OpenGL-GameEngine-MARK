/*
 * File: GraphicsShaderHandler.cpp
 * Author: Alex Emeny
 * Date: November 14th, 2024
 * Description: This file implements the ShaderHandler structmethods 
 *              declared in GraphicsShaderHandler.h.
 *              It defines the logic for compiling vertex and 
 *              fragment shaders and rendering models.
 */

#include "GraphicsShaderHandler.h"

namespace GraphicsRenderer
{
    /* Compiles fragment and vertex shaders from passed addresses and links attributes */
    ShaderHandler::ShaderHandler(std::string _vFileAddress, std::string _fFileAddress) 
        : m_programID(glCreateProgram())
    {
        m_vertShaderID = compileShader(_vFileAddress, GL_VERTEX_SHADER);
        m_fragShaderID = compileShader(_fFileAddress, GL_FRAGMENT_SHADER);
    }

    /* Handles detaching and destroying no longer needed shader objects */
    ShaderHandler::~ShaderHandler()
    {
        glDetachShader(m_vertShaderID, m_programID);
        glDetachShader(m_fragShaderID, m_programID);
        glDeleteShader(m_vertShaderID);
        glDeleteShader(m_fragShaderID);
        glDeleteProgram(m_programID);
    }

    /* Creates and compiles the passed shader from given address.
           Returns generated ID from the created shader */
    GLuint ShaderHandler::compileShader(std::string _fileAddress, GLuint _shaderType)
    {
        return GLuint();
    }

    /* Makes use of fstream to open and read the passed shader file.
       Returns converted data into a string to be given to OpenGL */
    std::string ShaderHandler::readFile(std::string _fileAddress)
    {
        std::string line;
        std::string fileData = "";
        std::ifstream file(_fileAddress);

        if (file.is_open())
        {
            while (std::getline(file, line))
            {
                fileData += line + '\n';
            }

            file.close();
        }
        else
        {
            throw std::runtime_error("Unable To Open Shader File: " + _fileAddress);
        }

        return fileData;
    }

    /* Binds matrix with passed shader type */
    void ShaderHandler::bindShader(glm::mat4 _matrix, const GLchar* _type)
    {
    }

    /* Links attributes to the shader program and sets their location */
    void ShaderHandler::linkAttributes()
    {
    }

    /* Takes in a model and texture and instructs OpenGL to draw to the screen */
    void ShaderHandler::renderModel(std::shared_ptr<ModelHandler> _model, std::shared_ptr<TextureHandler> _texture)
    {
    }
}