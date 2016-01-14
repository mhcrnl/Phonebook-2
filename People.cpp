#include "People.h"


int People::peopleCount = 0;

People::People(const string& name) : mID(++peopleCount), mName(name), mPhones() {

}

People::~People() {
    --peopleCount;
}

const string& People::getName() const {
    return mName;
}

int People::getID() const {
    return mID;
}

const set<int>& People::getPhones() const {
    return mPhones;
}

void People::addPhone(int id) {
    mPhones.insert(id);
}

bool People::deletePhone(int id)
{
    if (!hasPhone(id)) {
        return false;
    }
    mPhones.erase(id);
    return true;
}

bool People::hasPhone(int id) const {
    return mPhones.find(id) != mPhones.end();
}
