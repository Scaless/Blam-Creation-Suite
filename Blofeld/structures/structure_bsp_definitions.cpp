#include <blofeld-private-pch.h>

namespace blofeld
{

TAG_BLOCK(structure_edge_to_seam_edge_mapping, ((true) ? 2621440 : UNSIGNED_SHORT_MAX))
{
	FIELD( _field_short_integer, "seam_index*!" ),
	FIELD( _field_short_integer, "seam_edge_index*!" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_collision_materials, MAXIMUM_COLLISION_MATERIALS_PER_STRUCTURE)
{
	FIELD( _field_tag_reference, "render method{old shader}*^" ),
	FIELD( _field_string_id, "override material name" ),
	FIELD( _field_short_integer, "runtime global material index!" ),
	FIELD( _field_short_block_index, "conveyor surface index*" ),
	FIELD( _field_short_block_index, "seam mapping index*" ),
	FIELD( _field_word_flags, "flags*" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_bsp_leaf, ((true) ? 16*((1<<(k_bsp3d_node_child_index_bits-1))) : ((1<<(k_bsp3d_node_child_index_bits-1)))))
{
	FIELD( _field_byte_integer, "cluster*" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_super_node_aabbs, (k_bsp3d_maximum_super_node_count)*k_super_node_child_indices_count)
{
	FIELD( _field_real, "x0" ),
	FIELD( _field_real, "x1" ),
	FIELD( _field_real, "y0" ),
	FIELD( _field_real, "y1" ),
	FIELD( _field_real, "z0" ),
	FIELD( _field_real, "z1" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(super_node_mappings, (k_bsp3d_maximum_super_node_count))
{
	FIELD( _field_short_integer, "parent_super_node_index!*" ),
	FIELD( _field_char_integer, "parent_internal_node_index!*" ),
	FIELD( _field_byte_flags, "flags!*" ),
	FIELD( _field_long_integer, "has_traversal_geometry_mask!*" ),
	FIELD( _field_short_block_index, "first_traversal_geometry_index!*" ),
	FIELD( _field_short_block_index, "first_aabb_index!*" ),
	FIELD( _field_long_integer, "aabb_mask!*" ),
	FIELD( _field_short_block_index, "non_terminal_traversal_geometry_index!*" ),
	FIELD( _field_pad, "pad", 2 ),
	FIELD( _field_terminator )
};

TAG_BLOCK(super_node_recursable_masks, (k_bsp3d_maximum_super_node_count))
{
	FIELD( _field_short_integer, "mask!*" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_super_node_traversal_geometry, k_short_max)
{
	FIELD( _field_block, "portal_indices!*", &structure_super_node_traversal_geometry_indices_block ),
	FIELD( _field_block, "seam_indices!*", &structure_super_node_traversal_geometry_indices_block ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_super_node_traversal_geometry_indices, ((MAXIMUM_CLUSTER_PORTALS_PER_STRUCTURE)>(k_structure_seam_maximum_seam_count)?(MAXIMUM_CLUSTER_PORTALS_PER_STRUCTURE):(k_structure_seam_maximum_seam_count)))
{
	FIELD( _field_short_integer, "index!*" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_surface, ((true) ? SHORT_MAX<<3 : SHORT_MAX))
{
	FIELD( _field_long_integer, "first_structure_surface_to_triangle_mapping_index*" ),
	FIELD( _field_long_integer, "structure_surface_to_triangle_mapping_count*" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_surface_to_triangle_mapping, (8*((true) ? SHORT_MAX<<3 : SHORT_MAX)))
{
	FIELD( _field_dword_integer, "manual byteswarp1*" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_bsp_cluster_portal, MAXIMUM_CLUSTER_PORTALS_PER_STRUCTURE)
{
	FIELD( _field_struct, "oriented bounds" ),
	FIELD( _field_short_integer, "back cluster*" ),
	FIELD( _field_short_integer, "front cluster*" ),
	FIELD( _field_long_integer, "plane index*" ),
	FIELD( _field_real_point_3d, "centroid*" ),
	FIELD( _field_real, "bounding radius*" ),
	FIELD( _field_long_flags, "flags*" ),
	FIELD( _field_block, "vertices*", &structure_bsp_cluster_portal_vertex_block ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_bsp_cluster_portal_vertex, MAXIMUM_VERTICES_PER_CLUSTER_PORTAL)
{
	FIELD( _field_real_point_3d, "point*" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_bsp_detail_object_data, 1)
{
	FIELD( _field_block, "cells", &global_detail_object_cells_block ),
	FIELD( _field_block, "instances", &global_detail_object_block ),
	FIELD( _field_block, "counts", &global_detail_object_counts_block ),
	FIELD( _field_block, "z reference vectors", &global_z_reference_vector_block ),
	FIELD( _field_pad, "KXILLD", 1 ),
	FIELD( _field_pad, "EDFPN", 3 ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_bsp_cluster, MAXIMUM_CLUSTERS_PER_STRUCTURE)
{
	FIELD( _field_explanation, "CLUSTER INFO" ),
	FIELD( _field_real_bounds, "bounds x*" ),
	FIELD( _field_real_bounds, "bounds y*" ),
	FIELD( _field_real_bounds, "bounds z*" ),
	FIELD( _field_pad, "DING", 1 ),
	FIELD( _field_char_integer, "atmosphere index*" ),
	FIELD( _field_char_integer, "camera fx index*" ),
	FIELD( _field_char_integer, "weather index*" ),
	FIELD( _field_short_block_index, "acoustics*" ),
	FIELD( _field_short_integer, "acoustics sound cluster index" ),
	FIELD( _field_short_integer, "runtime first decal index!" ),
	FIELD( _field_short_integer, "runtime decal cound!" ),
	FIELD( _field_word_flags, "flags" ),
	FIELD( _field_pad, "ERERRFQ", 2 ),
	FIELD( _field_block, "predicted resources*", &g_null_block ),
	FIELD( _field_block, "portals*", &structure_bsp_cluster_portal_index_block ),
	FIELD( _field_short_integer, "mesh index*" ),
	FIELD( _field_short_integer, "instance imposter cluster mopp index" ),
	FIELD( _field_block, "seam indices*!", &seam_indices_block ),
	FIELD( _field_block, "decorator groups*", &decorator_runtime_cluster_block ),
	FIELD( _field_block, "cheap light marker refs*", &cheap_light_marker_ref_block ),
	FIELD( _field_block, "pvs bound object identifiers*!", &pvs_bound_object_identifiers_block ),
	FIELD( _field_block, "pvs bound object references*!", &pvs_bound_object_references_block ),
	FIELD( _field_block, "cluster cubemaps", &structure_cluster_cubemap_block ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_bsp_cluster_portal_index, MAXIMUM_CLUSTER_PORTALS_PER_CLUSTER)
{
	FIELD( _field_short_integer, "portal index*" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(seam_indices, k_structure_seam_maximum_seam_count)
{
	FIELD( _field_char_integer, "seam index*" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(cheap_light_marker_ref, MAXIMUM_MARKERS_PER_STRUCTURE)
{
	FIELD( _field_short_block_index, "cheap light reference reference" ),
	FIELD( _field_pad, "WHATIZZIT", 2 ),
	FIELD( _field_terminator )
};

TAG_BLOCK(pvs_bound_object_identifiers, k_maximum_scenario_object_datum_count)
{
	FIELD( _field_struct, "object ID*!" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(pvs_bound_object_references, k_maximum_scenario_object_datum_count)
{
	FIELD( _field_struct, "scenario object reference*!" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_material_lighting_info, SHORT_MAX)
{
	FIELD( _field_real, "emissive power" ),
	FIELD( _field_real_rgb_color, "emissive color" ),
	FIELD( _field_real, "emissive quality" ),
	FIELD( _field_real, "emissive focus" ),
	FIELD( _field_long_flags, "flags" ),
	FIELD( _field_real, "attenuation falloff" ),
	FIELD( _field_real, "attenuation cutoff" ),
	FIELD( _field_real, "bounce ratio" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_bsp_sky_owner_cluster, MAXIMUM_SKIES_PER_SCENARIO)
{
	FIELD( _field_short_integer, "cluster owner*" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_bsp_conveyor_surface, MAXIMUM_COLLISION_MATERIALS_PER_STRUCTURE)
{
	FIELD( _field_real_vector_3d, "u" ),
	FIELD( _field_real_vector_3d, "v" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_cookie_cutter_definition, k_kilo)
{
	FIELD( _field_custom, "Cookie Cutter" ),
	FIELD( _field_struct, "collision model" ),
	FIELD( _field_custom ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_bsp_marker, MAXIMUM_MARKERS_PER_STRUCTURE)
{
	FIELD( _field_char_enum, "marker type*" ),
	FIELD( _field_pad, "pad", 3 ),
	FIELD( _field_string, "marker parameter*" ),
	FIELD( _field_real_quaternion, "rotation" ),
	FIELD( _field_real_point_3d, "position*" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_bsp_marker_light_palette, MAXIMUM_MARKERS_PER_STRUCTURE)
{
	FIELD( _field_tag_reference, "light tag" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_bsp_marker_light_index, MAXIMUM_MARKERS_PER_STRUCTURE)
{
	FIELD( _field_short_integer, "palette index" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_bsp_runtime_decal, MAXIMUM_DECALS_PER_STRUCTURE)
{
	FIELD( _field_short_integer, "decal palette index!" ),
	FIELD( _field_pad, "post-decal-palette-index-pad", 2 ),
	FIELD( _field_struct, "manual bsp flags" ),
	FIELD( _field_real_quaternion, "rotation*" ),
	FIELD( _field_real_point_3d, "position*" ),
	FIELD( _field_real, "scale_x(scale}*" ),
	FIELD( _field_real, "scale_y*" ),
	FIELD( _field_real, "cull angle" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_bsp_environment_object_palette, MAXIMUM_ENVIRONMENT_OBJECT_PALETTE_ENTRIES_PER_STRUCTURE)
{
	FIELD( _field_tag_reference, "definition^" ),
	FIELD( _field_tag_reference, "model" ),
	FIELD( _field_long_integer, "GVEYN!" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_bsp_environment_object, MAXIMUM_ENVIRONMENT_OBJECTS_PER_STRUCTURE)
{
	FIELD( _field_string, "name^" ),
	FIELD( _field_real_quaternion, "rotation" ),
	FIELD( _field_real_point_3d, "translation" ),
	FIELD( _field_real, "scale" ),
	FIELD( _field_short_block_index, "palette_index" ),
	FIELD( _field_byte_flags, "flags" ),
	FIELD( _field_pad, "QHUGQ", 1 ),
	FIELD( _field_long_integer, "unique id*" ),
	FIELD( _field_tag, "exported object type" ),
	FIELD( _field_string_id, "scenario object name" ),
	FIELD( _field_string_id, "variant name" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_instance_cluster_definition, k_maximum_cluster_to_instance_group_block_size)
{
	FIELD( _field_long_flags, "flags" ),
	FIELD( _field_block, "instance group indices", &index_list_block ),
	FIELD( _field_terminator )
};

TAG_BLOCK(index_list, 4 * k_kilo)
{
	FIELD( _field_word_integer, "index" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_instance_group_definition, 4 * k_kilo)
{
	FIELD( _field_real_point_3d, "center" ),
	FIELD( _field_real, "radius" ),
	FIELD( _field_short_integer, "cluster count" ),
	FIELD( _field_word_flags, "flags" ),
	FIELD( _field_real, "maximum imposter distance*" ),
	FIELD( _field_real, "minimum centrifugal distance from group center*" ),
	FIELD( _field_real, "minimum imposter distance squared*" ),
	FIELD( _field_block, "instance indices", &index_list_block ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_instance_imposter_info, k_maximum_instance_geometry_instances_per_structure_bsp)
{
	FIELD( _field_string_id, "name" ),
	FIELD( _field_char_integer, "imposter policy" ),
	FIELD( _field_pad, "parasdd", 3 ),
	FIELD( _field_real, "transition distance" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(runtime_decorator_set, MAXIMUM_DECORATOR_SETS_PER_SCENARIO)
{
	FIELD( _field_tag_reference, "decorator set reference*" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(bsp_preplaced_decal_set_reference, MAXIMUM_DECALS_PER_STRUCTURE)
{
	FIELD( _field_long_integer, "decal definition index!" ),
	FIELD( _field_char_integer, "location bsp 0!" ),
	FIELD( _field_byte_integer, "location cluster 0!" ),
	FIELD( _field_char_integer, "location bsp 1!" ),
	FIELD( _field_byte_integer, "location cluster 1!" ),
	FIELD( _field_char_integer, "location bsp 2!" ),
	FIELD( _field_byte_integer, "location cluster 2!" ),
	FIELD( _field_char_integer, "location bsp 3!" ),
	FIELD( _field_byte_integer, "location cluster 3!" ),
	FIELD( _field_real_point_3d, "center*" ),
	FIELD( _field_short_integer, "first decal ref index!" ),
	FIELD( _field_short_integer, "decal ref count!" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(bsp_preplaced_decal_reference, MAXIMUM_DECALS_PER_STRUCTURE)
{
	FIELD( _field_short_integer, "index start" ),
	FIELD( _field_short_integer, "index count" ),
	FIELD( _field_short_integer, "vertex start" ),
	FIELD( _field_short_integer, "vertex count" ),
	FIELD( _field_short_integer, "definition block index" ),
	FIELD( _field_pad, "paddddg", 2 ),
	FIELD( _field_real_point_2d, "spirit corner" ),
	FIELD( _field_real_vector_2d, "spirit size" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(transparent_planes, 32*k_kilo)
{
	FIELD( _field_short_integer, "section index" ),
	FIELD( _field_short_integer, "part index" ),
	FIELD( _field_real_plane_3d, "plane" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_bsp_debug_info, 1)
{
	FIELD( _field_pad, "BRQYEF", 64 ),
	FIELD( _field_block, "clusters*", &structure_bsp_cluster_debug_info_block ),
	FIELD( _field_block, "fog planes*", &structure_bsp_fog_plane_debug_info_block ),
	FIELD( _field_block, "fog zones*", &structure_bsp_fog_zone_debug_info_block ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_bsp_cluster_debug_info, MAXIMUM_CLUSTERS_PER_STRUCTURE)
{
	FIELD( _field_word_flags, "errors*" ),
	FIELD( _field_word_flags, "warnings*" ),
	FIELD( _field_pad, "KHWRB", 28 ),
	FIELD( _field_block, "lines*", &structure_bsp_debug_info_render_line_block ),
	FIELD( _field_block, "fog plane indices*", &structure_bsp_debug_info_indices_block ),
	FIELD( _field_block, "visible fog plane indices*", &structure_bsp_debug_info_indices_block ),
	FIELD( _field_block, "vis-fog omission cluster indices*", &structure_bsp_debug_info_indices_block ),
	FIELD( _field_block, "containing fog zone indices*", &structure_bsp_debug_info_indices_block ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_bsp_debug_info_render_line, SHORT_MAX)
{
	FIELD( _field_enum, "type*" ),
	FIELD( _field_short_integer, "code*" ),
	FIELD( _field_short_integer, "pad thai*" ),
	FIELD( _field_pad, "BNQS", 2 ),
	FIELD( _field_real_point_3d, "point 0*" ),
	FIELD( _field_real_point_3d, "point 1*" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_bsp_debug_info_indices, SHORT_MAX)
{
	FIELD( _field_long_integer, "index*" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_bsp_fog_plane_debug_info, MAXIMUM_FOG_PLANES_PER_STRUCTURE)
{
	FIELD( _field_long_integer, "fog zone index*" ),
	FIELD( _field_pad, "WZGH", 24 ),
	FIELD( _field_long_integer, "connected plane designator*" ),
	FIELD( _field_block, "lines*", &structure_bsp_debug_info_render_line_block ),
	FIELD( _field_block, "intersected cluster indices*", &structure_bsp_debug_info_indices_block ),
	FIELD( _field_block, "inf. extent cluster indices*", &structure_bsp_debug_info_indices_block ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_bsp_fog_zone_debug_info, MAXIMUM_FOG_ZONES_PER_STRUCTURE)
{
	FIELD( _field_long_integer, "media index:scenario fog plane*" ),
	FIELD( _field_long_integer, "base fog plane index*" ),
	FIELD( _field_pad, "RB", 24 ),
	FIELD( _field_block, "lines*", &structure_bsp_debug_info_render_line_block ),
	FIELD( _field_block, "immersed cluster indices*", &structure_bsp_debug_info_indices_block ),
	FIELD( _field_block, "bounding fog plane indices*", &structure_bsp_debug_info_indices_block ),
	FIELD( _field_block, "collision fog plane indices*", &structure_bsp_debug_info_indices_block ),
	FIELD( _field_terminator )
};

TAG_BLOCK(widget_reference, MAXIMUM_MARKERS_PER_STRUCTURE)
{
	FIELD( _field_short_integer, "marker index*" ),
	FIELD( _field_pad, "gnlao", 2 ),
	FIELD( _field_tag_reference, "widget ref*" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(cheap_light_reference, MAXIMUM_MARKERS_PER_STRUCTURE)
{
	FIELD( _field_short_integer, "marker index*" ),
	FIELD( _field_pad, "ldajk", 2 ),
	FIELD( _field_tag_reference, "cheap light*" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_external_instanced_geometry_references, k_external_instanced_geometry_max)
{
	FIELD( _field_tag_reference, "prefab reference" ),
	FIELD( _field_string_id, "name*^" ),
	FIELD( _field_real, "scale" ),
	FIELD( _field_real_vector_3d, "forward" ),
	FIELD( _field_real_vector_3d, "left" ),
	FIELD( _field_real_vector_3d, "up" ),
	FIELD( _field_real_point_3d, "position" ),
	FIELD( _field_short_integer, "mesh count!" ),
	FIELD( _field_short_integer, "mesh block index!" ),
	FIELD( _field_short_integer, "light count!" ),
	FIELD( _field_short_integer, "light instance block index!" ),
	FIELD( _field_short_integer, "dynamic object count!" ),
	FIELD( _field_short_integer, "dynamic object block index!" ),
	FIELD( _field_word_flags, "override flags" ),
	FIELD( _field_pad, "SDFSDEE", 2 ),
	FIELD( _field_char_enum, "override pathfinding policy" ),
	FIELD( _field_char_enum, "override lightmapping policy" ),
	FIELD( _field_char_enum, "override imposter policy" ),
	FIELD( _field_char_enum, "override streaming priority*" ),
	FIELD( _field_real, "override lightmap resolution scale" ),
	FIELD( _field_real, "override imposter transition distance" ),
	FIELD( _field_real, "override imposter brightness" ),
	FIELD( _field_real, "override light channel flags" ),
	FIELD( _field_word_flags, "instance flags Mask" ),
	FIELD( _field_word_flags, "instance policy mask" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structure_bsp_obb_volume, 4096)
{
	FIELD( _field_real_point_3d, "origin" ),
	FIELD( _field_real_vector_3d, "axis 1" ),
	FIELD( _field_real_vector_3d, "axis 2" ),
	FIELD( _field_real_vector_3d, "axis 3" ),
	FIELD( _field_dword_integer, "type" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(AnimGraphDependencyBlock, 256)
{
	FIELD( _field_tag_reference, "graph" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structureBspFxMarkerBlock, MAXIMUM_MARKERS_PER_STRUCTURE)
{
	FIELD( _field_string, "marker name^" ),
	FIELD( _field_real_quaternion, "rotation*" ),
	FIELD( _field_real_point_3d, "position*" ),
	FIELD( _field_tag_reference, "optional attached effect" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(structureMetadataLightConeMarkerBlock, MAXIMUM_MARKERS_PER_STRUCTURE)
{
	FIELD( _field_string, "marker name^" ),
	FIELD( _field_real_quaternion, "rotation" ),
	FIELD( _field_real_point_3d, "position" ),
	FIELD( _field_real, "length" ),
	FIELD( _field_real, "width" ),
	FIELD( _field_real, "intensity" ),
	FIELD( _field_real_argb_color, "light color" ),
	FIELD( _field_tag_reference, "light cone tag" ),
	FIELD( _field_tag_reference, "intensity curve" ),
	FIELD( _field_terminator )
};

TAG_GROUP(prefab, PREFAB_TAG)
{
	FIELD( _field_tag_reference, "bsp reference" ),
	FIELD( _field_terminator )
};

TAG_GROUP(scenario_structure_bsp, SCENARIO_STRUCTURE_BSP_TAG)
{
	FIELD( _field_struct, "build identifier*" ),
	FIELD( _field_struct, "parent build identifier*" ),
	FIELD( _field_long_integer, "import info checksum*" ),
	FIELD( _field_tag_reference, "structure lighting_info^" ),
	FIELD( _field_long_integer, "import version*!" ),
	FIELD( _field_tag_reference, "structure meta data*" ),
	FIELD( _field_word_flags, "flags*!" ),
	FIELD( _field_word_flags, "content policy flags*!" ),
	FIELD( _field_word_flags, "failed content policy flags*!" ),
	FIELD( _field_pad, "faild policy pad*!", 2 ),
	FIELD( _field_block, "seam identifiers*!", &structure_seam_mapping_block ),
	FIELD( _field_block, "edge to seam edge*!", &structure_edge_to_seam_edge_mapping_block ),
	FIELD( _field_block, "collision materials*", &structure_collision_materials_block ),
	FIELD( _field_block, "leaves*!", &structure_bsp_leaf_block ),
	FIELD( _field_block, "super aabbs*!", &structure_super_node_aabbs_block ),
	FIELD( _field_block, "super node parent mappings*!", &super_node_mappings_block ),
	FIELD( _field_block, "super node recursable_masks*!", &super_node_recursable_masks_block ),
	FIELD( _field_block, "structure_super_node_traversal_geometry_block*!", &structure_super_node_traversal_geometry_block ),
	FIELD( _field_struct, "instance kd hierarchy!" ),
	FIELD( _field_real_bounds, "world bounds x*" ),
	FIELD( _field_real_bounds, "world bounds y*" ),
	FIELD( _field_real_bounds, "world bounds z*" ),
	FIELD( _field_block, "large structure surfaces*", &structure_surface_block ),
	FIELD( _field_block, "structure surface to triangle mapping*", &structure_surface_to_triangle_mapping_block ),
	FIELD( _field_block, "cluster portals*", &structure_bsp_cluster_portal_block ),
	FIELD( _field_block, "detail objects*", &structure_bsp_detail_object_data_block ),
	FIELD( _field_block, "clusters*", &structure_bsp_cluster_block ),
	FIELD( _field_block, "materials*", &global_geometry_material_block ),
	FIELD( _field_block, "emissive materials*", &structure_material_lighting_info_block ),
	FIELD( _field_block, "sky owner cluster*", &structure_bsp_sky_owner_cluster_block ),
	FIELD( _field_block, "conveyor surfaces*", &structure_bsp_conveyor_surface_block ),
	FIELD( _field_block, "breakable surface sets*", &breakable_surface_set_block ),
	FIELD( _field_block, "pathfinding data", &pathfinding_data_block ),
	FIELD( _field_block, "cookie cutters", &structure_cookie_cutter_definition_block ),
	FIELD( _field_block, "acoustics palette", &scenario_acoustics_palette_block ),
	FIELD( _field_data, "sound PAS data*" ),
	FIELD( _field_block, "markers*", &structure_bsp_marker_block ),
	FIELD( _field_block, "marker light palette*", &structure_bsp_marker_light_palette_block ),
	FIELD( _field_block, "marker light palette index*", &structure_bsp_marker_light_index_block ),
	FIELD( _field_block, "runtime decals*", &structure_bsp_runtime_decal_block ),
	FIELD( _field_block, "(DEPRECATED) environment object palette*", &structure_bsp_environment_object_palette_block ),
	FIELD( _field_block, "(DEPRECATED) environment objects*", &structure_bsp_environment_object_block ),
	FIELD( _field_pad, "IMISWXUG", 4 ),
	FIELD( _field_block, "leaf map leaves*", &global_map_leaf_block ),
	FIELD( _field_block, "leaf map connections*", &global_leaf_connection_block ),
	FIELD( _field_block, "errors*", &global_error_report_categories_block ),
	FIELD( _field_block, "cluster to instance group mopps", &mopp_code_definition_block ),
	FIELD( _field_block, "instance group to instance mopps", &mopp_code_definition_block ),
	FIELD( _field_block, "cluster to instance group spheres", &structure_instance_cluster_definition_block ),
	FIELD( _field_block, "instance group to instance spheres", &structure_instance_group_definition_block ),
	FIELD( _field_block, "instanced geometry instances*", &structure_bsp_instanced_geometry_instances_block ),
	FIELD( _field_block, "instanced geometry instance names*", &structure_bsp_instanced_geometry_instances_names_block ),
	FIELD( _field_tag_reference, "instance imposters" ),
	FIELD( _field_block, "instance imposter infos", &structure_instance_imposter_info_block ),
	FIELD( _field_long_integer, "Instance Geometry Tag Instance Count!" ),
	FIELD( _field_custom, "decorator info" ),
	FIELD( _field_block, "decorator sets*", &runtime_decorator_set_block ),
	FIELD( _field_struct, "decorator instance buffer!*" ),
	FIELD( _field_custom ),
	FIELD( _field_custom, "decals info" ),
	FIELD( _field_block, "preplaced decal sets*", &bsp_preplaced_decal_set_reference_block ),
	FIELD( _field_block, "preplaced decals*", &bsp_preplaced_decal_reference_block ),
	FIELD( _field_struct, "preplaced decal geometry!*" ),
	FIELD( _field_custom ),
	FIELD( _field_block, "acoustics sound clusters!", &structure_bsp_sound_cluster_block ),
	FIELD( _field_block, "transparent planes*", &transparent_planes_block ),
	FIELD( _field_block, "debug info*", &structure_bsp_debug_info_block ),
	FIELD( _field_struct, "structure_physics*" ),
	FIELD( _field_struct, "render geometry*" ),
	FIELD( _field_block, "widget references", &widget_reference_block ),
	FIELD( _field_block, "cheap light references", &cheap_light_reference_block ),
	FIELD( _field_struct, "resource interface" ),
	FIELD( _field_custom, "Any Platform Temporary Storage" ),
	FIELD( _field_block, "Any Platform Temp Havok Data*!", &structureIOHavokDataBlock_block ),
	FIELD( _field_custom ),
	FIELD( _field_block, "external references", &structure_external_instanced_geometry_references_block ),
	FIELD( _field_tag_reference, "dependencies" ),
	FIELD( _field_long_integer, "base material count*!" ),
	FIELD( _field_block, "obb volume list", &structure_bsp_obb_volume_block ),
	FIELD( _field_block, "scripted dependencies", &hs_references_block ),
	FIELD( _field_block, "pupAnimations*!", &AnimGraphDependencyBlock_block ),
	FIELD( _field_terminator )
};

} // namespace blofeld

