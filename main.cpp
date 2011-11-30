
// Simple buffer that just clears the contents on destruction, it's likely
// that we will want to add additional security features at some point,
// some minor things like a simple xor would do a ton against memory
// scanners and the like, but any more complicated encryption would
// just be a stop-gap.

template <T>
struct SecureBuffer
{
    size_t length;
    T* data;

    SecureBuffer() : length(0),  data(NULL) {}
    SecureBuffer(size_t len) : length(len)
    {
        data = new T[len];
    }

    ~SecureBuffer()
    {
        memset(data, 0, sizeof(T) * length);
        delete T;
        length = 0;
    }

    // Don't trust realloc!! It's likely that it may leave the old data around.
};

typedef char* uchar; // Make this utf-8 or w/e.

struct Span
{
    int offset;
    int length;

    Span* parent;
    Span* sibling; // Next sibling in the list.
    Span* children; // First child in the list.

    Span() : offset(0),
             length(0),
             parent(null),
             sibling(null),
             children(null)
    {}
};

// Document
// +--Table
//    +--Header
//    +--Row
//       +--Seperator
//       +--Site
//       +--User
//       +--Password

// Transforms can actually be really simple, if it's just a sorted list, we can
// just adjust the following transforms offsets if we are doing in-memory, but
// most likely we are transforming into a new buffer.

struct Transform
{
    int offset;
    int source_length;
    int transform_length;

    //API: Decide how we are going to manage this, do we copy,
    //uchar* transform;

    Transform* next;

    Transform() : offset(0),
                  source_length(0),
                  transform_length(0),
                  next(null)
    {}

    int lengthDelta()
    {
        return atomDelta() + (next ? next.lengthDelta() : 0);
    }

    int atomDelta()
    {
        return transform_length - source_length;
    }
};
