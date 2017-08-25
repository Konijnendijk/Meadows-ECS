
#ifndef MEADOWSECS_COMPONENTREGISTRY_H
#define MEADOWSECS_COMPONENTREGISTRY_H

#include <cstddef>

namespace Meadows {
    /**
     * Uses a templated variable to keep track of the existing component types in the form of a RegisteredComponent.
     */
    class ComponentRegistry {

        static std::size_t numRegisteredComponents;

        template <class T>
        static std::size_t componentIndex;

        static ComponentRegistry* instance;

    public:
        template <class T, class... VarArgs>
        T* create(VarArgs... varArgs) {
            T* component = new T(varArgs...);
            std::size_t index = componentIndex<T>;
            component->setIndex(index);
            return component;
        }

        static std::size_t getNumRegisteredComponents();

        static ComponentRegistry* getInstance();

        template <class T>
        std::size_t getComponentIndex() {
            return componentIndex<T>;
        }
    };

    template <class T>
    std::size_t ComponentRegistry::componentIndex<T> = ComponentRegistry::numRegisteredComponents++;
}

#endif //MEADOWSECS_COMPONENTREGISTRY_H
