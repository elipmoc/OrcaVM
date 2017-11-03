.func local2

.stack_size 1

store_i 0

load_i 0

itos

push_s " : result\n"

add_s

return

.func_end

.func local

.stack_size 2

store_i 0
store_i 1

load_i 0
load_i 1

add_i

invoke local2

return

.func_end

.entry_point

push_i 2
push_i 3

invoke local

output
