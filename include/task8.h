#include "task5.h"
namespace lab {
    class fib_priority_queue : public priority_queue {
    public:
        struct fpq_node {
            char const *value;
            int priority;

            fpq_node *left;
            fpq_node *right;
            fpq_node *child;
            fpq_node *parent;

            size_t rank;

            fpq_node(char const *value, int priority, size_t rank);
            ~fpq_node() noexcept;
            bool visited; // for proper destructor functioning
        };

        fpq_node *max_root;
        size_t size;

        fib_priority_queue();
        ~fib_priority_queue() noexcept override;

        void insert(char const *v, int p) override;
        [[nodiscard]] char const *get_max_priority_value() const override;
        void del_max_priority_value(char *& out_value, int &out_priority) override;
        priority_queue *merge(priority_queue *pq) override;

    private:
        void cut(fpq_node *child, fpq_node *parent);
        void cascade_cut(fpq_node *node);
    };
}