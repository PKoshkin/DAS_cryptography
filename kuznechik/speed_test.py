import subprocess
import numpy as np
times = []
for _ in range(1000):
    times.append(float(subprocess.check_output("./kuznechik", shell=True).decode("utf-8")[:-1].split(' ')[0]))

print(np.min(times), np.mean(times), np.max(times))
