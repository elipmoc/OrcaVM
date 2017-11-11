def $base 1

.func test

.stack_size 1

def $i 1

g_load_a $base
store_a $i
push_i 334
store_i $i

.func_end

.entry_point

invoke test
