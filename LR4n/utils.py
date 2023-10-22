def split_string_into_blocks(input_string):
    current_block: str = ''
    blocks: list = list()

    for char in input_string:
        char_binary = bin(int(char, 16))[2:].zfill(16)
        current_block += char_binary

    block = []

    for i in range(len(current_block)):
        if len(block) == 4:
            blocks.append(block)
            block = []
        block.append(int(current_block[i]))
    blocks.append(block)

    return blocks


def blocks_into_string(blocks):
    proto_string = ''
    string = ''
    for i in range(len(blocks)):
        for j in range(4):
            proto_string += str(int(blocks[i][j]))

    for i in range(0, len(proto_string), 16):
        delta_string = proto_string[i:i+16]
        string += chr(int(hex(int(delta_string, 2)), 16))

    return string


def read_file(file_name: str) -> str:
    with open(file_name, 'r', encoding='utf8') as file:
        text = file.read()
        return text


def write_file(file_name: str, data: str) -> None:
    with open(file_name, 'w', encoding='utf8') as file:
        file.write(data)