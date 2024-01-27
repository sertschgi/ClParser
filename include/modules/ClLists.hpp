#ifndef CLPARSER_CLLISTS_HPP
#define CLPARSER_CLLISTS_HPP

/* ############ Cl StringList ############# */

#include <string>
#include <list>
#include <vector>
#include <set>
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
#include <cstdarg>

template <class T>
class ClPtrList : public list<T*> {
public:
    using list<T*>::list;

    /*
    [[nodiscard]] ClPtrList<T> toPtrList(initializer_list<T&>& init) const {
        for_each(init.begin(), init.end(), [](T& obj) {make_shared<T>(obj);});
        return init;
    } */
    /*
    template <typename... Args>
    void addNonPtrArgs(T& firstObj, Args&... restObjs)
    {
        this->insert(make_shared<T>(firstObj));
        if constexpr(sizeof...(restObjs) > 0) addNonPtrArgs(restObjs...);
    } */

    /* ClPtrList(initializer_list<reference_wrapper<T>> init)
    {
        for (const reference_wrapper<T> & objRef : init) make_shared<T>(objRef.get());

        transform(
                init.begin(),
                init.end(),
                inserter(*this, this->end()), [](const reference_wrapper<T>& refW) {
                    return make_shared<T>(ref(refW));
                });
    } */

    //ClPtrList(T& arg) : ClPtrList(make_shared<T>(arg)) {}

    //void insert(shared_ptr<T> obj) {this->insert(obj);}
    //void insert(T& obj) {this->insert(make_shared<T>(obj));}
 /*
    void addPtrArg(T& ref) {
        cout << ref.name() << endl;

        shared_ptr<T> shared = make_shared<T>(move(ref));
        cout << shared->name() << endl;
        if (shared.get() == &ref) cout << "same!";
    }

    template <typename... Args>
    void addNonPtrArgs(Args&... objs)
    {
        (addPtrArg(objs), ...);
        (this->insert(make_shared<T>(objs)), ...);
    }

    template <typename... Args>
    ClPtrList(Args&... args) {
        addNonPtrArgs(args...);

    } */

    ClPtrList(initializer_list<reference_wrapper<T>> init)
    {
        for (const reference_wrapper<T> &objRef: init)
            this->emplace_back(&objRef.get());

    }

    [[nodiscard]] ClObjList<T> toObjList() const {
        ClObjList<T> objList;
        for (T * obj : *this)
            objList.emplace_back(*obj);
        return objList;
    };
};


/* ############# CL OBJ LIST ############# */

template <class T>
class ClObjList : public list<T> {
public:
    using list<T>::list;
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
    [[nodiscard]] ClPtrList<T> toPtrList() const {
        ClPtrList<T> ptrList;
        transform(this->begin(), this->end(), inserter(ptrList, ptrList.end()),
                  [](const T& obj) {return &obj;});
        return ptrList;
    }
};



#endif //CLPARSER_CLLISTS_HPP
