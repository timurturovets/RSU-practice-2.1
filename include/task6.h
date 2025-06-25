#include <cstring>
#include "task5.h"
namespace lab {
    class binary_priority_queue : public priority_queue {
    public:
        explicit binary_priority_queue(size_t size);
        binary_priority_queue(binary_priority_queue const &bpq);
        binary_priority_queue &operator =(binary_priority_queue const &bpq);
        ~binary_priority_queue() override;

        void sift_up(size_t pos);
        void sift_down(size_t pos);

        void insert(char const *value, int priority) override;

        [[nodiscard]] char *get_max_priority_value() const override;
        void del_max_priority_value(char *&out_value, int &out_priority) override;

        priority_queue *merge(priority_queue *pq) override;
    private:
        size_t _size;
        struct binary_priority_queue_node {
            char *value;
            int priority;
        };

        binary_priority_queue_node *_data;

        static void swap(binary_priority_queue_node &n1, binary_priority_queue_node &n2);
        void resize(size_t new_size);
    };
}