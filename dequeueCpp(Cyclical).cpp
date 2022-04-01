#include <iostream>
namespace dequeueV2 {
    template<typename T, class _Alloc = std::allocator<T>>
    class dequeue {
    public:
        typedef dequeue<T, _Alloc> _dque;
        typedef T _val_type;
        typedef _Alloc _allocator_type;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T* iterator;
        typedef const T* const_iterator;
        typedef std::size_t size_type;

        explicit dequeue()
            : _elements(0), _capacity(20), _dequeue(_Alloc().allocate(20)), _first(0)
        {

        }

        template<class InputIterator>
        dequeue(InputIterator first, InputIterator last) {
            _elements = 0;
            _capacity = 20;
            _dequeue = _Alloc().allocate(_capacity);
            _first = 0;
            for (auto i = first; i != last; ++i) {
                if (_elements == _capacity) {
                    extend();
                }
                _Alloc().construct(&_dequeue[_elements++], *i);
            }
        }

        explicit dequeue(const _dque& copy)
            :_elements(copy._elements),
            _capacity(copy._capacity + 20),
            _dequeue(_Alloc().allocate(copy._capacity + 20)),
            _first(copy._first)
        {
            for (int i = 0; i < copy._elements; ++i) {
                _Alloc().construct(&_dequeue[i], *(copy._dequeue + i));
            }
        }
        _dque& operator=(const _dque& rhs) {
            if (this == &rhs) {
                throw std::invalid_argument("Self-assignment error");
            }
            else {
                for (size_type i = 0; i < _capacity; ++i) {
                    _Alloc().destroy(_dequeue + i);
                }
                _Alloc().deallocate(_dequeue, _capacity);
                _dequeue = _Alloc().allocate(rhs._capacity);
                for (size_type i = 0; i < rhs._elements; ++i) {
                    _Alloc().construct(&_dequeue[i], rhs._dequeue[i]);
                }
                _elements = rhs._elements;
                _capacity = rhs._capacity;
                _first = rhs._first;
            }
            return *this;
        }
        size_type size() const {
            return _elements;
        }
        void push_back(_val_type val) {
            if (_elements == _capacity) {
                extend();
            }
            size_type insertTo = (_first + _elements) % _capacity;
            _Alloc().construct(&_dequeue[insertTo], val);
            _elements++;
        }
        void push_front(_val_type val) {
            if (_elements == _capacity) {
                extend();
            }
            if (_first == 0) {
                _first = _capacity - 1;
            }
            else {
                _first--;
            }
            _Alloc().construct(&_dequeue[_first], val);
            _elements++;

        }
        bool empty() const {
            return _elements == 0;
        }
        ~dequeue() {
            for (size_type i = 0; i < _elements; ++i) {
                _Alloc().destroy(_dequeue + i);
            }
            _Alloc().deallocate(_dequeue, _capacity);
        }
        void pop_front() {
            if (!empty()) {
                _first = (_first + 1) % _capacity;
                _elements--;
            }
            else throw std::runtime_error("Trying to pop empty dequeue");
        }
        _val_type& front() {
            return _dequeue[_first];
        }
        _val_type& back() {
            return  _dequeue[((_elements - 1) % _capacity)];
        }
        void pop_back() {
            if (!empty()) {
                _elements--;
            }
            else throw std::runtime_error("Trying to pop empty dequeue");
        }

    private:
        size_type _elements, _capacity, _first;
        T* _dequeue;
        void extend() {
            pointer buff = _Alloc().allocate(_capacity + 20);
            for (size_type i = 0, j = _first; i < _elements; ++i, ++j) {
                size_type copyFrom = j % _capacity;
                _Alloc().construct(&buff[i], *(_dequeue + copyFrom));
            }
            std::swap(_dequeue, buff);
            for (size_type i = 0; i < _elements; ++i) {
                _Alloc().destroy((buff + i));
            }
            _Alloc().deallocate(buff, _capacity);
            _capacity += 20;
        }
    };
}

int main()
{
    try {
        // code
    }
    catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
    return 0;

}