#include <blofeld-private-pch.h>

namespace blofeld
{

TAG_BLOCK(PuppetShowsBlock, MAXIMUM_PERFORMANCES_PER_SCENARIO)
{
	FIELD( _field_string_id, "name^" ),
	FIELD( _field_string_id, "designerZone" ),
	FIELD( _field_struct, "manual bsp flags*" ),
	FIELD( _field_byte_flags, "flags" ),
	FIELD( _field_pad, "pad", 3 ),
	FIELD( _field_string, "icsPoint0" ),
	FIELD( _field_string, "icsPoint1" ),
	FIELD( _field_string, "icsPoint2" ),
	FIELD( _field_string, "icsPoint3" ),
	FIELD( _field_long_integer, "lastActionId" ),
	FIELD( _field_block, "puppets", &PuppetBlock_block ),
	FIELD( _field_block, "puppetHeaders", &PuppetHeaderBlock_block ),
	FIELD( _field_block, "actions", &PuppetActionHeaderBlock_block ),
	FIELD( _field_block, "subActions", &PuppetSubActionHeaderBlock_block ),
	FIELD( _field_block, "animations", &PuppetAnimationBlock_block ),
	FIELD( _field_block, "paths", &PuppetPathBlock_block ),
	FIELD( _field_block, "points", &PuppetPointBlock_block ),
	FIELD( _field_block, "branches", &PuppetBranchBlock_block ),
	FIELD( _field_block, "scripts", &PuppetScriptBlock_block ),
	FIELD( _field_block, "comments", &CommentsBlock_block ),
	FIELD( _field_terminator )
};

TAG_BLOCK(PuppetBlock, MAX_PUPPETS_PER_SHOW)
{
	FIELD( _field_struct, "header" ),
	FIELD( _field_block, "actions", &PuppetActionBlock_block ),
	FIELD( _field_block, "subActions", &PuppetSubActionBlock_block ),
	FIELD( _field_block, "subTracks", &SubTracksBlock_block ),
	FIELD( _field_long_string, "comment" ),
	FIELD( _field_long_string, "startScript" ),
	FIELD( _field_long_string, "endScript" ),
	FIELD( _field_short_integer, "height" ),
	FIELD( _field_byte_flags, "editorFlags!*" ),
	FIELD( _field_pad, "pad", 1 ),
	FIELD( _field_terminator )
};

TAG_BLOCK(PuppetActionBlock, MAX_ACTIONS_PER_PUPPET)
{
	FIELD( _field_struct, "header" ),
	FIELD( _field_struct, "animation" ),
	FIELD( _field_struct, "path" ),
	FIELD( _field_long_string, "comment" ),
	FIELD( _field_long_string, "animCondition" ),
	FIELD( _field_dword_integer, "color" ),
	FIELD( _field_byte_flags, "editorFlags!*" ),
	FIELD( _field_pad, "pad", 3 ),
	FIELD( _field_long_integer, "startFrame*" ),
	FIELD( _field_long_integer, "endFrame*" ),
	FIELD( _field_long_integer, "blendFrame*" ),
	FIELD( _field_long_integer, "startPixel*" ),
	FIELD( _field_long_integer, "endPixel*" ),
	FIELD( _field_long_integer, "blendPixel*" ),
	FIELD( _field_long_integer, "blendInDrag*" ),
	FIELD( _field_long_integer, "lengthDrag*" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(PuppetSubActionBlock, MAX_SUB_ACTIONS_PER_PUPPET)
{
	FIELD( _field_struct, "header" ),
	FIELD( _field_struct, "point" ),
	FIELD( _field_struct, "branch" ),
	FIELD( _field_struct, "script" ),
	FIELD( _field_long_string, "comment" ),
	FIELD( _field_long_string, "startCondition" ),
	FIELD( _field_long_string, "endCondition" ),
	FIELD( _field_long_string, "scriptText" ),
	FIELD( _field_block, "branchConditions", &PuppetScriptTextBlock_block ),
	FIELD( _field_dword_integer, "color" ),
	FIELD( _field_byte_integer, "subTrack" ),
	FIELD( _field_byte_flags, "editorFlags!*" ),
	FIELD( _field_pad, "pad", 2 ),
	FIELD( _field_long_integer, "startFrame*" ),
	FIELD( _field_long_integer, "endFrame*" ),
	FIELD( _field_long_integer, "startPixel*" ),
	FIELD( _field_long_integer, "endPixel*" ),
	FIELD( _field_long_integer, "subTrackDrag*" ),
	FIELD( _field_long_integer, "startOffsetDrag*" ),
	FIELD( _field_long_integer, "endOffsetDrag*" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(PuppetScriptTextBlock, MAX_BRANCHES_PER_SUB_ACTION)
{
	FIELD( _field_long_string, "scriptText" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(SubTracksBlock, MAX_SUB_TRACKS)
{
	FIELD( _field_string_id, "name^" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(PuppetHeaderBlock, MAX_PUPPETS_PER_SHOW)
{
	FIELD( _field_byte_flags, "flags" ),
	FIELD( _field_char_enum, "indexType~" ),
	FIELD( _field_pad, "pad", 2 ),
	FIELD( _field_string_id, "name" ),
	FIELD( _field_tag_reference, "type" ),
	FIELD( _field_string_id, "objectName" ),
	FIELD( _field_long_integer, "index~" ),
	FIELD( _field_struct, "position" ),
	FIELD( _field_string_id, "startScriptName" ),
	FIELD( _field_string_id, "endScriptName" ),
	FIELD( _field_short_integer, "startScript~" ),
	FIELD( _field_short_integer, "endScript~" ),
	FIELD( _field_short_integer, "firstAction" ),
	FIELD( _field_short_integer, "actionCount" ),
	FIELD( _field_short_integer, "firstSubAction" ),
	FIELD( _field_short_integer, "subActionCount" ),
	FIELD( _field_tag_reference, "additionalAnimations" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(PuppetActionHeaderBlock, MAX_ACTIONS_PER_SHOW)
{
	FIELD( _field_string_id, "name" ),
	FIELD( _field_long_integer, "id" ),
	FIELD( _field_long_integer, "blendIn" ),
	FIELD( _field_long_integer, "length" ),
	FIELD( _field_long_integer, "comment" ),
	FIELD( _field_char_enum, "blendType" ),
	FIELD( _field_char_enum, "type" ),
	FIELD( _field_short_integer, "dataIndex" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(PuppetSubActionHeaderBlock, MAX_SUB_ACTIONS_PER_SHOW)
{
	FIELD( _field_char_enum, "type" ),
	FIELD( _field_char_enum, "startType" ),
	FIELD( _field_char_enum, "endType" ),
	FIELD( _field_pad, "pad1", 1 ),
	FIELD( _field_long_integer, "startAction" ),
	FIELD( _field_long_integer, "startOffset" ),
	FIELD( _field_string_id, "startConditionScriptName" ),
	FIELD( _field_string_id, "endConditionScriptName" ),
	FIELD( _field_short_integer, "startCondition~" ),
	FIELD( _field_short_integer, "endCondition~" ),
	FIELD( _field_long_integer, "endAction" ),
	FIELD( _field_long_integer, "endOffset" ),
	FIELD( _field_long_integer, "comment" ),
	FIELD( _field_short_integer, "dataIndex" ),
	FIELD( _field_pad, "pad2", 2 ),
	FIELD( _field_terminator )
};

TAG_BLOCK(PuppetAnimationBlock, MAX_ACTIONS_PER_SHOW)
{
	FIELD( _field_string_id, "name" ),
	FIELD( _field_struct, "position" ),
	FIELD( _field_byte_flags, "flags" ),
	FIELD( _field_char_enum, "posType" ),
	FIELD( _field_pad, "pad", 2 ),
	FIELD( _field_long_integer, "startFrame" ),
	FIELD( _field_long_integer, "endFrame" ),
	FIELD( _field_long_integer, "repeatCount" ),
	FIELD( _field_real, "scale" ),
	FIELD( _field_string_id, "conditionScriptName" ),
	FIELD( _field_long_integer, "condition~" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(PuppetPathBlock, MAX_ACTIONS_PER_SHOW)
{
	FIELD( _field_real, "throttle" ),
	FIELD( _field_block, "points", &PuppetPathPointBlock_block ),
	FIELD( _field_terminator )
};

TAG_BLOCK(PuppetPathPointBlock, MAX_POINTS_PER_PATH)
{
	FIELD( _field_char_enum, "type" ),
	FIELD( _field_byte_flags, "flags" ),
	FIELD( _field_char_enum, "indexType~" ),
	FIELD( _field_pad, "pad", 1 ),
	FIELD( _field_string_id, "objectName" ),
	FIELD( _field_long_integer, "index~" ),
	FIELD( _field_string_id, "marker" ),
	FIELD( _field_real_point_3d, "pos" ),
	FIELD( _field_real_euler_angles_3d, "rot" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(PuppetPointBlock, MAX_SUB_ACTIONS_PER_SHOW)
{
	FIELD( _field_struct, "point" ),
	FIELD( _field_tag_reference, "asset" ),
	FIELD( _field_byte_flags, "flags" ),
	FIELD( _field_pad, "pad", 3 ),
	FIELD( _field_terminator )
};

TAG_BLOCK(PuppetBranchBlock, MAX_SUB_ACTIONS_PER_SHOW)
{
	FIELD( _field_block, "elements", &PuppetSubActionBranchElementBlock_block ),
	FIELD( _field_terminator )
};

TAG_BLOCK(PuppetSubActionBranchElementBlock, MAX_BRANCHES_PER_SUB_ACTION)
{
	FIELD( _field_long_integer, "targetAction" ),
	FIELD( _field_string_id, "conditionScriptName" ),
	FIELD( _field_long_integer, "condition~" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(PuppetScriptBlock, MAX_SUB_ACTIONS_PER_SHOW)
{
	FIELD( _field_string_id, "scriptName" ),
	FIELD( _field_long_integer, "script~" ),
	FIELD( _field_terminator )
};

TAG_BLOCK(CommentsBlock, 65536)
{
	FIELD( _field_char_integer, "char" ),
	FIELD( _field_terminator )
};

} // namespace blofeld

