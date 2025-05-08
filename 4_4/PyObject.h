#ifndef PYOBJECT_H
#define PYOBJECT_H

#include <iostream>
#include <typeinfo>
#include <utility>     // std::move, std::forward
#include <stdexcept>   // std::runtime_error, std::logic_error
#include <type_traits> // std::is_fundamental, std::remove_cv, std::remove_reference, std::is_same, std::is_pointer, std::enable_if, std::false_type, std::true_type

namespace PyObjectDetail
{
    template <typename T>
    struct is_one_of_basics_impl : std::false_type
    {
    };
    template <>
    struct is_one_of_basics_impl<int> : std::true_type
    {
    };
    template <>
    struct is_one_of_basics_impl<char> : std::true_type
    {
    };
    template <>
    struct is_one_of_basics_impl<double> : std::true_type
    {
    };
    template <>
    struct is_one_of_basics_impl<long long> : std::true_type
    {
    };

    template <typename T>
    struct is_basic_type_for_pyobject
    {
        static const bool value = is_one_of_basics_impl<typename std::remove_cv<typename std::remove_reference<T>::type>::type>::value;
    };
}

class PyObject
{
private:
    struct IHolder
    {
        virtual ~IHolder() = default;
        virtual const std::type_info &type() const = 0;
        virtual void *get_raw_ptr() = 0;
        virtual const void *get_raw_ptr() const = 0;
        virtual IHolder *clone() const = 0;
        virtual bool is_ref_type() const = 0;
    };

    template <typename T>
    struct ValueHolder : IHolder
    {
        T data;
        template <typename U>
        explicit ValueHolder(U &&value) : data(std::forward<U>(value)) {}
        ~ValueHolder() override = default;
        const std::type_info &type() const override { return typeid(T); }
        void *get_raw_ptr() override { return &data; }
        const void *get_raw_ptr() const override { return &data; }
        IHolder *clone() const override { return new ValueHolder<T>(data); }
        bool is_ref_type() const override { return false; }
    };

    template <typename T>
    struct RefHolder : IHolder
    {
        T *ptr;
        explicit RefHolder(T &ref) : ptr(&ref) {}
        ~RefHolder() override = default;
        const std::type_info &type() const override { return typeid(T); }
        void *get_raw_ptr() override { return ptr; }
        const void *get_raw_ptr() const override { return ptr; }
        IHolder *clone() const override { return new RefHolder<T>(*ptr); }
        bool is_ref_type() const override { return true; }
    };

    IHolder *content_ = nullptr;

    void cleanup()
    {
        delete content_;
        content_ = nullptr;
    }

public:
    PyObject() = default;

    PyObject(const PyObject &other) : content_(nullptr)
    {
        if (other.content_)
        {
            content_ = other.content_->clone();
        }
    }

    PyObject(PyObject &&other) noexcept : content_(other.content_)
    {
        other.content_ = nullptr;
    }

    ~PyObject()
    {
        cleanup();
    }

    template <typename T,
              typename = typename std::enable_if<PyObjectDetail::is_basic_type_for_pyobject<T>::value>::type>
    PyObject &operator=(T value)
    {
        std::cout << "PyObject got a value" << std::endl;
        cleanup();
        content_ = new ValueHolder<typename std::remove_cv<typename std::remove_reference<T>::type>::type>(value);
        return *this;
    }

    template <typename T,
              typename CleanT = typename std::remove_cv<typename std::remove_reference<T>::type>::type,
              typename = typename std::enable_if<
                  !PyObjectDetail::is_basic_type_for_pyobject<CleanT>::value &&
                  !std::is_same<CleanT, PyObject>::value &&
                  !std::is_pointer<CleanT>::value>::type>
    PyObject &operator=(T &value)
    {
        std::cout << "PyObject got a value" << std::endl;
        cleanup();
        content_ = new RefHolder<CleanT>(value);
        std::cout << "Borrowing" << std::endl;
        return *this;
    }

    template <typename T,
              typename CleanT = typename std::remove_cv<typename std::remove_reference<T>::type>::type,
              typename = typename std::enable_if<
                  !PyObjectDetail::is_basic_type_for_pyobject<CleanT>::value &&
                  !std::is_same<CleanT, PyObject>::value &&
                  !std::is_pointer<CleanT>::value>::type>
    PyObject &operator=(T &&value)
    {
        std::cout << "PyObject got a value" << std::endl;
        cleanup();
        content_ = new ValueHolder<CleanT>(std::move(value));
        std::cout << "Owning" << std::endl;
        return *this;
    }

