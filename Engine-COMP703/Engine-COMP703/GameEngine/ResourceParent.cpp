/*
 *  File: ResourceParent.cpp
 *  Author: Alex Emeny
 *  Date: December 8th, 2024 (Last Edited)
 *  Description: This file implements the methods declared ResourceParent.h,
 *               It implements the function for loading a child Resource.
 *               This struct also handles storing and returning the file paths.
 */

#include "ResourceParent.h"

namespace GameEngine
{
    /* Calls virtual onLoad() function */
    void Resource::load()
    {
        onLoad();
    }

    std::string Resource::getfileAddress() const
    {
        return m_fileAddress;
    }

    std::string Resource::getfileAddress2() const
    {
        return m_fileAddress2;
    }
}