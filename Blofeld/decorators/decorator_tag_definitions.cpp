#include <blofeld-private-pch.h>

namespace blofeld
{

TAG_BLOCK(decorator_set_instance_name, SHORT_MAX)
{
	FIELD( _field_string_id, "name^" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(global_decorator_type, BYTE_MAX-1)
{
	FIELD( _field_long_integer, "index!" ),
	FIELD( _field_long_block_index, "mesh^" ),
	FIELD( _field_long_flags, "flags" ),
	FIELD( _field_real, "scale min:[0.0 - 5.0]" ),
	FIELD( _field_real, "scale max:[0.0 - 5.0]" ),
	FIELD( _field_real, "tilt min:degrees" ),
	FIELD( _field_real, "tilt max:degrees" ),
	FIELD( _field_real, "wind min:[0.0 - 1.0]" ),
	FIELD( _field_real, "wind max:[0.0 - 1.0]" ),
	FIELD( _field_real_rgb_color, "color 0" ),
	FIELD( _field_real_rgb_color, "color 1" ),
	FIELD( _field_real_rgb_color, "color 2" ),
	FIELD( _field_real, "ground tint min:[0.0 - 1.0]" ),
	FIELD( _field_real, "ground tint max:[0.0 - 1.0]" ),
	FIELD( _field_real, "hover min:[-1.0 - 1.0]" ),
	FIELD( _field_real, "hover max:[-1.0 - 1.0]" ),
	FIELD( _field_real, "minimum distance between decorators:world units" ),
	FIELD( _field_real, "placement weight:[0.0 - 1.0]" ),
	FIELD( _field_real, "postprocessed weight!" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(decorator_runtime_cluster, MAXIMUM_BLOCKS_PER_CLUSTER)
{
	FIELD( _field_word_integer, "decorator placement count*" ),
	FIELD( _field_byte_integer, "decorator set index*" ),
	FIELD( _field_byte_integer, "decorator instance buffer index*" ),
	FIELD( _field_long_integer, "decorator instance buffer offset*" ),
	FIELD( _field_real_vector_3d, "position bounds min*" ),
	FIELD( _field_real, "bounding sphere radius*" ),
	FIELD( _field_real_vector_3d, "position bounds size*" ),
	FIELD( _field_real_vector_3d, "bounding sphere center*" ),
	FIELD( _field_terminator )
};

TAG_GROUP(decorator_set, DECORATOR_SET_TAG)
{
	FIELD( _field_custom, "link to render model" ),
	FIELD( _field_explanation, "Render models:" ),
	FIELD( _field_tag_reference, "Base{render model}*" ),
	FIELD( _field_tag_reference, "Lod2{render model_lod1}*" ),
	FIELD( _field_tag_reference, "Lod3{render model_lod2}*" ),
	FIELD( _field_tag_reference, "Lod4{render model_lod3}*" ),
	FIELD( _field_block, "render model instance names!", &decorator_set_instance_name_block ),
	FIELD( _field_long_integer, "render model instance name valid count!" ),
	FIELD( _field_tag_reference, "texture" ),
	FIELD( _field_explanation, "RENDERING" ),
	FIELD( _field_byte_flags, "render flags" ),
	FIELD( _field_char_enum, "render shader" ),
	FIELD( _field_char_enum, "light sampling pattern" ),
	FIELD( _field_byte_integer, "version!" ),
	FIELD( _field_real, "translucency A!:dont touch#postprocessed value" ),
	FIELD( _field_real, "translucency B!:dont touch#postprocessed value" ),
	FIELD( _field_real, "translucency C!:dont touch#postprocessed value" ),
	FIELD( _field_real, "translucency:[0..1]#how translucent the material is (0 = opaque, 1 = both sides same intensity), only affects dynamic lights" ),
	FIELD( _field_real, "wavelength X:world units#direction and speed of wave through the world" ),
	FIELD( _field_real, "wavelength Y:world units#direction and speed of wave through the world" ),
	FIELD( _field_real, "wave speed:per second#waves per second through a point" ),
	FIELD( _field_real, "wave frequency:per world unit#number of waves per world unit" ),
	FIELD( _field_real, "shaded dark:#how dark is the dark side of a shaded decorator" ),
	FIELD( _field_real, "shaded bright:#the bright side of a shaded decorator is this much brighter than the dark side" ),
	FIELD( _field_real, "unused1!" ),
	FIELD( _field_real, "unused2!" ),
	FIELD( _field_explanation, "LOD FADE + CULL" ),
	FIELD( _field_real, "early cull:[0 - 1]#cull vertices this percentage sooner than LOD3-nothing transition" ),
	FIELD( _field_real, "cull block size:[0.5-100]world units#decorators are grouped into blocks to be culled in large batches, this determines how much ground each batch covers.  Should be small if you expect to have very dense decorators, and large if you expect them to be sparse" ),
	FIELD( _field_real, "decimation speed!:[0 - infinite]#1 is default" ),
	FIELD( _field_real, "decimation start distance!#[block size by default] decimation offset of the starting point" ),
	FIELD( _field_real, "decimate to!{max decimation percentage}#0 means all the way removed. 100 means nothing" ),
	FIELD( _field_real, "decimation start:world units" ),
	FIELD( _field_real, "decimation end:world units" ),
	FIELD( _field_long_integer, "max valid lod!" ),
	FIELD( _field_explanation, "Lod transitions:" ),
	FIELD( _field_explanation, "Base to LOD2:" ),
	FIELD( _field_real, "start point0{Base to LOD1 cross fading start point}" ),
	FIELD( _field_real, "end point0{Base to LOD1 cross fading end point}" ),
	FIELD( _field_real, "scale0!" ),
	FIELD( _field_real, "offset0!" ),
	FIELD( _field_explanation, "LOD2 to LOD3:" ),
	FIELD( _field_real, "start point1{LOD1 to LOD2 cross fading start point}" ),
	FIELD( _field_real, "end point1{LOD1 to LOD2 cross fading end point}" ),
	FIELD( _field_real, "scale1!" ),
	FIELD( _field_real, "offset1!" ),
	FIELD( _field_explanation, "LOD3 to LOD4:" ),
	FIELD( _field_real, "start point2{LOD2 to LOD3 cross fading start point}" ),
	FIELD( _field_real, "end point2{LOD2 to LOD3 cross fading end point}" ),
	FIELD( _field_real, "scale2!" ),
	FIELD( _field_real, "offset2!" ),
	FIELD( _field_explanation, "LOD4 to nothing:" ),
	FIELD( _field_real, "start point3{LOD3 to nothing cross fading start point}" ),
	FIELD( _field_real, "end point3{LOD3 to nothing cross fading end point}" ),
	FIELD( _field_real, "scale3!" ),
	FIELD( _field_real, "offset3!" ),
	FIELD( _field_explanation, "DECORATOR TYPES" ),
	FIELD( _field_block, "decorator types", &global_decorator_type_block ),
	FIELD( _field_terminator )
};

} // namespace blofeld

