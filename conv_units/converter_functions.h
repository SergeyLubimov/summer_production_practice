
#ifndef __CONVERTER_FUNCTIONS_H__
#define __CONVERTER_FUNCTIONS_H__

typedef double (*function_converter) (double);

extern double convertDegreeC_ToSI(double value);

extern double convertDegreeC_FromSI(double value);

extern double convertDegreeF_ToSI(double value);

extern double convertDegreeF_FromSI(double value);

#endif