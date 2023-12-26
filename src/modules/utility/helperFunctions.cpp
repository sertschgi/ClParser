/* ############# HELP FUNCTIONS ############# */

#include <functional>
#include <numeric>
#include <string>
#include <vector>
#include <memory>

#include "modules/ClLists.hpp"

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
static bool sameNameOfObjInVec(const T object, const vector<T> &objects) {
    for (const T& obj : objects)
        if constexpr (is_shared_ptr<T>::value)
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
static bool addObjToVec(T object, vector<T> &objects)
{
    if (sameNameOfObjInVec<T>(object, objects)) return false;
    objects.emplace_back(object);
    return true;
}

template <class T>
static size_t addVecToVec(const vector<T> &objVec0, vector<T> &objVec1)
{
    size_t value = 0;
    for (const T& arg : objVec0)
    {
        if (addObjToVec<T>(arg, objVec1)) ++value;
    }
    return value;
}

template <typename I>
static size_t addObjectsToVecAsPtr(
        vector<shared_ptr<typename I::value_type>> &vecTo, I start, I end
) {
    size_t skipped = 0;
    for (auto it = start; it != end; ++it)
        if (!addObjToVec<shared_ptr<typename I::value_type>>(make_shared<typename I::value_type>(*it), vecTo)) ++skipped;
    return skipped;
}

template <class T>
static ClStringList unwrapName(vector<T> args)
{
    ClStringList vec;
    for (T arg : args)
    {
        vec.insert(arg->name());
    }
    return vec;
}