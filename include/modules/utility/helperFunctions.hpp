#ifndef CLPARSER_HELPERFUNCTIONS_HPP
#define CLPARSER_HELPERFUNCTIONS_HPP

/* ############# HELP FUNCTIONS ############# */

#include <functional>
#include <numeric>
#include <string>
#include <vector>
#include <memory>

#include "../ClLists.hpp"
#include "../ClCommand.hpp"

using namespace std;

// joins vector to a string
static string join(const ClStringList& vec)
{
    string result;
    for (const string& piece : vec)
    {
        if (!result.empty()) result += ", ";
        result += piece;
    }
    return result;
}

// checks if it is a shared pointer or not
template<typename T> struct is_shared_ptr : std::false_type {};
template<typename T> struct is_shared_ptr<shared_ptr<T>> : std::true_type {};

// checks if there is an object with the same T::name in the vector
template <class T>
static bool sameNameOfObjInVec(const T object, const list<T> &objects) {
    for (const T& obj : objects)
        if constexpr (is_pointer_v<T>)
        {
            if (obj->name() == object->name()) return true;
        }
        else
        {
            if (obj.name() == object.name()) return true;
        }
    return false;
}

template <class T>
static bool addObjToVec(T object, list<T> & objects)
{
    if (sameNameOfObjInVec<T>(object, objects)) return false;
    objects.emplace_back(object);
    return true;
}


template <class T>
static size_t addVecToVec(const list<T> &objVec0, list<T> & objVec1)
{
    size_t value = 0;
    for (T arg : objVec0)
    {
        if (addObjToVec<T>(arg, objVec1)) ++value;
    }
    return value;
}

template <typename I>
static size_t addObjectsToVecAsPtr(
        list<typename I::value_type *> &vecTo, I start, I end
) {
    size_t skipped = 0;
    for (auto it = start; it != end; ++it)
        if (!addObjToVec<typename I::value_type *>(&(*it), vecTo)) ++skipped;
    return skipped;
}

template <class T>
static ClStringList unwrapName(list<T> args)
{
    ClStringList set;
    for (T arg : args)
    {
        set.push_back(arg->name());
    }
    return set;
}

template <class T>
static bool longest(const T& largestObj, const T& firstObj)
{
    return largestObj.name().size() < firstObj.name().size();
}

template <class T>
static bool longestFlags(const T& largestObj, const T& firstObj)
{
    return join(largestObj.flags()).size() < join(firstObj.flags()).size();
}


#endif //CLPARSER_HELPERFUNCTIONS_HPP
