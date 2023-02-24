#!/bin/sh
find . -name "*.txt" | while read f
do
    dos2unix "$f" >/dev/null 2>&1 ||:
    iconv -f gb18030 -t utf8 -o "$f.new" "$f" && mv -f "$f.new" "$f"
    if not [ $? -eq 0 ]; then
        echo $f;
    fi
done

find . -name "*.c" | while read f
do
    dos2unix "$f" >/dev/null 2>&1 ||:
    iconv -f gb18030 -t utf8 -o "$f.new" "$f" && mv -f "$f.new" "$f"
    if not [ $? -eq 0 ]; then
        echo $f;
    fi
done
find . -name "*.C" | while read f
do
    dos2unix "$f" >/dev/null 2>&1 ||:
    iconv -f gb18030 -t utf8 -o "$f.new" "$f" && mv -f "$f.new" "$f"
    if not [ $? -eq 0 ]; then
        echo $f;
    fi
done
find . -name "*.h" | while read f
do
    dos2unix "$f" >/dev/null 2>&1 ||:
    iconv -f gb18030 -t utf8 -o "$f.new" "$f" && mv -f "$f.new" "$f"
    if not [ $? -eq 0 ]; then
        echo $f;
    fi
done
find . -name "*.H" | while read f
do
    dos2unix "$f" >/dev/null 2>&1 ||:
    iconv -f gb18030 -t utf8 -o "$f.new" "$f" && mv -f "$f.new" "$f"
    if not [ $? -eq 0 ]; then
        echo $f;
    fi
done
