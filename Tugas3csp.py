# Tentukan peta dan matrix adjacency-nya
map = {
    'SA':['WA', 'NT', 'Q', 'NSW', 'V'], 
    'WA':['SA', 'NT'],
    'NT':['WA', 'SA', 'Q'], 
    'NSW': ['Q', 'V', 'SA'],
    'Q': ['NT', 'SA', 'NSW'],
    'V': ['SA', 'NSW'],
    'T':[]
}

# Menentukan warna dan jumlah warna yang tersedia
colors = ['red', 'green', 'blue', 'yellow']
num_colors = len(colors)

# Menetapkan fungsi untuk memeriksa apakah pewarnaan valid
def is_valid_coloring(state_coloring):
    for state in map:
        for adjacent_state in map[state]:
            if state_coloring[state] == state_coloring[adjacent_state]:
                return False
    return True

# Tentukan fungsi rekursif untuk mencari pewarnaan yang valid
def search_colorings(state_coloring):
    # Jika semua bagian diwarnai, periksa apakah ini adalah pewarnaan yang valid
    if len(state_coloring) == len(map):
        if is_valid_coloring(state_coloring):
            return state_coloring
        else:
            return None
    # Jika tidak, cobalah mewarnai status berikutnya yang belum diwarnai dengan setiap warna yang tersedia
    else:
        next_state = [state for state in map if state not in state_coloring][0]
        for color in colors:
            new_coloring = dict(state_coloring)
            new_coloring[next_state] = color
            result = search_colorings(new_coloring)
            if result is not None:
                return result
        return None

# Cari pewarnaan yang valid dimulai dengan pewarnaan kosong
coloring = search_colorings({})
if coloring is not None:
    print(coloring)
else:
    print("No valid coloring found.")
