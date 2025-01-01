#ifndef XTYPE_H

#define XTYPE_H

#include <vector>

using Id = uint64_t;
using Buffer = std::vector<std::byte>;

enum class TypeId : Id {
    Uint,
    Float,
    String,
    Vector
};

class IntegerType {
public:
    template<typename ...Args>
    IntegerType(Args&& ...);
};

class FloatType {
public:
    template<typename ...Args>
    FloatType(Args&& ...);
};

class StringType {
public:
    template<typename ...Args>
    StringType(Args&& ...);
};

class VectorType {
public:
    template<typename ...Args>
    VectorType(Args&& ...);

    template<typename Arg>
    void push_back(Arg&& _val);
};

class Any {
public:
    template<typename ...Args>
    Any(Args&& ...);

    void serialize(Buffer& _buff) const;

    Buffer::const_iterator deserialize(Buffer::const_iterator _begin, Buffer::const_iterator _end);

    TypeId getPayloadTypeId() const;

    template<typename Type>
    auto& getValue() const;

    template<TypeId kId>
    auto& getValue() const;

    bool operator == (const Any& _o) const;
};

class Serializator {
public:
    template<typename Arg>
    void push(Arg&& _val);

    Buffer serialize() const;

    static std::vector<Any> deserialize(const Buffer& _val);

    const std::vector<Any>& getStorage() const;
};

#endif // XTYPE_H