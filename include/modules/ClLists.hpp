#ifndef CLPARSER_CLLISTS_HPP
#define CLPARSER_CLLISTS_HPP

/* ############ Cl StringList ############# */

#include <string>
#include <vector>

using namespace std;

using ClStringList = vector<string>;

/* ############# INITIALIZE LISTS ############# */

template <class T>
class ClObjList;

template <class T>
class ClPtrList;


/* ############# CL PTR LIST ############# */

#include <memory>


template <class T>
class ClPtrList : public std::vector<shared_ptr<T>> {
public:
    using std::vector<shared_ptr<T>>::vector;
    [[nodiscard]] ClObjList<T> toObjList() const {
        ClObjList<T> objList;
        for (shared_ptr<T> obj : *this)
            objList.emplace_back(*obj);
        return objList;
    };
};


/* ############# CL OBJ LIST ############# */

template <class T>
class ClObjList : public std::vector<T> {
public:
    using std::vector<T>::vector;
    [[nodiscard]] ClPtrList<T> toPtrList() const {
        ClPtrList<T> objList;
        for (T obj : *this)
            objList.emplace_back(make_shared<T>(obj));
        return objList;
    };
};



#endif //CLPARSER_CLLISTS_HPP
