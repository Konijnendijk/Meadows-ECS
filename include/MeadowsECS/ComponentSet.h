
#ifndef MEADOWSECS_COMPONENTSET_H
#define MEADOWSECS_COMPONENTSET_H

#include <vector>
#include <cstddef>

#include "BitSet.h"
#include "Component.h"

namespace Meadows {

    class ComponentSet {

        // Each component type has a unique index, the bit at this index is set when a component type is present
        BitSet componentBitSet;

        // The components in this set, can be indexed by calling componentBitSet.numSetBitsBefore()
        std::vector<Component*> components;

    public:
        ComponentSet();

        ~ComponentSet();

        template <class T, class... VarArgs>
        void addComponent(VarArgs... varArgs) {
            Component* component = new T(varArgs...);
            std::size_t index = getComponentIndex<T>();
            componentBitSet.set(index);
            std::size_t vectorIndex = componentBitSet.numSetBitsBefore(index);
            components.insert(components.begin() + vectorIndex, component);
        };

        /**
         * Get the component of given type.
         *
         * @tparam T The component type to get
         * @return  The component or an empty pointer if the component was not in this set
         */
        template <class T>
        T* getComponent() {
            std::size_t index = getComponentIndex<T>();
            if (!componentBitSet[index]) {
                return nullptr;
            }
            return static_cast<T*>(components[componentBitSet.numSetBitsBefore(index)]);
        }

        /**
         * Test if this ComponentSet has an instance of the component type.
         *
         * @tparam T The component type to check for.
         * @return True if the component is present.
         */
        template <class T>
        bool hasComponent() {
            std::size_t index = getComponentIndex<T>();
            return componentBitSet[index] != 0;
        }

    private:
        template <class T>
        std::size_t getComponentIndex() {
            return ComponentRegistry::getInstance()->getComponentIndex<T>();
        }
    };
}

#endif //MEADOWSECS_COMPONENTSET_H
