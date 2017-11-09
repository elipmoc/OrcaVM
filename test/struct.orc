.struct test2

def $i 1
def $s 1

.struct_end

.struct test

def $i 1
def $str <test2>

.struct_end

def $st <test>

push_i 2
g_store_i $st.i

push_i 3
g_store_i $st.str.i
