"""
Generates a gzip hex dump of index.html and 
saves as C byte array in webpage.h for
serving by app_httpd.cpp static esp_err_t index_handler(httpd_req_t *req)
"""

from chepy import Chepy

# Open HTML file and read contents into variable
with open('support/index.html') as html:
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
    out.write(f"#include <stdint.h>\n#define WEBPAGE_LENGTH {len(result) // 2}\n")
    out.write("const uint8_t webpage[] = {\n" + array + "\n};")
    out.close()