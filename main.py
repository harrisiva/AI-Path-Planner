with open("input.txt", "r") as file: lines = [line.replace('\n','') for line in file.readlines()]
dimensions = [int(item) for item in lines[0].split(' ')] # Size of matrix as row,col
N = int(lines[1]) # Number of robots (moveable pieces)

# Get initial positions of N robots and store them in a dictionary (O(1) look up)
initial_positions = {}
for i in range(N,N+N,1):
    initial_positions[i-1] = [int(item) for item in lines[i].split(' ')]

R = [int(item) for item in lines[2+N].split(' ')] # Rendezvous location

# Set matrix
initial_state = []
for i in range(3+N,len(lines),1): initial_state.append([int(item) for item in lines[i]])
print(initial_state)