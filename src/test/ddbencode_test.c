#include "test/ddbencode_test_string.h"
#include "test/ddbencode_test_integer.h"
#include "test/ddbencode_test_list.h"
#include "test/ddbencode_test_dictionary.h"

int main(void)
{
	BETestString();
	BETestInteger();
	BETestList();
	BETestDictionary();

	return 0;
}
