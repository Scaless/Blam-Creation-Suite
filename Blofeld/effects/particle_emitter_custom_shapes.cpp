#include <blofeld-private-pch.h>

namespace blofeld
{

TAG_BLOCK(particle_emitter_custom_point, s_particle_emitter_custom_points::k_maximum_points)
{
	FIELD( _field_short_integer, "position_x" ),
	FIELD( _field_short_integer, "position_y" ),
	FIELD( _field_short_integer, "position_z" ),
	FIELD( _field_char_integer, "normal_x" ),
	FIELD( _field_char_integer, "normal_y" ),
	FIELD( _field_char_integer, "normal_z" ),
	FIELD( _field_byte_integer, "correlation" ),
	FIELD( _field_terminator )
};

TAG_GROUP(particle_emitter_custom_points, PARTICLE_EMITTER_CUSTOM_POINTS_TAG)
{
	FIELD( _field_custom, "import" ),
	FIELD( _field_explanation, "PARTICLE POINTS" ),
	FIELD( _field_tag_reference, "source reference!" ),
	FIELD( _field_real_vector_3d, "compression scale" ),
	FIELD( _field_real_vector_3d, "compression offset" ),
	FIELD( _field_block, "points", &particle_emitter_custom_point_block ),
	FIELD( _field_terminator )
};

} // namespace blofeld

