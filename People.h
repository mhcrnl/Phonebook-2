#ifndef _PEOPLE_H_
#define _PEOPLE_H_
#include <string>
#include <vector>
#include <set>

using namespace std;

class People {
  private:
    static int peopleCount;
    int mID;
    string mName;
    set<int> mPhones;

  public:

    People(const string& name);
    ~People();
    const string& getName() const;
    int getID() const;
    const set<int>& getPhones() const;
    void addPhone(int id);
    bool deletePhone(int id);
    bool hasPhone(int id) const;
};


#endif
