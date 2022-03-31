from chepy import Chepy

# Open HTML file and read contents into variable
with open('Support/index.html') as html:
    htmlContents = html.read()

# Generate the array for the file
c = Chepy(htmlContents).gzip_compress().binary_to_hex()
result = c.o.decode('ascii')
array = ""
for a, b in zip(result[0::2], result[1::2]):
    array += f"0x{a}{b}, "
array = array[:-2:]

# Start writing the file contents
with open('webpage.h', 'w') as out:

    out.write(f"#define WEBPAGE_LENGTH {len(result) // 2}\n")
    out.write("const uint8_t webpage[] = {\n" + array + "\n};")
    out.close()