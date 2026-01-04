#!/bin/bash

### 1️⃣ Renomear arquivos *_bonus.c e reverter include
find . -type f -name "*_bonus.c" | while read -r f; do
    dir=$(dirname "$f")
    base=$(basename "$f" _bonus.c)
    new="$dir/${base}.c"

    mv -- "$f" "$new"
    echo "Arquivo renomeado: $f -> $new"

    sed -i 's/#include "minirt_bonus.h"/#include "minirt.h"/g' "$new"
    echo "Include revertido em: $new"
done

### 2️⃣ Renomear diretórios *_bonus (do mais profundo para o mais alto)
find . -depth -type d -name "*_bonus" | while read -r dir; do
    parent=$(dirname "$dir")
    base=$(basename "$dir" _bonus)

    new="$parent/$base"

    mv -- "$dir" "$new"
    echo "Pasta renomeada: $dir -> $new"
done

