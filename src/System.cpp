
#include "System.h"

Meadows::System::System(std::string name) {

}

void Meadows::System::tick(float delta) {
    // Remove objects set to be removed
    while (!toRemove.empty()) {
        auto remove = toRemove.front();
        objects.erase(std::remove_if(objects.begin(), objects.end(),
                                     [&](GameObject* obj) {
                                         return obj == remove;
                                     }), objects.end());
        objectRemoved(remove);
        toRemove.pop();
    }

    // Add new objects
    while (!toAdd.empty()) {
        auto add = toAdd.front();
        objects.push_back(add);
        objectAdded(add);
        toAdd.pop();
    }

    doTick(delta);
}

void Meadows::System::registerObject(Meadows::GameObject *object) {
    toAdd.push(object);
}

void Meadows::System::removeObject(Meadows::GameObject *object) {
    toRemove.push(object);
}

bool Meadows::System::acceptsObject(Meadows::GameObject *object) {
    return true;
}
