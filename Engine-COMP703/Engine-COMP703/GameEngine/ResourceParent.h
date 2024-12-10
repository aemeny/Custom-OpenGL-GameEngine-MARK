/*
 *  File: ResourceParent.h
 *  Author: Alex Emeny
 *  Date: December 8th, 2024 (Last Edited)
 *  Description: This file contains the Resource struct,
 *               It defines the function for loading a child Resource.
 *               This struct also handles storing and returning the file paths.
 */

#pragma once
#include "../Graphics/GraphicsMasterHeader.h"
#include <memory>
#include <string>

namespace GameEngine
{
    struct Resource
    {
        /* Load function called to children */
        virtual void onLoad() = 0;

        std::string getfileAddress() const;
        std::string getfileAddress2() const;
    private:
        friend struct Resources;
        /* File path for address to resource */
        std::string m_fileAddress;
        std::string m_fileAddress2; // Second available for double shader paths

        /* Calls virtual onLoad() function */
        void load();
    };
}