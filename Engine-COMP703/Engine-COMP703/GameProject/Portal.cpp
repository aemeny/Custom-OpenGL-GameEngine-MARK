/*
 *  File: Portal.cpp
 *  Author: Alex Emeny
 *  Date: January 5th, 2025 (Last Edited)
 *  Description: This file implements the methods declared in Portal.h
 *               It implements the functions for portal behavior within the world
 */

#include "Portal.h"

 /// THIS IS AN EXAMPLE OF A USER CREATED SCRIPT WHEN USING THE ENGINE AND NOT PART OF THE ENIGNE ITSELF ///

void Portal::onTick()
{
    m_portalEntity.lock()->setActiveStatus(false);



}
