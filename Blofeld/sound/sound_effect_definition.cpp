#include <blofeld-private-pch.h>

namespace blofeld
{

TAG_BLOCK(sound_effect_templates, k_maximum_number_of_sound_effect_templates)
{
	FIELD( _field_string_id, "dsp effect" ),
	FIELD( _field_explanation, "WARNING" ),
	FIELD( _field_data, "explanation" ),
	FIELD( _field_long_flags, "flags" ),
	FIELD( _field_short_integer, "dsp state offset!" ),
	FIELD( _field_short_integer, "dsp state size!" ),
	FIELD( _field_block, "parameters", &sound_effect_template_parameter_block ),
	FIELD( _field_terminator )
};

TAG_BLOCK(sound_effect_template_parameter, k_maximum_number_of_sound_effect_parameters)
{
	FIELD( _field_string_id, "name" ),
	FIELD( _field_enum, "type" ),
	FIELD( _field_word_flags, "flags" ),
	FIELD( _field_long_integer, "hardware offset" ),
	FIELD( _field_long_integer, "default enum integer value" ),
	FIELD( _field_real, "default scalar value" ),
	FIELD( _field_custom ),
	FIELD( _field_struct, "default function" ),
	FIELD( _field_real, "minimum scalar value" ),
	FIELD( _field_real, "maximum scalar value" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(sound_effect_template_additional_sound_input, 1)
{
	FIELD( _field_string_id, "dsp effect" ),
	FIELD( _field_custom ),
	FIELD( _field_struct, "low frequency sound" ),
	FIELD( _field_real, "time period: seconds" ),
	FIELD( _field_terminator )
};

TAG_GROUP(sound_effect_template, SOUND_EFFECT_TEMPLATE_TAG)
{
	FIELD( _field_block, "template collection", &sound_effect_templates_block ),
	FIELD( _field_string_id, "internal dsp effect name{input effect name}" ),
	FIELD( _field_block, "additional sound inputs", &sound_effect_template_additional_sound_input_block ),
	FIELD( _field_terminator )
};

} // namespace blofeld

