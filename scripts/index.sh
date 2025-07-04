#!/bin/sh
# Generate docs/index.md with links to all documented libraries in docs/*.md

cat <<EOF > docs/index.md
C Utils
---

A collections of utilities for C projects.

## Utilities

EOF

for file in docs/*.md; do
  # Skip index.md itself
  [ "$file" = "docs/index.md" ] && continue
  # Extract the base name with extension
  name=$(basename "$file" .md)
  # Output a GitHub Pages link (assuming standard repo URL)
  echo "* [${name}](https://shikaan.github.io/c-utils/${name})" >> docs/index.md
done
