.func test2

push_s "test2\n"
output

.func_end

.func test

.stack_size 0

push_s "test\n"
output

invoke test2

.func_end

.entry_point

invoke test

push_s "end_test\n"
output
