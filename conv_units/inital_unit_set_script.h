
#ifndef INITIAL_UNIT_SET_SCRIPT	

#define INITIAL_UNIT_SET_SCRIPT															\
		ADD_SI_UNIT "degree K" END_ADD													\
		ADD_SPECIAL_UNIT "degree C", convertDegreeC_ToSI, convertDegreeC_FromSI END_ADD \
		ADD_SPECIAL_UNIT "degree F", convertDegreeF_ToSI, convertDegreeF_FromSI END_ADD \
		ADD_SI_UNIT "s" END_ADD															\
		ADD_SIMPLE_UNIT "min", 60 END_ADD												\
		ADD_SIMPLE_UNIT "h", 3600 END_ADD	
		
#endif