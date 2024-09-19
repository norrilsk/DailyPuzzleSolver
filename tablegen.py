import numpy as np;
def get_state( mat):
    B= mat
    A = np.zeros((8, 8), dtype=int)
    A[0:0+B.shape[0], 0:0+B.shape[1]] = B
    A_r = A.reshape(1,64)
    while (A_r[0][0] == 0):
        A_r = np.roll(A_r,-1)
    st =''.join(map(str,A_r))[1:-1].replace(' ','').replace('\n','')
    return st
def gen_tables(matrix):
    mset = {}
    mset[get_state(matrix)] = 1;
    for i in range(4):
        matrix = np.rot90(matrix)
        mset[get_state(matrix)] = 1
    matrix = np.fliplr(matrix)
    for i in range(4):
        matrix = np.rot90(matrix)
        mset[get_state(matrix)] = 1
    for key in mset:
        print(f"states.emplace_back(0b{key});")

print("Rect")
matrix = np.array([[1,1], 
                   [1,1], 
                   [1,1]])
gen_tables(matrix)

print("RectP")
matrix = np.array([[0,1], 
                   [1,1], 
                   [1,1]])
gen_tables(matrix)

print("Chair")
matrix = np.array([[1,0], 
                   [1,0], 
                   [1,1],
                   [0,1]])
gen_tables(matrix)

print("L")
matrix = np.array([[1,0], 
                   [1,0], 
                   [1,0],
                   [1,1]])
gen_tables(matrix)

print("Pistol")
matrix = np.array([[1,0], 
                   [1,1], 
                   [1,0],
                   [1,0]])
gen_tables(matrix)

print("Cap")
matrix = np.array([[1,1], 
                   [1,0], 
                   [1,1]])
gen_tables(matrix)

print("ZigZag")
matrix = np.array([[1,1,0], 
                   [0,1,0], 
                   [0,1,1]])
gen_tables(matrix)

print("Corner")
matrix = np.array([[1,0,0], 
                   [1,0,0], 
                   [1,1,1]])
gen_tables(matrix)
