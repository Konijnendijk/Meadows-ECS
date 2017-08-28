
#ifndef MEADOWSGAMEOSG_SYSTEM_H
#define MEADOWSGAMEOSG_SYSTEM_H

#include <vector>
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
        std::vector<Entity*> entities;
        //Objects added or removed in the current frame, will be added to or removed from objects before next frame
        std::vector<Entity*> toAdd;
        std::vector<Entity*> toRemove;

    public:
        /**
         * @brief Tick this system
         */
        void tick(float delta);

        /**
         * @brief register an object for parsing by this system
         */
        void registerEntity(Entity *object);

        void removeEntity(Entity *object);

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
        virtual void entityAdded(Entity *object) = 0;

        /**
         * @brief Called when an object is removed from the system
         *
         * @param object The removed object
         */
        virtual void entityRemoved(Entity *object) = 0;

        /**
         * @brief Called each tick after all objects have been processed
         *
         * @param delta Delta time
         */
        virtual void doTick(float delta) = 0;
    };
}

#endif //MEADOWSGAMEOSG_SYSTEM_H
