height = 0

while (True):
    try:
        height = int(input("Height: "))
        if (height < 1 or height > 8):
            continue
        
    except ValueError:
        continue
        
    else:
        break

for y in range(height):
    for x in range(height):
        if (x < height - 1 - y):
            print(" ", end='')

        else:
            print("#", end='')

        if (x == height - 1):
            print("  ", end='')
            for x2 in range(y + 1):
                print("#", end='')

    print("\n", end='')