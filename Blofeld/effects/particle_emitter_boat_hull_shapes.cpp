#include <blofeld-private-pch.h>

namespace blofeld
{

TAG_BLOCK(particle_emitter_boat_hull_group, s_particle_emitter_boat_hull_shape_data::k_max_groups_per_hull_shape)
{
	{ _field_string_id, "marker group^" },
	{ _field_terminator },
};

TAG_GROUP(particle_emitter_boat_hull_shape, PARTICLE_EMITTER_BOAT_HULL_SHAPE_TAG)
{
	{ _field_char_enum, "distribution#heuristic used to determine where to spawn particles" },
	{ _field_pad, "PEBHSP1", 3 },
	{ _field_block, "markers", &particle_emitter_boat_hull_group_block },
	{ _field_terminator },
};

} // namespace blofeld
