#include "ModelHandler.h"
#include "Core.h"

namespace GameEngine
{
    void ModelHandler::onDisplay()
    {
        std::weak_ptr<Camera> camera = m_entity.lock()->m_corePtr.lock()->getActiveRenderingCamera();

        // UPDATE TRANSFORM MATRIX-------------------------------------------------------

        m_shader->bindShader(camera.lock()->getProjectionMatrix(), "u_Projection");
        //m_shader->bindShader(TRANSFORM GET MODEL MATRIX, "u_Model");
        m_shader->bindShader(camera.lock()->getViewingMatrix(), "u_Viewing");

        m_shader->renderModel(m_model, m_texture);
    }

    /* Loads the Graphics Renderer's ModelHandler resource */
    void ModelHandler::setModel(std::string _modelFileAddress)
    {
        m_model = m_entity.lock()->m_corePtr.lock()->m_resources->
            load<ModelResource>("../Samples/Models/" + _modelFileAddress)->getModel();
    }

    /* Loads the Graphics Renderer's TextureHandler resource */
    void ModelHandler::setTexture(std::string _textureFileAddress)
    {
        m_texture = m_entity.lock()->m_corePtr.lock()->m_resources->
            load<TextureResource>("../Samples/Textures/" + _textureFileAddress)->getTexture();
    }

    /* Loads the Graphics Renderer's ShaderHandler resource */
    void ModelHandler::setShaders(std::string _vertShaderFileAddress, std::string _fragShaderFileAddress)
    {
        m_shader = m_entity.lock()->m_corePtr.lock()->m_resources->
            load<ShaderResource>("../Shaders/" + _vertShaderFileAddress, "../Shaders/" + _fragShaderFileAddress)->getShader();
    }
}