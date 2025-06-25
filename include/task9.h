#include <cstring>
#include "task5.h"
namespace lab {

    class leftist_priority_queue : public priority_queue {
    private:
        struct lpq_node {
            int priority;
            char *value;
            int rank;
            lpq_node *left;
            lpq_node *right;

            lpq_node(int p, char const *v, int r);
            ~lpq_node() noexcept;
            lpq_node(lpq_node const &bpqn);
            lpq_node &operator =(lpq_node const &bpqn);
            static lpq_node *deep_copy_tree(lpq_node *bpqn);
        };

        lpq_node *root;

        static lpq_node *merge_nodes(lpq_node *lpqn1, lpq_node *lpqn2);
    public:
        leftist_priority_queue();
        ~leftist_priority_queue();
        leftist_priority_queue(leftist_priority_queue const &lpq);

        void insert(char const *v, int p) override;
        [[nodiscard]] char* get_max_priority_value() const override;
        void del_max_priority_value(char *&out_value, int &out_priority) override;
        priority_queue *merge(priority_queue *pq) override;
    };
}