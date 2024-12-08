/*
 *  File: Resources.h
 *  Author: Alex Emeny
 *  Date: December 8th, 2024 (Last Edited)
 *  Description: This file contains the Resources struct,
 *               It defines the function for caching and returning a Resource.
 *               This struct handles storing all the resources loaded.
 */

#pragma once
#include "ResourceParent.h"

#include <memory>
#include <vector>
#include <string>

namespace GameEngine
{
    struct Resources
    {
        template<typename T>
        std::shared_ptr<T> load(const std::string& _fileAddress, const std::string& _fileAddress2 = "")
        {
            /* Search to check if the resource is already loaded */
            for (size_t i = 0; i < m_resources.size(); i++)
            {
                /* Return loaded resource if file address matches */
                if (m_resources.at(i)->getfileAddress() == _fileAddress)
                {
                    return std::dynamic_pointer_cast<T>(m_resources.at(i));
                }
            }

            /* If new resource is being loaded, Instantiate and add to Cache */
            std::shared_ptr<T> rtn = std::make_shared<T>();
            rtn->m_fileAddress = _fileAddress;
            rtn->m_fileAddress2 = _fileAddress2;
            rtn->load();

            m_resources.push_back(rtn);
            return rtn;
        }

    private:
        std::vector<std::shared_ptr<Resource>> m_resources;
    };
}