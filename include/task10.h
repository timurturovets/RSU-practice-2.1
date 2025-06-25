#include <cstring>
#include "task5.h"
namespace lab {

    class skew_priority_queue : public priority_queue {
    private:
        struct spq_node {
            int priority;
            char *value;
            int rank;
            spq_node *left;
            spq_node *right;

            spq_node(int p, char const *v, int r);
            ~spq_node() noexcept;
            spq_node(spq_node const &bpqn);
            spq_node &operator =(spq_node const &bpqn);
            static spq_node *deep_copy_tree(spq_node *bpqn);
        };

        spq_node *root;

        static spq_node *merge_nodes(spq_node *lpqn1, spq_node *lpqn2);
    public:
        skew_priority_queue();
        ~skew_priority_queue();
        skew_priority_queue(skew_priority_queue const &lpq);
x
        void insert(char const *v, int p) override;
        [[nodiscard]] char* get_max_priority_value() const override;
        void del_max_priority_value(char *&out_value, int &out_priority) override;
        priority_queue *merge(priority_queue *pq) override = 0;
    };
}