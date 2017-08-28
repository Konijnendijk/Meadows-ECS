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

    public:
        virtual ~Component() {}
    };
}

#endif //MEADOWSECS_COMPONENT_H
