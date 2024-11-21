
#include "converter_functions.h"

double convertDegreeC_ToSI(double value)
{
	return value + 273.15; 
}

double convertDegreeC_FromSI(double value)
{
	return value - 273.15; 
}

double convertDegreeF_ToSI(double value)
{
	return (5. / 9) * (value - 32) + 273.15;
}

double convertDegreeF_FromSI(double value)
{
	return (9. / 5) * (value - 273.15) + 32;
}