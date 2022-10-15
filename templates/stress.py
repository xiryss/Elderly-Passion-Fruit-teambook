import os

SOL1 = "good"
SOL2 = "bad"

GEN1 = "gen"

def main():
    os.system("make " + SOL1 + " && make " + SOL2 + " && make " + GEN1)
    for te in range(10**6):
        os.system("./" + GEN1 + " > in")

        a1 = os.system("./" + SOL1 + " < in > out")
        if a1 != 0:
            print("RE", te, SOL1)
            print("in = ")
            print(open("in", "r").read())
            return
        out1 = open("out", "r").read()
        
        a2 = os.system("./" + SOL2 + " < in > out")
        if a2 != 0:
            print("RE", te, SOL2)
            print("in = ")
            print(open("in", "r").read())
            return
        out2 = open("out", "r").read()

        if out1 != out2:
            print("WA", te)
            print("in = ")
            print(open("in", "r").read())
            print("out", SOL1)
            print(out1)
            print("out", SOL2)
            print(out2)
            return

        print("OK", te)
main()