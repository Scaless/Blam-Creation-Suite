#include "mantlelib-private-pch.h"

c_virtual_bitmap_resource::c_virtual_bitmap_resource(c_virtual_resource_manager& virtual_resource_manager, v_tag_interface_legacy<s_bitmap_definition_legacy>& bitmap_tag_interface) :
	virtual_resource_manager(virtual_resource_manager),
	bitmap_tag_interface(bitmap_tag_interface)
{

}

c_virtual_bitmap_resource::~c_virtual_bitmap_resource()
{
	virtual_resource_manager.unload_bitmap_resource(this);
	bitmap_tag_interface.virtual_resource_user_data = nullptr;
}