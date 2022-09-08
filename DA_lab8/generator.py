import random

def main():
    symbols = 1000000
    file_name = "test.txt"
    res = ""
    with open(file_name, "w") as f:
        res += str(symbols) + "\n"
        for _ in range(symbols):
            res += chr(random.randint(49, 51)) + " "
        f.write(res)

if __name__ == "__main__":
    main()