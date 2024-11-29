/*
 * File: GraphicsShaderHandler.cpp
 * Author: Alex Emeny
 * Date: November 14th, 2024
 * Description: This file implements the ShaderHandler struct methods 
 *              declared in GraphicsShaderHandler.h.
 *              It defines the logic for compiling vertex and 
 *              fragment shaders and rendering models.
 */

#include "GraphicsShaderHandler.h"

#include <glm/ext.hpp>
#include <iostream>

namespace GraphicsRenderer
{
    /* Compiles fragment and vertex shaders from passed addresses and links attributes */
    ShaderHandler::ShaderHandler(std::string _vFileAddress, std::string _fFileAddress) 
        : m_programID(glCreateProgram())
    {
        // Compile both vertex and fragment shader
        m_vertShaderID = compileShader(_vFileAddress, GL_VERTEX_SHADER);
        m_fragShaderID = compileShader(_fFileAddress, GL_FRAGMENT_SHADER);

        // Link attribute locations
        linkAttributes();
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
        // Open file address and return the contents as a single string
        std::string fileData = readFile(_fileAddress);
        // Convert to C-style string
        const GLchar* shaderSrc = fileData.c_str();

        // Create the new shader, attach source (shader data string), compile
        GLuint shaderID = glCreateShader(_shaderType);
        glShaderSource(shaderID, 1, &shaderSrc, NULL);
        glCompileShader(shaderID);

        // Check for errors within shader code
        GLint success = 0;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

        if (!success) // Print found error with exact location within shader for easier debugging
        {   
            // Get length of error log info
            GLint maxLength = 0;
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

            // Print shader error log info
            std::vector<GLchar> errorLog(maxLength);
            glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);
            std::cout << &errorLog.at(0) << std::endl;

            throw std::exception();
        }

        // If successful, attach shader
        glAttachShader(m_programID, shaderID);

        return shaderID;
    }

    /* Makes use of fstream to open and read the passed shader file.
       Returns converted data into a string to be given to OpenGL */
    std::string ShaderHandler::readFile(std::string _fileAddress)
    {
        std::string line;
        std::string fileData = "";
        std::ifstream file(_fileAddress);

        // Try opening file address
        if (file.is_open())
        {
            // Run through each line and add it to the string
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
        glUseProgram(m_programID);
        glProgramUniformMatrix4fv(m_programID, glGetUniformLocation(m_programID, _type), 1, GL_FALSE, glm::value_ptr(_matrix));
        glUseProgram(0);
    }

    /* Links attributes to the shader program and sets their location */
    void ShaderHandler::linkAttributes()
    {
        glBindAttribLocation(m_programID, 0, "a_Position");
        glBindAttribLocation(m_programID, 1, "a_TexCoord");
        glBindAttribLocation(m_programID, 2, "a_Normal");

        // Link to shader and check for errors
        GLint success = 0;
        glLinkProgram(m_programID);
        glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
        if (!success)
        {
            std::cout << "Error linking attributes to shader \n";
            throw std::exception();
        }
    }

    /* Takes in a model and texture and instructs OpenGL to draw to the screen */
    void ShaderHandler::renderModel(std::shared_ptr<ModelHandler> _model, std::shared_ptr<TextureHandler> _texture)
    {
        glUseProgram(m_programID);

        // Bind model ID to VAO
        glBindVertexArray(_model->getModelId());
        // Bind texture ID
        glBindTexture(GL_TEXTURE_2D, _texture->getID());

        // Enable Back Face Culling
        glEnable(GL_CULL_FACE);
        // Enable Depth Testing
        glEnable(GL_DEPTH_TEST);
        // Enable Alpha Blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Draw model to screen using triangles (3 vertices)
        glDrawArrays(GL_TRIANGLES, 0, _model->getVertices());

        // Reset the state
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        glDisable(GL_BLEND);

        glBindVertexArray(0);
        glUseProgram(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}