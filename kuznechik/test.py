from collections import namedtuple
from kuznechik import encrypt

Test = namedtuple('Test', ['function', 'arguments', 'output'])

def test(tests):
    for test in tests:
        result = test.function(*test.arguments)
        if result == test.output:
            print('OK')
        else:
            print(result)
            print(test.output)

encrypt_tests = [
    Test(
        function=encrypt,
        arguments=[
            '8899aabbccddeeff0011223344556677fedcba98765432100123456789abcdef',
            '1122334455667700ffeeddccbbaa9988'
        ],
        output='7f679d90bebc24305a468d42b9d4edcd'
    )
]

test(encrypt_tests)
