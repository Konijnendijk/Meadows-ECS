
#ifndef MEADOWSECS_COMPONENTREGISTRY_H
#define MEADOWSECS_COMPONENTREGISTRY_H

#include <cstddef>
#include <type_traits>

#include "Component.h"

namespace Meadows {
    /**
     * Uses a templated variable to keep track of the existing component types.
     */
    class ComponentRegistry {

        static std::size_t numRegisteredComponents;

        template <class T>
        static const std::size_t componentIndex;

        static ComponentRegistry* instance;

    public:
        static std::size_t getNumRegisteredComponents();

        static ComponentRegistry* getInstance();

        template <class T>
        std::size_t getComponentIndex() {
            static_assert(std::is_base_of<Component, T>::value, "T must be of type Component");
            return componentIndex<T>;
        }
    };

    template <class T>
    const std::size_t ComponentRegistry::componentIndex = ComponentRegistry::numRegisteredComponents++;
}

#endif //MEADOWSECS_COMPONENTREGISTRY_H
