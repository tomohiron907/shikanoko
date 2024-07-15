# マッピング用の辞書
command_map = {
    '>': 'こし',
    '<': 'たん',
    '+': 'しか',
    '-': 'ぬん',
    '.': 'のこ',
    ',': 'なら',
    '[': 'つの',
    ']': 'のつ'
}

def convert_to_hiragana(brainfuck_code):
    result = ''
    for char in brainfuck_code:
        if char in command_map:
            result += command_map[char]
    return result

# 例としてBrainfuckコードを入力
brainfuck_code = "+++++++++++[>++++++>++++++>+++>++++++++<<<<-]>+++>++++++.<.>++++..+++.>-.>-.<<.>>-----.<<---.<-.>>+."

hiragana_code = convert_to_hiragana(brainfuck_code)
print(hiragana_code)
