
#ifndef MEADOWSGAMEOSG_ENTITY_H
#define MEADOWSGAMEOSG_ENTITY_H

#include <list>

#include "ComponentSet.h"

namespace Meadows {

    class Entity {

        typedef std::list<Entity*>::const_iterator entity_location;

        friend class World;

        bool enabled;
        std::size_t id;
        ComponentSet componentSet;

        // The location of this Entity in its World
        std::list<Entity*>::const_iterator location;

    public:
        Entity();

        Entity(const Entity &other);

        virtual ~Entity();

        /**
         * @brief Called when the game starts
         */
        virtual void init() {};

        /**
         * @brief Add a component to this Entity.
         *
         * Only a single component of each type can be stored in a Entity instance. The component can be retrieved
         * by calling Entity.getComponent().
         *
         * @tparam T A class extending Component
         * @tparam VarArgs The argument types to pass to the component's constructor
         * @param varArgs The arguments to the component's constructor
         */
        template<class T, class... VarArgs>
        void addComponent(VarArgs... varArgs) {
            componentSet.addComponent<T>(varArgs...);
        }

        /**
         * Get a component from this Entity.
         *
         * Get a component previously added by calling Entity.addComponent(). When no such component exists,
         * returns nullptr.
         *
         * @tparam T
         * @return The component of type T or nullptr
         */
        template<class T>
        T *getComponent() {
            return componentSet.getComponent<T>();
        }

        /**
         * Test if this Entity has an instance of the component type.
         *
         * @tparam T The component type to check for.
         * @return True if the component is present.
         */
        template<class T>
        bool hasComponent() {
            return componentSet.hasComponent<T>();
        }

        bool isEnabled() { return enabled; }

        /**
         * @brief Get this object's id
         *
         * The id is unique to the World this Entity belongs to
         *
         * @return The id
         */
        std::size_t getId() const;

        bool operator==(const Entity &rhs);

    protected:
        /**
        * @brief Called at each tick
        *
        * Use this method to implement logic that does not involve other Entity instances.
        *
        * @param delta The delta time in seconds
        */
        virtual void tick(float delta);

        /**
         * @brief Enable this object
         *
         * When enabled, Entity#tick() is called on this object
         */
        void enable();

        /**
         * @brief Disable this object
         *
         * When disabled, Entity#tick() is not called on this object and it will not be parsed by systems
         */
        void disable();

    private:

        /**
         * @brief Set the id of this Entity
         *
         * The id should be set when registering the object with the World. Each object's ID should be unique in that
         * World.
         *
         * @param id The id
         */
        void setId(std::size_t id);

        /**
         * @brief Set the location of this Entity in the world
         *
         * Used by the World to store where in its entity list this Entity is stored.
         *
         * @param location The location of this entity in its world.
         */
        void setLocation(entity_location location);

        /**
         * @brief Get the location of this entity in the World entity list
         *
         * @return An iterator to the location
         */
        entity_location getLocation();
    };
}


#endif //MEADOWSGAMEOSG_ENTITY_H
