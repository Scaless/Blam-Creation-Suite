#include "mantlereflect-private-pch.h"

c_mantle_tag_groups_generator::c_mantle_tag_groups_generator(const wchar_t* output_header_file, std::vector<c_reflection_type_container*>& reflection_types) :
	c_ast_source_generator(output_header_file, nullptr, reflection_types)
{

}

void c_mantle_tag_groups_generator::run()
{
	header_string_stream << "#pragma once" << std::endl << std::endl;

	write_tag_group_enum(header_string_stream);
}

void c_mantle_tag_groups_generator::write_tag_group_enum(std::stringstream& stringstream)
{
	stringstream << std::endl;
	stringstream << "enum e_tag_group : int32_t" << std::endl;
	stringstream << "{" << std::endl;
	stringstream << "\t_tag_group_invalid = -1," << std::endl;
	for (c_reflection_type_container* reflection_type_container : reflection_types)
	{
		assert(reflection_type_container);

		if (reflection_type_container->raw_tag_group.empty()) continue; 

		stringstream << std::nouppercase;
		std::string enum_name = reflection_type_container->type_name.substr(2, reflection_type_container->type_name.rfind("_definition") - 2);
		stringstream << "\t_tag_group_" << enum_name << " = '" << reflection_type_container->tag_group << "'" << "," << std::endl;
	}
	stringstream << "};" << std::endl;
	stringstream << std::endl;
}