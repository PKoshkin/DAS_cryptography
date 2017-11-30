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

def L(block):
    return from_2_to_16(
        subprocess.check_output("./kuznechik L {}".format(
            from_16_to_2(block)
        ), shell=True).decode("utf-8")[:-1]
    )

def S(block):
    return from_2_to_16(
        subprocess.check_output("./kuznechik S {}".format(
            from_16_to_2(block)
        ), shell=True).decode("utf-8")[:-1]
    )

def X(key, block):
    return from_2_to_16(
        subprocess.check_output("./kuznechik X {} {}".format(
            from_16_to_2(key), from_16_to_2(block)
        ), shell=True).decode("utf-8")[:-1]
    )

def LSX(key, block):
    return from_2_to_16(
        subprocess.check_output("./kuznechik LSX {} {}".format(
            from_16_to_2(key), from_16_to_2(block)
        ), shell=True).decode("utf-8")[:-1]
    )

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
