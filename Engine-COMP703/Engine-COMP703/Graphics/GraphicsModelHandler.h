/*
 *  File: GraphicsModelHandler.h
 *  Author: Alex Emeny
 *  Date: November 14th, 2024
 *  Description: This file contains the ModelHandler struct, 
 *               which is responsible for handling the uploading of .obj 
 *               model data to the GPU and storing information about the model's data.
 */

#pragma once
#include <bugl.h> // .obj model reader and loader

namespace GraphicsRenderer
{
    struct ModelHandler
    {
        /* Uploads .obj model to gpu from given file address */
        ModelHandler(std::string _fileAddress);

        /* Calls upon the .obj model to be reuploaded to the gpu */
        void updateModel();

        /* Returns the number of vertices in the model */
        size_t getVertices() const { return m_vertices; }
        /* Sets the value for how many vertices the model has */
        void setVertices(size_t _vertices) { m_vertices = _vertices; }

        /* Returns the models id value */
        GLuint getModelId() const { return m_modelId; }

        /* Returns a pointer to a vector of the models faces */
        std::vector<bu::Face>* getFaces() { return &m_faces; }
        /* Sets passed faces to the models held faces */
        void setFaces(std::vector<bu::Face> _newFaces) { m_faces = _newFaces; }

    private:
        size_t m_vertices;
        GLuint m_modelId;
        std::vector<bu::Face> m_faces;
    };
}