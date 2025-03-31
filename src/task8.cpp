#include <algorithm>
#include "../include/task8.h"

namespace lab {
    leftist_priority_queue::lpq_node::lpq_node(int p, const char *v, int r)
    : priority(p), rank(r), left(nullptr), right(nullptr) {
        value = new char[std::strlen(v) + 1];
        strcpy(value, v);
    }

    leftist_priority_queue::lpq_node::~lpq_node() noexcept {
        delete [] value;
        delete left;
        delete right;
    }


    leftist_priority_queue::lpq_node::lpq_node(lpq_node const &bpqn)
        : priority(bpqn.priority), rank(bpqn.rank), left(bpqn.left), right(bpqn.right) {
        value = new char[std::strlen(bpqn.value) + 1];
        strcpy(value, bpqn.value);
    }

    leftist_priority_queue::lpq_node &leftist_priority_queue::lpq_node::operator =(lpq_node const &bpqn) {
        if (this == &bpqn) return *this;

        delete [] value;

        value = new char[std::strlen(bpqn.value) + 1];
        strcpy(value, bpqn.value);

        priority = bpqn.priority;
        rank = bpqn.rank;

        left = bpqn.left;
        right = bpqn.right;

        return *this;
    }

    leftist_priority_queue::lpq_node *leftist_priority_queue::lpq_node::deep_copy_tree(leftist_priority_queue::lpq_node *lpqn) {
        if (lpqn == nullptr) return nullptr;

        auto *new_node = new lpq_node(lpqn->priority, lpqn->value, lpqn->rank);
        new_node->left = deep_copy_tree(lpqn->left);
        new_node->right = deep_copy_tree(lpqn ->right);
        new_node->rank = lpqn->rank;
        return new_node;
    }

    leftist_priority_queue::lpq_node *leftist_priority_queue::merge_nodes(lpq_node *lpqn1, lpq_node *lpqn2) {
        if (!lpqn1) return lpqn2;
        if (!lpqn2) return lpqn1;

        if (lpqn1->priority < lpqn2->priority) std::swap(lpqn1, lpqn2);

        lpqn1->right = merge_nodes(lpqn1->right, lpqn2);

        if (!lpqn1->left || lpqn1->left->rank < lpqn1->right->rank) std::swap(lpqn1->left, lpqn1->right);


        lpqn1->rank = (lpqn1->right ? lpqn1->right->rank : 0) + 1;

        return lpqn1;
    }

    leftist_priority_queue::leftist_priority_queue() : root(nullptr) {}

    leftist_priority_queue::~leftist_priority_queue() {
        delete root;
    }

    leftist_priority_queue::leftist_priority_queue(leftist_priority_queue const &lpq)
        : root(leftist_priority_queue::lpq_node::deep_copy_tree(lpq.root)) {

    }

    void leftist_priority_queue::insert(char const *v, int p) {
        auto *new_node = new lpq_node(p, v, 0);
        root = merge_nodes(root, new_node);
    }

    [[nodiscard]] char* leftist_priority_queue::get_max_priority_value() const {
        if (root == nullptr) return nullptr;

        char *cpy = new char[std::strlen(root->value) + 1];
        strcpy(cpy, root->value);

        return cpy;
    }

    void leftist_priority_queue::del_max_priority_value() {
        if (root == nullptr) return;

        lpq_node *old_root = root;
        root = merge_nodes(root->left, root->right);
        old_root->left = old_root->right = nullptr;

        delete old_root;
    }

    priority_queue &leftist_priority_queue::merge(priority_queue &pq) {
        auto *new_lpq = dynamic_cast<leftist_priority_queue*>(&pq);
        if (new_lpq == nullptr) return *this;

        root = merge_nodes(root, new_lpq->root);
        new_lpq->root = nullptr;

        return *this;
    }
}