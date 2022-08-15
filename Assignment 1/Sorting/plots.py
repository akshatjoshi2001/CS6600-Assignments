import matplotlib.pyplot as plt
import os
import re

methods = ["bubble","selection","radix","quick","merge"]
sizes = [250000,500000,750000,1000000]
prefixes = ["","reduce_assoc","increase_cap","reduce_block_size"]
labels = ["Default","Reduced \nAssociativity","Increased\nCapacity","Reduced\nBlock Size"]

dump_folder = "dump/"
plot_folder = "plots/"

for size in sizes:
    data = {}
    for method in methods:    
        file = f"{dump_folder}{method}_{size}"
        if not os.path.isfile(f"{file}.txt"):
            continue
        lines = []
        with open(f"{file}_summary.txt", "r") as f:
            lines = f.readlines()
        
        for line in lines[13:18]:
            data_pair = line.strip().split(":")
            key = re.sub(r'\=\=.*\=\=','',data_pair[0].strip())
            value = data_pair[1].split("(")[0].strip()
            value = value.replace(",","")
            value = value.strip("%")
            if key not in data:
                data[key] = {}
            data[key][method]  = float(value)
        
    
    for key in data:
        methods = list(data[key].keys())
        vals = list(data[key].values())

        print(methods)
        print(vals)

        plt.figure()
        plt.title(f"{key} comparison across different sorting algorithms \n (array size {size})")
        if "miss rate" in key:
            plt.ylabel("Miss Rate (%)")
        plt.bar(methods,vals,color ='maroon',width = 0.4)
        key2 = key.replace("miss rate","mr")
        key = key2.strip()
        key2 = key2.replace(" ","_")
        plotfilename = f"{plot_folder}/{key2}_{size}_default.png"
        plt.savefig(plotfilename.strip())
        

size = 1000000
    
for method in methods:
    vals = []    
    for i,prefix in enumerate(prefixes):
        if(prefix != ""):
            file = f"{dump_folder}{method}_{size}_{prefix}"
        else:
            file = f"{dump_folder}{method}_{size}"
        if not os.path.isfile(f"{file}.txt"):
            continue
        lines = []
        with open(f"{file}_summary.txt", "r") as f:
            lines = f.readlines()
        
        line = lines[16]
        data_pair = line.strip().split(":")
        key = re.sub(r'\=\=.*\=\=','',data_pair[0].strip())
        
        value = data_pair[1].split("(")[0].strip()
        value = value.replace(",","")
        value = value.strip("%")
        vals.append(float(value))
    plt.figure()
    plt.title(f"Miss Rate comparison for {method} sort \n for size {size}  across different cache configurations")
    plt.ylabel("Miss Rate (%)")
    print(labels)
    print(vals)
    if(len(vals) != len(labels)):
        continue
    plt.bar(labels,vals,color ='blue',width = 0.4)
    plotfilename = f"{plot_folder}/cache_compare_{method}_{size}.png"
    plt.savefig(plotfilename.strip())