
namespace flecs
{

////////////////////////////////////////////////////////////////////////////////
//// Utility for iterating over tables that match a filter
////////////////////////////////////////////////////////////////////////////////

class filter_iterator
{
public:
    filter_iterator(ecs_iter_next_action_t action)
        : m_world(nullptr)
        , m_has_next(false)
        , m_iter{ } 
        , m_action(action) { }

    filter_iterator(const world& world, const filter& filter, ecs_iter_next_action_t action)
        : m_world( world.c_ptr() )
        , m_iter( ecs_filter_iter(m_world, filter.c_ptr()) ) 
        , m_action(action)
    { 
        m_has_next = m_action(&m_iter);
    }

    filter_iterator(const world& world, const snapshot& snapshot, const filter& filter, ecs_iter_next_action_t action) 
        : m_world( world.c_ptr() )
        , m_iter( ecs_snapshot_iter(snapshot.c_ptr(), filter.c_ptr()) )
        , m_action(action)
    {
        m_has_next = m_action(&m_iter);
    }

    bool operator!=(filter_iterator const& other) const {
        return m_has_next != other.m_has_next;
    }

    flecs::iter const operator*() const {
        return flecs::iter(&m_iter);
    }

    filter_iterator& operator++() {
        m_has_next = m_action(&m_iter);
        return *this;
    }

private:
    world_t *m_world;
    bool m_has_next;
    ecs_iter_t m_iter;
    ecs_iter_next_action_t m_action;
};


////////////////////////////////////////////////////////////////////////////////
//// Tree iterator
////////////////////////////////////////////////////////////////////////////////

class tree_iterator
{
public:
    tree_iterator()
        : m_has_next(false)
        , m_iter{ } { }

    tree_iterator(flecs::entity entity) 
        : m_iter( ecs_scope_iter(entity.world().c_ptr(), entity.id()) )
    {
        m_has_next = ecs_scope_next(&m_iter);
    }

    bool operator!=(tree_iterator const& other) const {
        return m_has_next != other.m_has_next;
    }

    flecs::iter const operator*() const {
        return flecs::iter(&m_iter);
    }

    tree_iterator& operator++() {
        m_has_next = ecs_scope_next(&m_iter);
        return *this;
    }

private:
    bool m_has_next;
    ecs_iter_t m_iter;
};

////////////////////////////////////////////////////////////////////////////////
//// Utility for creating a world-based filter iterator
////////////////////////////////////////////////////////////////////////////////

class world_filter {
public:
    world_filter(const world& world, const filter& filter) 
        : m_world( world )
        , m_filter( filter ) { }

    inline filter_iterator begin() const {
        return filter_iterator(m_world, m_filter, ecs_filter_next);
    }

    inline filter_iterator end() const {
        return filter_iterator(ecs_filter_next);
    }

private:
    const world& m_world;
    const filter& m_filter;
};


////////////////////////////////////////////////////////////////////////////////
//// Utility for creating a snapshot-based filter iterator
////////////////////////////////////////////////////////////////////////////////

class snapshot_filter {
public:
    snapshot_filter(const world& world, const snapshot& snapshot, const filter& filter) 
        : m_world( world )
        , m_snapshot( snapshot )
        , m_filter( filter ) { }

    inline filter_iterator begin() const {
        return filter_iterator(m_world, m_snapshot, m_filter, ecs_snapshot_next);
    }

    inline filter_iterator end() const {
        return filter_iterator(ecs_snapshot_next);
    }

private:
    const world& m_world;
    const snapshot& m_snapshot;
    const filter& m_filter;
};


////////////////////////////////////////////////////////////////////////////////
//// Utility for creating a child table iterator
////////////////////////////////////////////////////////////////////////////////

class child_iterator {
public:
    child_iterator(const entity& entity) 
        : m_parent( entity ) { }

    inline tree_iterator begin() const {
        return tree_iterator(m_parent);
    }

    inline tree_iterator end() const {
        return tree_iterator();
    }

private:
    const entity& m_parent;
};


////////////////////////////////////////////////////////////////////////////////
//// Filter fwd declared functions
////////////////////////////////////////////////////////////////////////////////

inline snapshot_filter snapshot::filter(const flecs::filter& filter) {
    return snapshot_filter(m_world, *this, filter);
}

inline filter_iterator snapshot::begin() {
    return filter_iterator(m_world, *this, flecs::filter(m_world), ecs_snapshot_next);
}

inline filter_iterator snapshot::end() {
    return filter_iterator(ecs_snapshot_next);
}

}
