.entry_point

def $i 100

push_i 5
push_i 3
g_astore_i $i

push_i 3
g_aload_i $i

itos

push_s "\n"

add_s

output
