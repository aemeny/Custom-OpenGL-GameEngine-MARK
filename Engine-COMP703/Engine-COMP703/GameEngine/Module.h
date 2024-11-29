#pragma once
#include "Entity.h"

namespace GameEngine
{
	struct Core;

	struct Module
	{
		Module();

		void load();
		void unload();

		glm::vec3 m_relativePosition;
		

		/*
		 * \param _out a vector of shared pointers argument.
		 * Find function that returns a vector of any type thats passed into it.
		 * Checks through all entities then all their components for given template.
		*/
		template <typename T>
		void find(std::vector<std::shared_ptr<T> >& _out)
		{
			// Go through each Entity in the Module.
			for (size_t ei = 0; ei < m_entities.size(); ++ei)
			{
				std::shared_ptr<Entity> e = m_entities.at(ei);
				// Go through each Component in Entity.
				for (size_t ci = 0; ci < e->m_components.size(); ++ci)
				{
					std::shared_ptr<Component> c = e->m_components.at(ci);
					// Try to dynamic cast the Component to a T.
					std::shared_ptr<T> t = std::dynamic_pointer_cast<T>(c);
					// If succeeds then add it to the output array.
					if (t)
					{
						_out.push_back(t);
					}
				}
			}
		}

	private:
		std::vector<std::shared_ptr<Entity> > m_entities;
	};
}