# arducky
Parser that reads duckyscript from a file and generates an Arduino sketch

## How to use:
Execute the file with `python main.py` or `chmod +x main.py` and then `./main.py`

You can change the input or output file by adding args (input: -i), (output: -o).
For example: [executable_name] -i custom_file.txt -o test_project.ino

## Differences with other interpreters:
- It creates an Arduino file directly, not a text you have to copy-paste into a new file
- You can write Arduino code directly, for example a for loop and it won't get parsed
- More commands:
    - `LOOP` will put all following code in `void loop(){}` so it keeps repeating forever
    - `MOUSE` can move the mouse or click

## Planned features
- Support for multiple payloads to select with the dipswitch

Thanks to [Seytonic](https://www.youtube.com/seytonic) and [Dckuino.js](https://github.com/Thecakeisgit/Dckuino.js)
