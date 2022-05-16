antlr4 -o ../src/woglac/parser -Dlanguage=Cpp Woglac.g4

# Without this, you'd get compile errors on MSVC2019
sed -i "s/u8\"/\"/g" "../../src/woglac/parser/WoglacLexer.cpp"