
#ifndef MEADOWSGAMEOSG_WORLD_H
#define MEADOWSGAMEOSG_WORLD_H


#include <vector>
#include <map>
#include <memory>
#include <string>

#include "GameObject.h"
#include "System.h"


namespace Meadows {

    class SystemAlreadyRegisteredException : std::runtime_error {
    public:
        SystemAlreadyRegisteredException(const std::string what);
    };

    class World {

        static World *instance;

        std::vector<GameObject*> objects;
        std::vector<GameObject*> objectsToAdd;
        std::vector<GameObject*> objectsToRemove;
        std::map<std::string, System*> systems;

        // Counter for assigning ids to GameObjects
        std::size_t nextGameObjectId;

    public:

        World();

        ~World();

        /**
         * @brief create an object of the given type using the constructor taking varArgs
         *
         * @return A pointer to the newly created component, owned by this World
         */
        template<class T, class... VarArgs>
        T* createObjectOfType(VarArgs... varArgs) {
            T* object = new T(varArgs...);
            registerObject(object);
            return object;
        }

        /**
         * @brief register an already created system to this world
         *
         * The system's System.registerObject(), System.removeObject() and System.tick() methods
         * will start to be called.
         *
         * @param name A unique name for the system
         * @param system The System to register, transfers ownership to this World
         */
        void registerSystem(std::string name, System* system);

        /**
         * @brief Remove a game object from the world.
         *
         * Removes the given GameObject from the world. Next tick the System.objectRemoved() methods wil be called and
         * all pointers to this object will be invalidated .
         *
         * @param object The object to remove
         */
        void removeObject(GameObject* object);

        /**
         * @brief Retrieve a system given its name
         *
         * Note that this method will return nullptr when T does not match the type of the System.
         */
        template<class T>
        T* getSystem(std::string name) {
            return dynamic_cast<T*>(systems[name]);
        }

        /**
         * @brief Tick all game objects and systems
         *
         * @param delta The delta time
         */
        void tick(float delta);

    private:
        void registerObject(GameObject* object);
    };
}


#endif //MEADOWSGAMEOSG_WORLD_H
