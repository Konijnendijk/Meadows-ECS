
#ifndef MEADOWSGAMEOSG_WORLD_H
#define MEADOWSGAMEOSG_WORLD_H


#include <vector>

#include "Entity.h"
#include "System.h"


namespace Meadows {
    class World {
        std::vector<Entity*> entities;
        std::vector<Entity*> entitiesToAdd;
        std::vector<Entity*> entitiesToRemove;

        std::vector<System*> systems;

        // Counter for assigning ids to GameObjects
        std::size_t nextGameObjectId;

    public:

        World();

        ~World();

        /**
         * @brief create an object of the given type using the constructor taking varArgs
         *
         * @return A pointer to the newly created entity, owned by this World
         */
        template<class T, class... VarArgs>
        T* createEntity(VarArgs... varArgs) {
            T* object = new T(varArgs...);
            registerEntity(object);
            return object;
        }

        /**
         * @brief create a system of the given type using the constructor taking varArgs
         *
         * The system's System.registerObject(), System.removeObject() and System.tick() methods
         * will start to be called the next time world.tick() is called.
         *
         * @return A pointer to the newly created system, owned by this World
         */
         template <class T, class... VarArgs>
        T* createSystem(VarArgs... varArgs) {
            T* system = new T(varArgs...);
            registerSystem(system);
            return system;
        };

        /**
         * @brief Remove a game object from the world.
         *
         * Removes the given GameObject from the world. Next tick the System.objectRemoved() methods wil be called and
         * all pointers to this object will be invalidated .
         *
         * @param object The object to remove
         */
        void removeEntity(Entity *object);

        /**
         * @brief Retrieve a system given its type
         *
         * This can be a time-consuming operation since it will loop through all systems until the first system of the
         * given type is found.
         *
         * @return The first registered system of the given type, or nullptr if no such system is present
         */
        template<class T>
        T* getSystem() {
            for (System* s : systems) {
                T* result = dynamic_cast<T*>(s);
                if (result != nullptr) {
                    return result;
                }
            }
        }

        /**
         * @brief Tick all game objects and systems
         *
         * @param delta The delta time
         */
        void tick(float delta);

    private:
        void registerEntity(Entity *object);

        void registerSystem(System* system);
    };
}

#endif //MEADOWSGAMEOSG_WORLD_H
