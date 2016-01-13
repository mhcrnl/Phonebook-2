#ifndef _PEOPLE_H_
#define _PEOPLE_H_
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

class People {
  private:
    static long long peopleCount;
    int mID;
    string mName;
    map<string, set<string>> mPhoneNums;

  public:
    People(const string& name);
    const map<string, vector<string>>& getPhoneNums() const;
    const vector<string>& getPhoneNumsByType(const string& phoneType) const;
    void addPhoneNum(const string& type, const string& num);
    void editPhoneNum(const string& num);
    void deletePhoneNum(const string& num);
};


#endif
