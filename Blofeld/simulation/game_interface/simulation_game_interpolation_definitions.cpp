#include <blofeld-private-pch.h>

namespace blofeld
{

TAG_GROUP(simulation_interpolation, SIMULATION_INTERPOLATION_TAG)
{
	FIELD( _field_explanation, "SIMULATION INTERPOLATION" ),
	FIELD( _field_custom, "High level settings" ),
	FIELD( _field_real, "position_client_ignore_tolerance:WU#How much rope clients have WRT their controlled object of this type. They are free to ignore host updates within this tolerance." ),
	FIELD( _field_real, "angular_speed_threshold_for_temporarily_ignoring_rotation_updates:degrees per second#If angular speed exceeds this threshold, we will ignore rotational updates (because it\'s spinning so fast that we can\'t possibly do a good job w/ any kind of interpolation - instead, just wait for it to settle down a bit).  Note that if a warp threshold is exceeded, rotation will be warped regardless of the value of this parameter." ),
	FIELD( _field_custom, "Warp Thresholds" ),
	FIELD( _field_explanation, "WARP THRESHOLDS" ),
	FIELD( _field_real, "position_warp_threshold:WU#Threshold of position error beyond which we will warp instead of interpolating." ),
	FIELD( _field_real, "position_warp_threshold_xy:WU#Separated for bipeds, for whom z discrepancies are more permissible because of jumping. If you don\'t want a special lower XY threshold, just set this to a very high number." ),
	FIELD( _field_real, "rotation_warp_threshold:degrees#Threshold of rotation error beyond which we will warp instead of interpolating.  Set this to 180.0 if you don\'t want to warp based on rotational deviation (may be important for objects that often spin very fast, e.g. grenades or garbage bits)." ),
	FIELD( _field_custom ),
	FIELD( _field_custom ),
	FIELD( _field_custom, "Position while controlled" ),
	FIELD( _field_struct, "position_while_controlled#All speeds in here are WU/s" ),
	FIELD( _field_custom ),
	FIELD( _field_custom, "Rotation while controlled" ),
	FIELD( _field_struct, "rotation_while_controlled#All speeds in here are degrees/s" ),
	FIELD( _field_custom ),
	FIELD( _field_custom, "Position while not controlled" ),
	FIELD( _field_struct, "position_while_uncontrolled#All speeds in here are WU/s" ),
	FIELD( _field_custom ),
	FIELD( _field_custom, "Rotation while not controlled" ),
	FIELD( _field_struct, "rotation_while_uncontrolled#All speeds in here are degrees/s" ),
	FIELD( _field_custom ),
	FIELD( _field_terminator )
};

} // namespace blofeld

