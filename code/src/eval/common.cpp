#include <eval/common.hpp>
#include <cstdio>

namespace eval {

int 
report_error(int error_num, char const * error_str) noexcept
{
	fprintf(stderr, "ERROR[%d]: %s\n", error_num, error_str);
	return error_num;
}

void 
report_value(value_t const & value) noexcept
{
	printf("%.15lf\n", value);
}


} // namespace eval
