C Utils
---

A random collections of C utils I end up copy-pasting over and over in every 
project.

## Add it to your project

```sh
curl -O https://raw.githubusercontent.com/shikaan/c-utils/refs/heads/main/lib/${FILE}

# example 
# curl -O https://raw.githubusercontent.com/shikaan/c-utils/refs/heads/main/lib/debug.h
```

## Development

Generate documentation for `file.h`

```sh
python3 scripts/docs.py file.h # generates docs/file.h.md
```
