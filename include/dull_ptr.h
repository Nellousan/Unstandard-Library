/*
** Unstandard-Library
** File description:
** dullptr
*/

#ifndef DULLPTR_H_
#define DULLPTR_H_

///@file dull_ptr.h

#include <memory>

namespace ustd {

/**
 * @brief An upgraded std::weak_ptr easier to use.
 * 
 * The main features of this class is the ability to access the stored pointer easily,
 * as well as an easier way to tell if two pointer are the same or to tell if a pointer has expired
 * by comparing it with nullptr.
 */
template <class T>
class dull_ptr : public std::weak_ptr<T> {
public:
    dull_ptr() = delete;

    dull_ptr(const dull_ptr& other)
        : std::weak_ptr<T>(other)
    {
    }

    dull_ptr(const std::shared_ptr<T>& ptr)
        : std::weak_ptr<T>(ptr)
    {
    }

    dull_ptr(void* ptr)
        : std::weak_ptr<T>(std::make_shared<T>(reinterpret_cast<T>(ptr)))
    {
    }

    ~dull_ptr() = default;

    /**
     * @brief Returns the underlying pointer.
     * 
     * @return The underlying pointer, returns nullptr if the shared_ptr expired.
     */
    T* get()
    {
        return std::weak_ptr<T>::lock().get();
    }

    /**
     * @brief Access elements of the stored object.
     *
     * Throw an error if the pointer is expired.
     */
    T* operator->()
    {
        if (std::weak_ptr<T>::expired()) {
            throw std::runtime_error("dull_ptr: operator->: expired");
        }
        return get();
    }

    /**
     * @brief Derefence the stored pointer.
     * 
     * Throw an error if the pointer is expired.
     */
    T& operator*()
    {
        if (std::weak_ptr<T>::expired()) {
            throw std::runtime_error("dull_ptr: operator*: expired");
        }
        return *get();
    }

    bool operator==(const dull_ptr& other)
    {
        return (std::weak_ptr<T>::lock().get() == other.std::weak_ptr<T>::lock().get());
    }

    bool operator==(void* ptr)
    {
        return (std::weak_ptr<T>::lock().get() == ptr);
    }

    bool operator!=(const dull_ptr& other)
    {
        return (std::weak_ptr<T>::lock().get() != other.std::weak_ptr<T>::lock().get());
    }

    bool operator!=(void* ptr)
    {
        return (std::weak_ptr<T>::lock().get() != ptr);
    }

    friend bool operator==(const dull_ptr<T>& first, const dull_ptr<T>& second)
    {
        return (first == second);
    }
};

}

#endif /* !DULLPTR_H_ */
