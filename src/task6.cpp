#include "../include/task6.h"

namespace lab {
    binary_priority_queue::binary_priority_queue(size_t size) {
        _data = new binary_priority_queue_node[size];
        _size = 0;
    }

    size_t get_left_child_index(size_t pos) { return pos * 2 + 1; }
    size_t get_right_child_index(size_t pos) { return pos * 2 + 2; }
    size_t get_parent_index(size_t pos) { return (pos - 1) / 2; }

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
        size_t left_child_index, right_child_index;
        while ((left_child_index = get_left_child_index(pos)) < _size
                 ||(right_child_index = get_right_child_index(pos)) < _size) {
            size_t m;

            if (right_child_index >= _size
                || _data[left_child_index].priority > _data[right_child_index].priority) m = left_child_index;
            else m = right_child_index;

            if (_data[pos].priority > _data[m].priority) return;

            swap(_data[pos], _data[m]);
            pos = m;
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

    void binary_priority_queue::del_max_priority_value(char *&out_value, int &out_priority) {

        memcpy(out_value, _data[0].value, strlen(_data[0].value));
        out_priority = _data[0].priority;

        delete [] _data[0].value;

        _data[0] = _data[_size-- - 1];
        sift_down(0);
    }

    priority_queue *binary_priority_queue::merge(priority_queue *pq_stub) {
        binary_priority_queue pq = *dynamic_cast<binary_priority_queue *>(pq_stub);

        if (&pq == this) return this;

        int curr_p;
        char *curr_v;
        while (pq._size > 0) {
            pq.del_max_priority_value(curr_v, curr_p);
            this->insert(curr_v, curr_p);
        }

        return this;
    }

    binary_priority_queue &binary_priority_queue::meld();

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