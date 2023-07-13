import math

for i in range(0, 360):

    print(f"[+]: Value of cosinus {i}: {math.cos(i)}")
    #print(f"[+]: Value of sinus {i}: {math.sin(i)}")

    with open("sin_cos_values.txt", "a") as file:
        file.write(f"{math.cos(i)}\n")