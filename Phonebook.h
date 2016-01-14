#ifndef _PHONEBOOK_H_
#define _PHONEBOOK_H_
#include "Phone.h"
#include "People.h"
#include <map>

using namespace std;

class Phonebook {
  private:
    map<int, People*> mID2People;
    map<string, vector<People*> > mName2People;
    map<int, Phone*> mID2Phone;
    map<string, vector<Phone*> > mNum2Phone;

  public:
    Phonebook();
    ~Phonebook();
    void addContact(const string& name, const string& phoneType, const string& phoneNum);
    bool deleteContact(const string& name, const string& num);
    vector<string> getNameByNum(const string& num);
    vector<string> getPhoneByName(const string& name);
};

#endif
