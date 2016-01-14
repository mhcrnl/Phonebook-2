#ifndef _PHONE_H_
#define _PHONE_H_
#include <string>
#include <vector>
#include <set>

using namespace std;

class Phone {
  private:
    static int phoneCount;
    int mID;
    string mNum;
    string mType;
    set<int> mPeoples;

  public:
    Phone(const string& num, const string& type);
    ~Phone();
    const string& getType() const;
    const string& getNum() const;
    int getID() const;
    const set<int>& getPeoples() const;
    void addPeople(int id);
    bool deletePeople(int id);
    bool hasPeople(int id) const;
};

#endif
