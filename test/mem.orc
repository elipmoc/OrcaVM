def $i 1
def $n 1

.entry_point

g_load_a $i
g_store_a $n

push_i 3
g_store_i $n

g_load_i $i
itos
push_s "\n"
add_s
output
