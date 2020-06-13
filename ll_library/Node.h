#pragma once
#ifndef LL_LIBRARY_NODE_H
#define LL_LIBRARY_NODE_H


#include <string>
#include <type_traits>
#include <stdexcept>
#include <cstring> // memset
#include <map>


//#include <variant>
// using Data = std::variant<int, double, std::string>;  // =(

// Enable code-generation only for some types only.
#define TYPE_LIMITER_INT_DOUBLE_STRING  \
    template<typename T, \
       typename std::enable_if< \
                 std::is_same<T, int> {} || std::is_same<T, double>{}  || std::is_same<T, std::string>{}, int \
                >::type = 0>

enum Types  // We don't need "enum class" here because of unneded convertions.
{
    Empty=0,
    Integer,
    Double,
    String,
    Unknown=0xffff
};

namespace
{
    const std::map<Types, const std::string> typesDesc =
    {
        {Types::Integer, std::string("int")},
        {Types::Double, std::string("double")},
        {Types::String, std::string("string")},
        {Types::Empty, std::string("unknown/empty")},
        {Types::Unknown, std::string("unknown")},
    };
}
namespace Utils
{
// some helper functions, written after Node class was completed

    inline const std::string& GetTypesDesc(Types type)
    {
        return typesDesc.at(type);
    }

    inline Types TypeFromInt(int value)
    {
        switch (value)
        {
            case 0: return Types::Integer;
            case 1: return Types::Double;
            case 2: return Types::String;
        default:
            return Types::Unknown;
            break;
        }
    }

    TYPE_LIMITER_INT_DOUBLE_STRING
    Types  GetTypeOfParam(T )
    {
        if constexpr(std::is_same<T, int>::value) // int
            return Types::Integer;
        else if constexpr (std::is_same<T, double>::value) // double
            return Types::Double;
        else if constexpr (std::is_same<T, std::string>::value) // string
            return Types::String;
    }

}

class Data
{
public:

TYPE_LIMITER_INT_DOUBLE_STRING
    Data(T value)
    {
        if constexpr(std::is_same<T, int>::value)
        {
            Integer = new (content) int(value);
            currentType = Types::Integer;
        }
        else if constexpr (std::is_same<T, double>::value)
        {
            Double = new (content) double(value);
            currentType = Types::Double;
        }
        else if constexpr (std::is_same<T, std::string>::value)
        {
            String =  new (content) std::string(value);
            currentType = Types::String;
        }
    }
    ~Data()
    {
        if (currentType == Types::String)
            String->~basic_string();
        content[0] = 0;  // Hack: We should use "content" in destructor explicitly, or it will be optimised by gcc and freed before our code (double-free)
    }
TYPE_LIMITER_INT_DOUBLE_STRING
    void SetValue(T value)
    {
        if constexpr(std::is_same<T, int>::value)
        {
            if (currentType != Types::Integer)
            {
                if (currentType == Types::String)
                    String->~basic_string();
                memset(content, 0, sizeOfdata);
                Integer = new (content) int(value);
                currentType = Types::Integer;
            }
            else
            {
                *Integer = value;
            }
        }
        else if constexpr (std::is_same<T, double>::value)
        {
            if (currentType != Types::Double)
            {
                if (currentType == Types::String)
                    String->~basic_string();
                memset(content, 0, sizeOfdata);
                Double = new (content) double(value);
                currentType = Types::Double;
            }
            else
            {
                *Double = value;
            }
        }
        else if constexpr (std::is_same<T, std::string>::value)
        {
            if (currentType != Types::String)
            {
                memset(content, 0, sizeOfdata);
                String = new (content) std::string(value);
                currentType = Types::String;
            }
            else
            {
                *String = value;
            }
        }
    }


    Types GetStoredType()
    {
        return currentType;
    }
    int TryGetInt()
    {
        if (currentType == Types::Integer)
            return *Integer;
        throw std::runtime_error("No such content: int");
    }
    double TryGetDouble()
    {
        if (currentType == Types::Double)
            return *Double;
        throw std::runtime_error("No such content: double");
    }
    std::string TryGetString()
    {
        if (currentType == Types::String)
            return *String;
        throw std::runtime_error("No such content: string");
    }
    std::string ToString()
    {
        std::string result;
        if (currentType == Types::Integer)
            result = std::to_string( *Integer);
        if (currentType == Types::Double)
            result = std::to_string(*Double);
        if (currentType == Types::String)
            result = *String;
        return result;
    }
    const void* GetRawData()
    {
        return reinterpret_cast<const void*>(content);
    }


private:
    Types currentType;
    // Let's check which type is bigger on current platform (of course it definitely isn't "int")
    constexpr static auto sizeOfdata  =  sizeof(std::string) > sizeof(double) ?  sizeof(std::string) : sizeof(double);
    char content[sizeOfdata]{};

    // Pointers are not necessary and could be ommited (to decrease memory consumption). currentType is enough to use stored values.
    int * Integer = nullptr;
    double * Double = nullptr;
    std::string * String = nullptr;

};

struct Node
{

TYPE_LIMITER_INT_DOUBLE_STRING
    Node(T value, Node* prv, Node* nxt)
        :data(value), prev(prv), next(nxt){};


    ~Node() = default;

public:   //  anyway we need use all of this fields, so let's do it directly without trivial setters/getters
    Data data;
    Node* prev;
    Node* next;

};

#endif // LL_LIBRARY_NODE_H
