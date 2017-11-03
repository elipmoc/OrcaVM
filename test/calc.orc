.func add

.stack_size 2

store_i 1
store_i 0

load_i 0
load_i 1

add_i

return

.func_end

.entry_point

input
stoi
input
stoi

invoke add

itos
push_s "\n"
add_s

output
