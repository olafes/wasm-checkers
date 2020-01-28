top = [0, 1, 2, 3, 4]
left = [0, 5, 15, 25, 35, 45]
right = [4, 14, 24, 34, 44]
bottom = [45, 46, 47, 48, 49]

def getRightTop(x):
    indices = []
    if (x in top) or (x in right):
        return indices
    while not ((x in top) or (x in right)):
        indices.append(x)
        row = x//5
        if row%2:
            x -= 5
        else:
            x -= 4
    indices.pop(0)
    return indices

def getLeftTop(x):
    indices = []
    if (x in top) or (x in left):
        return indices
    while not ((x in top) or (x in left)):
        indices.append(x)
        row = x//5
        if row%2:
            x -= 6
        else:
            x -= 5
    indices.pop(0)
    return indices

def getLeftBottom(x):
    indices = []
    if (x in bottom) or (x in left):
        return indices
    while not ((x in bottom) or (x in left)):
        indices.append(x)
        row = x//5
        if row%2:
            x += 4
        else:
            x += 5
    indices.pop(0)
    return indices

def getRightBottom(x):
    indices = []
    if (x in bottom) or (x in right):
        return indices
    while not ((x in bottom) or (x in right)):
        indices.append(x)
        row = x//5
        if row%2:
            x += 5
        else:
            x += 6
    indices.pop(0)
    return indices

def indicesToBits(indices):
    x = 0
    for index in indices:
        x += 2**(index)
    return x

startpos = {
    # "whiteMen": [x+30 for x in range(20)],
    "whiteMen": [12, 13, 16],
    "whiteKings": [],
    # "blackMen": [x for x in range(20)],
    "blackMen": [6, 7, 9, 21, 32],
    "blackKings": []
}

for name, bitboard in startpos.items():
    x = indicesToBits(bitboard)
    x = f"{x:#066b}".strip()
    print(f"u64 {name} = {x};")

# n = 14
# i0 = getRightTop(n)
# print(i0)
# x0 = indicesToBits(i0)
# i1 = getLeftTop(n)
# print(i1)
# x1 = indicesToBits(i1)
# i2 = getLeftBottom(n)
# print(i2)
# x2 = indicesToBits(i2)
# i3 = getRightBottom(n)
# print(i3)
# x3 = indicesToBits(i3)
#

# print(f"{x2:#02x}")
# data = '{'
# for i in range(50):
#     x = 2**(i)
#     x_0 = indicesToBits(getRightTop(i))
#     x_1 = indicesToBits(getLeftTop(i))
#     x_2 = indicesToBits(getLeftBottom(i))
#     x_3 = indicesToBits(getRightBottom(i))
#     data += "\n{"
#     data += f"{x:#02x}"
#     data += ", {"
#     data += f"{x_0:#66b},".strip()
#     # data += "\n"
#     data += f"{x_1:#66b},".strip()
#     # data += "\n"
#     data += f"{x_2:#66b},".strip()
#     # data += "\n"
#     data += f"{x_3:#66b}".strip()
#     data += "}},"
#
# data = data[:-1] + "}"
#
# with open('magic.txt', 'w') as file:
#     file.write(data)

# print(f"costam costam {x0:#066b}")
# print(f"costam costam {x1:#066b}")
# print(f"costam costam {x2:#066b}")
# print(f"costam costam {x3:#066b}")
