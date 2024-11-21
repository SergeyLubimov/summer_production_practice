
CREATE FUNCTION init_conv_units()
RETURNS void
AS 'MODULE_PATHNAME'
LANGUAGE C;

SELECT init_conv_units();

CREATE FUNCTION create_convertors_pool(integer)
RETURNS boolean
AS 'MODULE_PATHNAME'
LANGUAGE C;

CREATE FUNCTION configure_converter(text, text, integer)
RETURNS text
AS 'MODULE_PATHNAME'
LANGUAGE C;

CREATE FUNCTION convert_unit(double precision, integer)
RETURNS double precision
AS 'MODULE_PATHNAME'
LANGUAGE C;