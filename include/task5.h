#include <cstdio>
namespace lab {
    class priority_queue {
    public:
        virtual ~priority_queue() = default;
        virtual void insert(char const *v, int p) = 0;
        [[nodiscard]] virtual char *get_max_priority_value() const = 0;
        virtual void del_max_priority_value(char *&out_value, int &out_priority) = 0;
        virtual priority_queue *merge(priority_queue *pq) = 0;
    };
}