class priority_queue {
public:
    virtual ~priority_queue() = default;

    virtual void insert(char const *v, int p) = 0;
    virtual char *get_max_priority_value() = 0;
    virtual void del_max_priority_value() = 0;
    virtual priority_queue &merge(priority_queue const &pq) = 0;
};