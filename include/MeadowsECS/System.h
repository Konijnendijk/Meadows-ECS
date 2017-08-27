
#ifndef MEADOWSGAMEOSG_SYSTEM_H
#define MEADOWSGAMEOSG_SYSTEM_H

#include <vector>
#include <queue>
#include <memory>
#include <algorithm>

#include "Entity.h"

namespace Meadows {

    /**
     * A System is used to handle interactions between multiple GameObject instances. An example is handling physics
     * interactions between objects.
     *
     * When objects do not depend on each other, consider using GameObject.tick().
     */
    class System {
        std::vector<Entity*> objects;
        //Objects added or removed in the current frame, will be added to or removed from objects before next frame
        std::queue<Entity*> toAdd;
        std::queue<Entity*> toRemove;

    public:

        /**
         * @brief Construct a new system
         *
         * @param name A name describing this system
         */
        System(std::string name);

        /**
         * @brief Tick this system
         */
        void tick(float delta);

        /**
         * @brief register an object for parsing by this system
         */
        void registerObject(Entity* object);

        void removeObject(Entity* object);

        /**
         * @brief Called when the game starts
         */
        virtual void init() = 0;

        /**
         * @brief Determines whether a GameObject is accepted by this system
         *
         * If this system accepts the object, it is added to this list of objects and objectAdded() is called.
         *
         * This method is not meant to store the passed pointer or alter the passed object.
         *
         * @return True if the object should be accepted, false if not
         */
        virtual bool acceptsObject(Entity *object);

        /**
         * @brief Called when an object is added to this system
         *
         * @param object The added object
         */
        virtual void objectAdded(Entity* object) = 0;

        /**
         * @brief Called when an object is removed from the system
         *
         * @param object The removed object
         */
        virtual void objectRemoved(Entity* object) = 0;

        /**
         * @brief Called each tick after all objects have been processed
         *
         * @param delta Delta time
         */
        virtual void doTick(float delta) = 0;
    };
}

#endif //MEADOWSGAMEOSG_SYSTEM_H
