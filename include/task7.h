#include "task5.h"
#include <cstring>

namespace lab {

class binomial_priority_queue : public priority_queue {
private:
    struct bpq_node {
    public:
        int priority;
        char *value;
        int rank;
        bpq_node *parent;
        bpq_node *peer;
        bpq_node *child;

        bpq_node(int p, char const *v, int r);
        ~bpq_node() noexcept;
        bpq_node(bpq_node const &bpqn);
        bpq_node &operator =(bpq_node const &bpqn);
        static bpq_node *deep_copy_tree(bpq_node *bpqn);
    };

    bpq_node *head;

    static bpq_node *merge_trees(bpq_node *bpqn1, bpq_node *bpqn2);
    static bpq_node *merge_heaps(bpq_node *bpqn1, bpq_node *bpqn2);

    [[nodiscard]] bpq_node *get_max_priority_node() const;

    static bpq_node *reverse(bpq_node *bpqn);
    static void del_node(bpq_node *bpqn);
public:
    binomial_priority_queue();
    ~binomial_priority_queue() noexcept override;
    binomial_priority_queue(binomial_priority_queue const &bpqn);
    binomial_priority_queue &operator =(binomial_priority_queue const &bpqn);

    void insert(char const *v, int p) override;
    char *get_max_priority_value() const override;
    void del_max_priority_value() override;
    priority_queue &merge(priority_queue &pq) override;
    };
}