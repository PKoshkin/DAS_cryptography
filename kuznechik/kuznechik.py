import subprocess

array_16 = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f']

array_2 = [
    '0000', '0001', '0010', '0011',
    '0100', '0101', '0110', '0111',
    '1000', '1001', '1010', '1011',
    '1100', '1101', '1110', '1111'
]

def from_16_to_2(string):
    map_dict = {
        value_16: value_2
        for value_2, value_16 in zip(array_2, array_16)
    }
    result = ''
    for char in string:
        result += map_dict[char]
    return result

def from_2_to_16(string):
    map_dict = {
        value_2: value_16
        for value_2, value_16 in zip(array_2, array_16)
    }
    result = ''
    for i in range(0, len(string), 4):
        result += map_dict[string[i:(i + 4)]]
    return result

def from_array_to_2(array):
    result = ''
    for value in reversed(array):
        result += '0' * (8 - len(bin(value)[2:])) + bin(value)[2:]
    return result

def from_2_to_array(string):
    result = []
    for i in range(len(string) - 8, -1, -8):
        result.append(int(string[i:(i + 8)], 2))
    return result

def from_array_to_16(array):
    return from_2_to_16(from_array_to_2(array))
    
def from_16_to_array(string):
    return from_2_to_array(from_16_to_2(string))

def encrypt(key, block):
    return from_2_to_16(
        subprocess.check_output("./kuznechik encrypt {} {}".format(
            from_16_to_2(key), from_16_to_2(block)
        ), shell=True).decode("utf-8")[:-1]
    )

def decrypt(key, block):
    return from_2_to_16(
        subprocess.check_output("./kuznechik decrypt {} {}".format(
            from_16_to_2(key), from_16_to_2(block)
        ), shell=True).decode("utf-8")[:-1]
    )
