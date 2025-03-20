#include "../include/task6.h"

namespace lab {
    binary_priority_queue::binary_priority_queue(size_t size) {
        _data = new binary_priority_queue_node[size];
        _size = 0;
    }

    binary_priority_queue::binary_priority_queue(binary_priority_queue const &bpq) {
        _data = new binary_priority_queue_node[bpq._size];

        for (size_t i = 0; i < bpq._size; i++) {
        _data[i].value = new char[std::strlen(bpq._data[i].value) + 1];
        strcpy(_data[i].value, bpq._data[i].value);

        _data[i].priority = bpq._data[i].priority;
        }

        _size = bpq._size;
    }

    binary_priority_queue &binary_priority_queue::operator =(binary_priority_queue const &bpq) {
        if (&bpq == this) return *this;

        for (size_t i = 0; i < _size; i++) {
            delete [] _data[i].value;
        }

        delete [] _data;

        _data = new binary_priority_queue_node[bpq._size];
        for (size_t i = 0; i < bpq._size; i++) {
            _data[i].value = new char[strlen(bpq._data[i].value) + 1];
            strcpy(_data[i].value, bpq._data[i].value);

            _data[i].priority = bpq._data[i].priority;
        }

        _size = bpq._size;

        return *this;
    }

    binary_priority_queue::~binary_priority_queue() {
        for(size_t i = 0; i < _size; i++) {
        delete [] _data[i].value;
        }

        delete _data;
    }

    void binary_priority_queue::sift_up(size_t pos) {
        while (pos > 0 && _data[pos].priority < _data[(pos - 1) / 2].priority) {
            binary_priority_queue::swap(_data[pos], _data[(pos - 1) / 2]);
            pos = (pos - 1) / 2;
        }
    }

    void binary_priority_queue::sift_down(size_t pos) {
        while (2 * pos + 1 < _size) {
            size_t l = (2 * pos) + 1, r = (2 * pos) + 2;
            size_t i = l;

            if (r < _size && _data[r].priority < _data[l].priority) i = r;

            if (_data[pos].priority <= _data[i].priority) break;

            swap(_data[pos], _data[i]);

            pos = i;
        }
    }

    void binary_priority_queue::insert(char const *v, int p) {
        resize(_size + 1);
        _size++;

        strcpy(_data[_size - 1].value, v);
        _data[_size - 1].priority = p;

        sift_up(_size - 1);
    }

    char *binary_priority_queue::get_max_priority_value() const {
        return _data[0].value;
    }

    int binary_priority_queue::get_max_priority() const {
        return _data[0].priority;
    }

    void binary_priority_queue::del_max_priority_value() {
        delete [] _data[0].value;

        _data[0] = _data[_size-- - 1];
        sift_down(0);
    }

    binary_priority_queue &binary_priority_queue::merge(binary_priority_queue &pq) {
        if (&pq == this) return *this;

        while (pq._size > 0) {
            this->insert(pq.get_max_priority_value(), pq.get_max_priority());
            pq.del_max_priority_value();
        }

        return *this;
    }

    void binary_priority_queue::resize(size_t new_size) {
        auto *resized = new binary_priority_queue_node[new_size];
        for (size_t i = 0; i < _size && i < new_size; i++) {
            resized[i].value = new char[std::strlen(_data[i].value) + 1];

            strcpy(resized[i].value, _data[i].value);
            resized[i].priority = _data[i].priority;

            delete [] _data[i].value;
        }
        delete [] _data;

        _data = resized;
        _size = new_size;

    }

    void binary_priority_queue::swap(binary_priority_queue_node &n1, binary_priority_queue_node &n2) {
        binary_priority_queue_node &temp = n1;
        n1 = n2;
        n2 = temp;
    }
}