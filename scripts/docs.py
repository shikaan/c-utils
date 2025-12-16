## Copilot generated and just mildly reviewed. Don't take seriously.

import os
import sys

if len(sys.argv) < 2:
    print("Usage: python3 docs.py <header-file>")
    sys.exit(1)

header_file = sys.argv[1]
md_file = "docs/" + os.path.basename(header_file) + ".md"

with open(header_file, "r") as f:
    lines = f.readlines()

# Extract doc block before ___HEADER_END___
doc_block = []
for line in lines:
    if "___HEADER_END___" in line:
        break
    doc_block.append(line.rstrip("\n")[3:])

# Find all JSDoc-style docblocks and their associated function/macro
api_docs = []
i = 0
while i < len(lines):
    if lines[i].strip().startswith("/**"):
        # Parse docblock
        desc = []
        name = ""
        example = []
        in_example = False
        i += 1
        while i < len(lines) and not lines[i].strip().startswith("*/"):
            l = lines[i].strip()
            if "@name" in l:
                name = l.split("@name", 1)[1].strip()
            elif "@example" in l:
                in_example = True
            elif in_example:
                if l.startswith("*"):
                    l = l[1:].lstrip()
                if l == "":
                    pass
                else:
                    example.append(l)
            elif l.startswith("*"):
                l = l[1:].lstrip()
                if l and not l.startswith("@"):
                    desc.append(l)
            i += 1
        # Find the next function/macro signature
        sig = ""
        j = i + 1
        while j < len(lines):
            sig_line = lines[j].strip()
            if sig_line and (
                sig_line.startswith("void ")
                or sig_line.startswith("int ")
                or sig_line.startswith("#define ")
            ):
                sig = sig_line
                break
            j += 1
        api_docs.append(
            {
                "name": name,
                "desc": " ".join(desc),
                "example": "\n".join(example),
                "sig": sig,
            }
        )
    i += 1

with open(md_file, "w") as out:
    for l in doc_block:
        out.write(l + "\n")

    if api_docs:
        out.write("\n## API Docs\n\n")

    for method in api_docs:
        out.write(
            f"### {method['name']}\n\n{method['desc']}\n\n```c\n{method['example']}\n```\n\n\n"
        )
