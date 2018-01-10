#ifndef MEADOWSECS_COMPONENT_H
#define MEADOWSECS_COMPONENT_H

namespace Meadows {

    /**
     * A data container base class for use in an Entity.
     */
    class Component {

    public:
        virtual ~Component() = default;
    };
}

#endif //MEADOWSECS_COMPONENT_H
