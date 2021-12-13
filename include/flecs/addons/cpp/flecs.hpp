/**
 * @file flecs.hpp
 * @brief Flecs C++ API.
 *
 * Modern, type safe C++11 API
 */

#pragma once

// C++ utilities
#include <type_traits>
#include "utils/utils.hpp"

// Forward declarations
namespace flecs 
{

struct world;
struct world_async_stage;
struct iter;

namespace _ 
{
template <typename T, typename U = int>
struct cpp_type;

template <typename Func, typename ... Components>
struct each_invoker;
} // namespace _
} // namespace flecs

// Types imported from C API
#include "c_types.hpp"

// Mixin forward declarations
#include "mixins/id/decl.hpp"
#include "mixins/entity/decl.hpp"
#include "mixins/component/decl.hpp"
#include "mixins/type/decl.hpp"
#include "mixins/term/decl.hpp"
#include "mixins/filter/decl.hpp"
#include "mixins/event/decl.hpp"
#include "mixins/query/decl.hpp"
#include "mixins/trigger/decl.hpp"
#include "mixins/observer/decl.hpp"
#ifdef FLECS_MODULE
#include "mixins/module/decl.hpp"
#endif
#ifdef FLECS_SYSTEM
#include "mixins/system/decl.hpp"
#endif
#ifdef FLECS_PIPELINE
#include "mixins/pipeline/decl.hpp"
#endif
#ifdef FLECS_TIMER
#include "mixins/timer/decl.hpp"
#endif
#ifdef FLECS_SNAPSHOT
#include "mixins/snapshot/decl.hpp"
#endif
#ifdef FLECS_DOC
#include "mixins/doc/decl.hpp"
#endif
#ifdef FLECS_REST
#include "mixins/rest/decl.hpp"
#endif

// Mixins (remove from list to disable)
namespace flecs {
using Mixins = mixin_list<
    id_m,
    entity_m,
    component_m,
    type_m,
    term_m,
    filter_m,
    query_m,
    event_m,
    trigger_m,
    observer_m
#ifdef FLECS_MODULE
    , module_m
#endif
#ifdef FLECS_SYSTEM
    , system_m
#endif
#ifdef FLECS_PIPELINE
    , pipeline_m
#endif
#ifdef FLECS_TIMER
    , timer_m
#endif
#ifdef FLECS_SNAPSHOT
    , snapshot_m
#endif
#ifdef FLECS_DOC
    , doc_m
#endif
#ifdef FLECS_REST
    , rest_m
#endif
>;
}

#include "log.hpp"
#include "pair.hpp"
#include "lifecycle_traits.hpp"
#include "world.hpp"
#include "iter.hpp"
#include "ref.hpp"
#include "entity.hpp"
#include "invoker.hpp"
#include "utils/iterable.hpp"
#include "component.hpp"
#include "type.hpp"

// Mixin implementations
#include "mixins/id/impl.hpp"
#include "mixins/entity/impl.hpp"
#include "mixins/component/impl.hpp"
#include "mixins/type/impl.hpp"
#include "mixins/term/impl.hpp"
#include "mixins/filter/impl.hpp"
#include "mixins/event/impl.hpp"
#include "mixins/query/impl.hpp"
#include "mixins/trigger/impl.hpp"
#include "mixins/observer/impl.hpp"
#ifdef FLECS_MODULE
#include "mixins/module/impl.hpp"
#endif
#ifdef FLECS_SYSTEM
#include "mixins/system/impl.hpp"
#endif
#ifdef FLECS_PIPELINE
#include "mixins/pipeline/impl.hpp"
#endif
#ifdef FLECS_TIMER
#include "mixins/timer/impl.hpp"
#endif
#ifdef FLECS_SNAPSHOT
#include "mixins/snapshot/impl.hpp"
#endif
#ifdef FLECS_DOC
#include "mixins/doc/impl.hpp"
#endif
#ifdef FLECS_REST
#include "mixins/rest/impl.hpp"
#endif

#include "impl.hpp"
