import subprocess
import shlex
methods = ["bubble","selection","radix","quick","merge"]
sizes = [250000,500000,750000,1000000]

folder = "dump/"


I1s = ["65536,16,64","65536,16,64","65536,16,64"]
D1s  = ["32768,4,64","65536,8,64","32768,8,32"]
LLs = ["4194304,16,64","4194304,16,64","4194304,16,64"]
prefixes = ["reduce_assoc","increase_cap","reduce_block_size"]

for i,prefix in enumerate(prefixes):
    for method in methods:
        for size in sizes:
            program = f"./main.o {method} {size}  disable_output"
            f = open(f"{folder}{method}_{size}_{prefix}_summary.txt","w")    
            subprocess.Popen(["valgrind","--tool=cachegrind",f"--I1={I1s[i]}",f"--D1={D1s[i]}",f"--LL={LLs[i]}",f"--cachegrind-out-file={folder}{method}_{size}_{prefix}.txt","./main.o",method,str(size),"disable_output"],stdout=f,stderr=f)
