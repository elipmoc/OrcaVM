def $x 1
def $y 1

.entry_point

push_i 3
g_store_i $x

push_i 5
g_store_i $y

g_load_i $x

g_load_i $y

add_i

itos
push_s "\n"
add_s

output
