
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
