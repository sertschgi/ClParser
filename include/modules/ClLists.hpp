#ifndef CLPARSER_CLLISTS_HPP
#define CLPARSER_CLLISTS_HPP

/* ############ Cl StringList ############# */

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

using ClStringList = vector<string>;

/* ############# INITIALIZE LISTS ############# */

template <class T>
class ClObjList;

template <class T>
class ClPtrList;


/* ############# CL PTR LIST ############# */

#include <memory>
#include <iostream>


template <class T>
class ClPtrList : public vector<shared_ptr<T>> {
public:
    using vector<shared_ptr<T>>::vector;

    /*
    [[nodiscard]] ClPtrList<T> toPtrList(initializer_list<T&>& init) const {
        for_each(init.begin(), init.end(), [](T& obj) {make_shared<T>(obj);});
        return init;
    } */

    template <typename... Args>
    ClPtrList(T& firstObj, Args&... restObjs) {
        this->emplace_back(&firstObj);
    }

    [[nodiscard]] ClObjList<T> toObjList() const {
        ClObjList<T> objList;
        for (shared_ptr<T> obj : *this)
            objList.emplace_back(*obj);
        return objList;
    };
};


/* ############# CL OBJ LIST ############# */

template <class T>
class ClObjList : public vector<T> {
public:
    using vector<T>::vector;
    /*
    [[nodiscard]] ClPtrList<T> toPtrList() const {
        ClPtrList<T> objList;
        for (int i; i < this->size(); ++i)
            objList.emplace_back(make_shared<T>(this->at(i)));
        return objList;
    }; */
    /*
    [[nodiscard]] ClPtrList<T> toPtrList(initializer_list<T&>& init) const {
        for_each(init.begin(), init.end(), [](T& obj) {make_shared<T>(obj);});
        return init;
    }
    */
    [[nodiscard]] ClPtrList<T> toPtrList() {
        ClPtrList<T> ptrList;
        transform(this->begin(), this->end(), back_inserter(ptrList),
                  [](const T& obj) {return make_shared<T>(obj);});
        return ptrList;
    }
};



#endif //CLPARSER_CLLISTS_HPP
