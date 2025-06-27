#include "../include/task8.h"
#include <stdexcept>
#include <cstring>

namespace lab {
    fib_priority_queue::fpq_node::fpq_node(char const *value, int priority, size_t rank) {
        this->value = value;
        this->priority = priority;
        this->rank = rank;

        right = nullptr;
        left = nullptr;
        parent = nullptr;
        child = nullptr;
        visited = false;
    }

    fib_priority_queue::fpq_node::~fpq_node() noexcept {
        delete value;
    }

    fib_priority_queue::fib_priority_queue() {
        max_root = nullptr;
        size = 0;

    }

    fib_priority_queue::~fib_priority_queue() noexcept {
        if (max_root == nullptr) return;

        max_root->left->right = nullptr;
        max_root->left = nullptr;

        auto stack = new fpq_node*[size];
        size_t stack_top = 0;

        stack[stack_top++] = max_root;
        max_root->visited = true;

        while (stack_top > 0) {
            fpq_node *curr = stack[--stack_top];

            if (curr->right != nullptr && !curr->right->visited) {
                stack[stack_top++] = curr->right;
                curr->right->visited = true;
            }

            if (curr->child != nullptr && !curr->child->visited) {
                fpq_node *child = curr->child;
                child->left->right = nullptr;
                child->left = nullptr;

                stack[stack_top++] = child;
                child->visited = true;
            }

            curr->left = nullptr;
            curr->right = nullptr;
            curr->parent = nullptr;
            curr->child = nullptr;
            delete curr;
        }

        delete [] stack;
    }

    void fib_priority_queue::insert(const char *v, int p) {
        auto new_node = new fpq_node(v, p, 0);

        if (max_root == nullptr) {
            new_node->left = new_node;
            new_node->right = new_node;
            max_root = new_node;

            size++;
            return;
        }

        new_node->left = max_root;
        new_node->right = max_root->right;

        max_root->right->left = new_node;
        max_root->right = new_node;

        if (p > max_root->priority) {
            max_root = new_node;
        }

        size++;
    }

    char const *fib_priority_queue::get_max_priority_value() const {
        if (max_root == nullptr) return nullptr;

        return max_root->value;
    }

    void fib_priority_queue::del_max_priority_value(char *& out_value, int &out_priority) {
        if (max_root == nullptr) throw std::runtime_error("heap is empty.");

        strcpy(out_value, max_root->value);
        out_priority = max_root->priority;

        fpq_node *child = max_root->child;
        while (child != nullptr) {
            fpq_node *next_child = child->right;

            child->left = max_root;
            child->right = max_root->right;
            max_root->right->left = child;
            max_root->right = child;

            child->parent = nullptr;
            child = next_child;
        }

        fpq_node *to_delete = max_root;
        if (max_root->right == max_root) {
            max_root = nullptr;
        } else {
            max_root->left->right = max_root->right;
            max_root->right->left = max_root->left;
            max_root = max_root->right;
        }

        if (max_root != nullptr) {
            fpq_node *curr = max_root->right;
            fpq_node *new_max = max_root;
            while (curr != max_root) {
                if (curr->priority > new_max->priority) new_max = curr;

                curr = curr->right;
            }
            max_root = new_max;
        }

        delete to_delete;

        size--;
    }

    priority_queue *fib_priority_queue::merge(priority_queue *pq) {
        auto other = dynamic_cast<fib_priority_queue *>(pq);
        if (other == nullptr) return this;

        if (max_root == nullptr) {
            max_root = other->max_root;
            size = other->size;
        }

        else if (other->max_root != nullptr) {
            fpq_node *this_right = max_root->right;
            fpq_node *other_left = other->max_root->left;

            max_root->right = other->max_root;
            other->max_root->left = max_root;
            this_right->left = other_left;
            other_left->right = this_right;

            if (other->max_root->priority > max_root->priority) max_root = other->max_root;

            size += other->size;
        }

        other->max_root = nullptr;
        other->size = 0;

        return this;
    }
}