    PyObject &operator=(PyObject &other)
    { // non-const lvalue other
        if (this == &other)
            return *this;
        std::cout << "PyObject got a value" << std::endl;
        cleanup();

        if (!other.content_)
        {
            content_ = nullptr;
            return *this;
        }

        if (other.content_->is_ref_type())
        {
            content_ = other.content_->clone();
            std::cout << "Borrowing" << std::endl;
        }
        else
        {
            content_ = other.content_;
            other.content_ = nullptr;
            std::cout << "Owning" << std::endl;
        }
        return *this;
    }

    PyObject &operator=(const PyObject &other)
    { // const lvalue other
        if (this == &other)
            return *this;
        // Check if the non-const version could have been called (i.e. other is actually non-const)
        // This is tricky; overload resolution handles it. If 'other' is truly const, this is called.
        // If 'other' is non-const, the non-const 'operator=(PyObject&)' is preferred.
        // So, this operator handles cases where 'other' is genuinely const.
        std::cout << "PyObject got a value" << std::endl;
        cleanup();

        if (!other.content_)
        {
            content_ = nullptr;
            return *this;
        }
        content_ = other.content_->clone();
        if (content_->is_ref_type())
        {
            std::cout << "Borrowing" << std::endl;
        }
        else
        {
            std::cout << "Owning" << std::endl;
        }
        return *this;
    }

    PyObject &operator=(PyObject &&other) noexcept
    {
        if (this == &other)
            return *this;
        std::cout << "PyObject got a value" << std::endl;
        cleanup();

        content_ = other.content_;
        other.content_ = nullptr;

        if (content_)
        {
            if (content_->is_ref_type())
            {
                std::cout << "Borrowing" << std::endl;
            }
            else
            {
                std::cout << "Owning" << std::endl;
            }
        }
        return *this;
    }

    PyObject &operator=(PyObject *ptr_to_pyobject)
    {
        std::cout << "PyObject got a value" << std::endl;
        cleanup();
        if (ptr_to_pyobject)
        {
            content_ = new RefHolder<PyObject>(*ptr_to_pyobject);
            std::cout << "Borrowing" << std::endl;
        }
        else
        {
            content_ = nullptr;
        }
        return *this;
    }

    template <typename T>
    operator T() const
    {
        if (!content_)
            throw std::runtime_error("PyObject is empty for conversion to T by value");

        if (content_->type() == typeid(PyObject))
        {
            const PyObject &referenced_py_obj = *static_cast<const PyObject *>(content_->get_raw_ptr());
            return referenced_py_obj.operator T();
        }

        typedef typename std::remove_cv<typename std::remove_reference<T>::type>::type TargetType;

        if (PyObjectDetail::is_basic_type_for_pyobject<TargetType>::value)
        {
            if (content_->type() == typeid(int))
                return static_cast<TargetType>(*static_cast<int *>(content_->get_raw_ptr()));
            if (content_->type() == typeid(char))
                return static_cast<TargetType>(*static_cast<char *>(content_->get_raw_ptr()));
            if (content_->type() == typeid(double))
                return static_cast<TargetType>(*static_cast<double *>(content_->get_raw_ptr()));
            if (content_->type() == typeid(long long))
                return static_cast<TargetType>(*static_cast<long long *>(content_->get_raw_ptr()));
        }
        else
        {
            if (content_->type() == typeid(TargetType))
            {
                return *static_cast<const TargetType *>(content_->get_raw_ptr());
            }
        }
        throw std::runtime_error("PyObject type mismatch or unsupported conversion for T by value");
    }

    template <typename T>
    operator T &()
    {
        if (!content_)
            throw std::runtime_error("PyObject is empty for conversion to T&");

        if (content_->type() == typeid(PyObject))
        {
            PyObject &referenced_py_obj = *static_cast<PyObject *>(content_->get_raw_ptr());
            return referenced_py_obj.operator T &();
        }

        typedef typename std::remove_cv<typename std::remove_reference<T>::type>::type TargetType;
        if (content_->type() == typeid(TargetType))
        {
            return *static_cast<TargetType *>(content_->get_raw_ptr());
        }
        throw std::runtime_error("PyObject type mismatch for conversion to T&");
    }

    template <typename T>
    operator const T &() const
    {
        if (!content_)
            throw std::runtime_error("PyObject is empty for conversion to const T&");

        if (content_->type() == typeid(PyObject))
        {
            const PyObject &referenced_py_obj = *static_cast<const PyObject *>(content_->get_raw_ptr());
            return referenced_py_obj.operator const T &();
        }

        typedef typename std::remove_cv<typename std::remove_reference<T>::type>::type TargetType;
        if (content_->type() == typeid(TargetType))
        {
            return *static_cast<const TargetType *>(content_->get_raw_ptr());
        }
        throw std::runtime_error("PyObject type mismatch for conversion to const T&");
    }
};

#endif // PYOBJECT_H
