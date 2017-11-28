import subprocess
import numpy as np

def make_random_input(length):
    result = ""
    for i in range(length):
        result += str(np.random.randint(0, 2))
    return result

speeds = []
for i in range(100):
    mb_time = 0
    for _ in range(64):
        mb_time += float(subprocess.check_output("./kuznechik encrypt_time {} {}".format(
            make_random_input(256),
            make_random_input(128)
        ), shell=True).decode("utf-8")[:-1])
    speeds.append(1 / mb_time)

print(np.min(speeds), np.mean(speeds), np.max(speeds))
