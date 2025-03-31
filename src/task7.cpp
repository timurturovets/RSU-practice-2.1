#include "../include/task7.h"
#include <cstring>

namespace lab {
    binomial_priority_queue::~binomial_priority_queue() noexcept {
        bpq_node *curr = head;
        del_node(curr);
    }

    binomial_priority_queue::binomial_priority_queue() : head(nullptr) {}
    binomial_priority_queue::binomial_priority_queue(binomial_priority_queue const &bpq)
        : head(nullptr) {
        bpq_node *curr = bpq.head,
            *prev = nullptr,
            *new_head = nullptr;

        while (curr != nullptr) {
            auto *new_node = new bpq_node(curr->priority, curr->value, curr->rank);

            if(curr->child != nullptr) {
                new_node->child = bpq_node::deep_copy_tree(curr->child);
                new_node->child->parent = new_node;
            }

            if (new_head == nullptr) new_head = new_node;
            else if (prev != nullptr) prev->peer = new_node;

            prev = new_node;
            curr = curr->peer;
        }


    }

    binomial_priority_queue &binomial_priority_queue::operator =(lab::binomial_priority_queue const &bpqn) {
        if (this == &bpqn) return *this;

        bpq_node *curr = head;
        while (curr != nullptr) {
            bpq_node *next = curr->peer;
            delete curr;
            curr = next;
        }

        head = bpqn.head != nullptr ? bpq_node::deep_copy_tree(bpqn.head) : nullptr;

        return *this;
    }

    binomial_priority_queue::bpq_node::~bpq_node() noexcept {
        delete [] value;

        bpq_node *curr = child;
        del_node(curr);
    }

    binomial_priority_queue::bpq_node::bpq_node(int p, char const *v, int r)
            : priority(p), rank(r), parent(nullptr), peer(nullptr), child(nullptr) {
        value = new char[std::strlen(v) + 1];
        strcpy(value, v);
    }

    binomial_priority_queue::bpq_node::bpq_node(bpq_node const &bpqn)
            : priority(bpqn.priority), rank(bpqn.rank), parent(bpqn.parent), peer(bpqn.peer), child(bpqn.child) {
        value = new char[std::strlen(bpqn.value) + 1];
        strcpy(bpqn.value, value);
    }

    binomial_priority_queue::bpq_node
        &binomial_priority_queue::bpq_node::operator =(bpq_node const &bpqn) {
        if (&bpqn == this) return *this;

        delete [] value;

        value = new char[std::strlen(bpqn.value) + 1];
        strcpy(value, bpqn.value);

        priority = bpqn.priority;
        rank = bpqn.rank;

        parent = bpqn.parent;
        peer = bpqn.peer;
        child = bpqn.child;

        return *this;
    }

    binomial_priority_queue::bpq_node *binomial_priority_queue::merge_trees(
            binomial_priority_queue::bpq_node *bpqn1,
            binomial_priority_queue::bpq_node *bpqn2
            ) {
        if (bpqn2->rank > bpqn1->rank) {
            binomial_priority_queue::bpq_node *temp = bpqn1;
            bpqn1 = bpqn2;
            bpqn2 = temp;
        }

        bpqn2->parent = bpqn1;
        bpqn2->peer = bpqn1->child;
        bpqn1->child = bpqn2;
        bpqn1->rank++;

        return bpqn1;
    }

    binomial_priority_queue::bpq_node *binomial_priority_queue::merge_heaps(
            binomial_priority_queue::bpq_node *bpqn1,
            binomial_priority_queue::bpq_node *bpqn2
            ) {
        bpq_node *new_head = nullptr;
        bpq_node **pos = &new_head;

        while (bpqn1 != nullptr || bpqn2 != nullptr) {
            bpq_node *curr;

            if (bpqn2 == nullptr || (bpqn1 != nullptr && bpqn1->rank <= bpqn2->rank)) {
                curr = bpqn1;
                bpqn1 = bpqn1->peer;
            } else {
                curr = bpqn2;
                bpqn2 = bpqn2->peer;
            }

            if (*pos != nullptr && (*pos)->rank == curr->rank) {
                bpq_node *merged = merge_trees(*pos, curr);
                *pos = merged;
                curr = merged->peer;
            }

            *pos = curr;
            pos = &((*pos)->peer);
        }

        return new_head;
    }

    binomial_priority_queue::bpq_node *binomial_priority_queue::get_max_priority_node() const {
        if (head == nullptr) return nullptr;

        bpq_node *max = head;
        bpq_node *curr = max->peer;

        while (curr != nullptr) {
            if (curr->priority > max->priority) max = curr;
            curr = curr->peer;
        }

        return max;
    }

    void binomial_priority_queue::insert(char const *v, int p)  {
        auto *temp = new binomial_priority_queue();
        temp->head = new bpq_node(p, v, 0);
        merge(*temp);
    }

    char *binomial_priority_queue::get_max_priority_value() const {
        auto *max_node = get_max_priority_node();
        return max_node == nullptr ? nullptr : max_node->value;
    }

    void binomial_priority_queue::del_max_priority_value() {
        auto *max_node = get_max_priority_node();
        if (max_node == nullptr) return;

        if (max_node == head) head = head->peer;
        else {
            bpq_node *prev = head;
            while (prev->peer != max_node) {
                prev = prev->peer;
            }

            prev->peer = max_node->peer;
        }

        binomial_priority_queue child_bpq;
        child_bpq.head = reverse(max_node->child);

        max_node->child = nullptr;
        max_node->peer = nullptr;
        delete max_node;

        merge(child_bpq);
    }

    priority_queue &binomial_priority_queue::merge(priority_queue &pq) {

    }

    binomial_priority_queue::bpq_node *binomial_priority_queue::reverse(binomial_priority_queue::bpq_node *bpqn) {
        bpq_node *prev = nullptr;

        while (bpqn != nullptr) {
            bpq_node *next = bpqn->peer;
            bpqn->peer = prev;
            prev = bpqn;
            bpqn = next;
        }

        return prev;
    }

    void binomial_priority_queue::del_node(binomial_priority_queue::bpq_node *bpqn) {
        while (nullptr != bpqn) {
            bpq_node *next = bpqn->peer;
            delete bpqn;
            bpqn = next;
        }
    }

    binomial_priority_queue::bpq_node *binomial_priority_queue::bpq_node::deep_copy_tree(bpq_node *bpqn) {
        if (bpqn == nullptr) return bpqn;

        auto new_root = new bpq_node(bpqn->priority, bpqn->value, bpqn->rank);

        if (bpqn->child != nullptr) {
            new_root->child = deep_copy_tree(bpqn->child);
            new_root->child->parent = new_root;
        }

        bpq_node *curr_peer = bpqn->peer, *prev = new_root;

        while (curr_peer != nullptr) {
            auto new_peer = new bpq_node(bpqn->priority, bpqn->value, bpqn->rank);

            if (curr_peer->child != nullptr) {
                new_peer->child = deep_copy_tree(curr_peer->child);
                new_peer->child->parent = new_peer;
            }

            prev->peer = new_peer;
            prev = new_peer;
            curr_peer = curr_peer->peer;
        }

        return new_root;
    }
}