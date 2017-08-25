
#ifndef MEADOWSGAMEOSG_GAMEOBJECT_H
#define MEADOWSGAMEOSG_GAMEOBJECT_H

#include "ComponentSet.h"

namespace Meadows {

    class GameObject {

        friend class World;

        bool enabled;

        std::size_t id;

        ComponentSet componentSet;

    public:
        GameObject();

        GameObject(const GameObject &other);

        virtual ~GameObject();

        /**
         * @brief Called when the game starts
         */
        virtual void init() {};

        /**
         * @brief Called at each tick
         *
         * Use this method to implement logic that does not involve other GameObject instances.
         *
         * @param delta The delta time in seconds
         */
        virtual void tick(float delta);

        /**
         * @brief Enable this object
         *
         * When enabled, GameObject#tick() is called on this object
         */
        virtual void enable();

        /**
         * @brief Disable this object
         *
         * When disabled, GameObject#tick() is not called on this object and it will not be parsed by systems
         */
        virtual void disable();

        /**
         * @brief Add a component to this GameObject.
         *
         * Only a single component of each type can be stored in a GameObject instance. The component can be retrieved
         * by calling GameObject.getComponent().
         *
         * @tparam T A class extending Component
         * @tparam VarArgs The argument types to pass to the component's constructor
         * @param varArgs The arguments to the component's constructor
         */
        template <class T, class... VarArgs>
        void addComponent(VarArgs... varArgs) {
            componentSet.addComponent<T>(varArgs...);
        }

        /**
         * Get a component from this GameObject.
         *
         * Get a component previously added by calling GameObject.addComponent(). When no such component exists,
         * returns nullptr.
         *
         * @tparam T
         * @return The component of type T or nullptr
         */
        template <class T>
        T* getComponent() {
            return componentSet.getComponent<T>();
        }

        /**
         * Test if this GameObject has an instance of the component type.
         *
         * @tparam T The component type to check for.
         * @return True if the component is present.
         */
        template <class T>
        bool hasComponent() {
            return componentSet.hasComponent<T>();
        }

        bool isEnabled() { return enabled; }

        /**
         * @brief Get this object's id
         *
         * The id is unique to the World this GameObject belongs to
         *
         * @return The id
         */
        std::size_t getId() const;

        bool operator==(const GameObject& rhs);

    private:

        /**
         * @brief Set the id of this object
         *
         * The id should be set when registering the object with the World. Each object's ID should be unique in that
         * World.
         *
         * @param id The id
         */
        void setId(std::size_t id);

    };
}


#endif //MEADOWSGAMEOSG_GAMEOBJECT_H
