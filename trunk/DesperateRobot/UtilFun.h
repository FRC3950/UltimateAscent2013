#ifndef UTIL_FUN_H
#define UTIL_FUN_H

/*
 * if the value is betwen the min and the max it sets it to 0 
 * otherwize it returns the original value
 */
inline float ZeroIfInRangeInclusive(float value, float min, float max) {
	if ((value >= min) && (value <= max))
	{
		return 0.0;
	}
	
	return value;
}

inline bool InRangeInclusive(float value, float min, float max) {
	return((value >= min) && (value <= max));
		
}

#endif // UTIL_FUN_H
