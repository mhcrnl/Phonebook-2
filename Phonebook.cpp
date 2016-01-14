#include "Phonebook.h"

Phonebook::Phonebook() {}

Phonebook::~Phonebook() {
    for (map<int, People*>::iterator it = mID2People.begin(); it != mID2People.end(); ++it) {
        delete it->second;
    }

    for (map<int, Phone*>::iterator it = mID2Phone.begin(); it != mID2Phone.end(); ++it) {
        delete it->second;
    }
}

void Phonebook::addContact(const string& name, const string& phoneType, const string& phoneNum) {

    //Always create new People, because people can have same name.
    People* person = new People(name);
    int personID = person->getID();

    Phone* phone = NULL;
    int phoneID = -1;

    // check if the phone exists
    if (mNum2Phone.find(phoneNum) != mNum2Phone.end()) {
        vector<Phone*> phoneVec = mNum2Phone[phoneNum];
        for (size_t i = 0; i < phoneVec.size(); ++i) {
            Phone* curPhone = phoneVec[i];
            if (curPhone->getType() == phoneType) {
                phone = curPhone;
                phoneID = curPhone->getID();
            }
        }
    }

    if (!phone) {
        phone = new Phone(phoneNum, phoneType);
        phoneID = phone->getID();
        mID2Phone[phoneID] = phone;
        if (mNum2Phone.find(phoneNum) != mNum2Phone.end()) {
            mNum2Phone[phoneNum].push_back(phone);
        } else {
            vector<Phone*> vec;
            vec.push_back(phone);
            mNum2Phone[phoneNum] = vec;
        }
    }

    person->addPhone(phoneID);
    phone->addPeople(personID);

    mID2People[personID] = person;
    if (mName2People.find(name) != mName2People.end()) {
        mName2People[name].push_back(person);
    } else {
        vector<People*> vec;
        vec.push_back(person);
        mName2People[name] = vec;
    }

}


vector<string> Phonebook::getNameByNum(const string& num) {
    vector<string> vec;
    if (mNum2Phone.find(num) == mNum2Phone.end()) {
        return vec;
    }
    vector<Phone*> phones = mNum2Phone[num];
    for (size_t i = 0; i < phones.size(); ++i) {
        const set<int>& personID = phones[i]->getPeoples();
        for (auto it = personID.begin(); it != personID.end(); ++it) {
            People* person = mID2People[*it];
            vec.push_back(person->getName());
        }
    }
    return vec;
}

vector<string> Phonebook::getPhoneByName(const string& name) {
    vector<string> vec;
    if (mName2People.find(name) == mName2People.end()) {
        return vec;
    }

    vector<People*> persons = mName2People[name];
    for (size_t i = 0; i < persons.size(); ++i) {
        const set<int>& phoneID = persons[i]->getPhones();
        for (auto it = phoneID.begin(); it != phoneID.end(); ++it) {
            Phone* phone = mID2Phone[*it];
            vec.push_back(phone->getNum());
        }
    }
    return vec;
}

