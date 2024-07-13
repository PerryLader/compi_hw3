rm -f lex.yy.c
rm -f parser.tab.*pp
rm -f hw3
flex scanner.lex 
bison -Wcounterexamples -d parser.ypp
g++ -std=c++17 -o hw3.out *.c *.cpp 
cp hw3.out tests/
./run_tests.sh




