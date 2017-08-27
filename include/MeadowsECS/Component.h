#ifndef MEADOWSECS_COMPONENT_H
#define MEADOWSECS_COMPONENT_H

#include "ComponentRegistry.h"

namespace Meadows {

    /**
     * A data container base class for use in a GameObject.
     *
     * Each component type (subclass) has an index that represents its index in ComponentSet.
     */
    class Component {

        friend class ComponentRegistry;

        std::size_t index;

    public:
        virtual ~Component() {}

        std::size_t getIndex() {
            return index;
        }

    private:
        /**
         * Called by RegisteredComponent.
         *
         * This index should be unique for each component type.
         *
         * @param index This component type's index in ComponentSet
         */
        void setIndex(std::size_t index) {
            this->index = index;
        }
    };
}

#endif //MEADOWSECS_COMPONENT_H
