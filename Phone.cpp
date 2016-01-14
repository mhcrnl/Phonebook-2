#include "Phone.h"


int Phone::phoneCount = 0;

Phone::Phone(const string& num, const string& type) : mID(++phoneCount), mNum(num), mType(type), mPeoples() {}

Phone::~Phone() {
    --phoneCount;
}

const string& Phone::getType() const {
    return mType;
}

const string& Phone::getNum() const {
    return mNum;
}

int Phone::getID() const {
    return mID;
}

const set<int>& Phone::getPeoples() const {
    return mPeoples;
}

void Phone::addPeople(int id) {
    mPeoples.insert(id);
}

bool Phone::deletePeople(int id)
{
    if (!hasPeople(id)) {
        return false;
    }
    mPeoples.erase(id);
    return true;
}

bool Phone::hasPeople(int id) const {
    return mPeoples.find(id) != mPeoples.end();
}



