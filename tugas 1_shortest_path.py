import heapq

def a_star(graph, start, dest, heuristic):
    distances = {vertex: float('inf') for vertex in graph} # V time / V space
    distances[start] = 0

    parent = {vertex: None for vertex in graph} # store path => V time / V space

    visited = set()

    pq = [( 0 + heuristic[start], 0 ,  start)] # E space

    while pq: # ElogE time
        curr_f, curr_dist, curr_vert = heapq.heappop(pq) #logE time


        if curr_vert not in visited:
            visited.add(curr_vert)

            for nbor, weight in graph[curr_vert].items():
                distance = curr_dist + weight  # distance from start (g)
                f_distance = distance + heuristic[nbor] # f = g + h

                # Only process new vert if it's f_distance is lower
                if f_distance < distances[nbor]:
                    distances[nbor] = f_distance
                    parent[nbor] = curr_vert


                    if nbor == dest:
                        # we found a path based on heuristic
                        return distances, parent

                    heapq.heappush(pq, (f_distance, distance, nbor)) #logE time

    return distances, parent



def generate_path_from_parents(parent, start, dest):
    path = []
    curr = dest
    while curr:
        path.append(curr)
        curr = parent[curr]

    return '->'.join(path[::-1])

graph = {
    'A': {'B':5, 'C':5},
    'B': {'A':5, 'C':4, 'D':3  },
    'C': {'A':5, 'B':4, 'D':7, 'E':7, 'H':8},
    'D': {'B':3, 'C':7, 'H':11, 'K':16, 'L':13, 'M':14},
    'E': {'C':7, 'F':4, 'H':5},
    'F': {'E':4, 'G':9},
    'G': {'F':9, 'N':12},
    'H': {'E':5, 'C':8, 'D':11, 'I':3 },
    'I': {'H':3, 'J':4},
    'J': {'I':4, 'N':3},
    'K': {'D':16, 'L':5, 'P':4, 'N':7},
    'L': {'D':13, 'M':9, 'O':4, 'K':5},
    'M': {'D':14, 'L':9, 'O':5},
    'N': {'G':12, 'J':3, 'P':7},
    'O': {'M':5, 'L':4},
    'P': {'K':4, 'J':8, 'N':7},
}


heuristic = {
    'A': 16,
    'B': 17,
    'C': 13,
    'D': 16,
    'E': 16,
    'F': 20,
    'G': 17,
    'H': 11,
    'I': 10,
    'J': 8,
    'K': 4,
    'L': 7,
    'M': 10,
    'N': 7,
    'O': 5,
    'P': 0
}

start = 'A'
dest= 'O'
distances,parent = a_star(graph, start, dest, heuristic)
print('distances => ', distances)
print('\n')
print('parent -> ', parent)
print('\n')
print('optimal path -> ', generate_path_from_parents(parent,start,dest))
