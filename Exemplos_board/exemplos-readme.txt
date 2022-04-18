# gerar tabuleiros vazios
time ./palavras -t 7x7   -j 2 -n 0 -o 7x7-vazio.txt
time ./palavras          -j 2 -n 0 -o 9x9-vazio.txt
time ./palavras -t 11x11 -j 2 -n 0 -o 11x11-vazio.txt
# exemplo de modo de jogo 2
time ./palavras -t 7x7   -j 2 -d /usr/share/dict/words         -o 7x7-j2-us.txt   -r 7x7-j2-us-registo.txt > 7x7-j2-us-log.txt
time ./palavras -t 7x7   -j 2 -d /usr/share/hunspell/pt_PT.dic -o 7x7-j2-pt.txt   -r 7x7-j2-pt-registo.txt > 7x7-j2-pt-log.txt
time ./palavras          -j 2 -d /usr/share/dict/words         -o 9x9-j2-us.txt   -r 9x9-j2-us-registo.txt > 9x9-j2-us-log.txt
time ./palavras          -j 2 -d /usr/share/hunspell/pt_PT.dic -o 9x9-j2-pt.txt   -r 9x9-j2-pt-registo.txt > 9x9-j2-pt-log.txt
time ./palavras -t 11x11 -j 2 -d /usr/share/dict/words         -o 11x11-j2-us.txt -r 11x11-j2-us-registo.txt > 11x11-j2-us-log.txt
time ./palavras -t 11x11 -j 2 -d /usr/share/hunspell/pt_PT.dic -o 11x11-j2-pt.txt -r 11x11-j2-pt-registo.txt > 11x11-j2-pt-log.txt
# exemplo de modo de jogo 3
time ./palavras -t 7x7   -j 3 -d /usr/share/dict/words         -o 7x7-j3-us.txt   -r 7x7-j3-us-registo.txt -m 20 -l letras-us.txt > 7x7-j3-us-log.txt
time ./palavras -t 7x7   -j 3 -d /usr/share/hunspell/pt_PT.dic -o 7x7-j3-pt.txt   -r 7x7-j3-pt-registo.txt -m 20 -l letras-pt.txt > 7x7-j3-pt-log.txt
time ./palavras          -j 3 -d /usr/share/dict/words         -o 9x9-j3-us.txt   -r 9x9-j3-us-registo.txt -m 20 -l letras-us.txt > 9x9-j3-us-log.txt
time ./palavras          -j 3 -d /usr/share/hunspell/pt_PT.dic -o 9x9-j3-pt.txt   -r 9x9-j3-pt-registo.txt -m 20 -l letras-pt.txt > 9x9-j3-pt-log.txt
time ./palavras -t 11x11 -j 3 -d /usr/share/dict/words         -o 11x11-j3-us.txt -r 11x11-j3-us-registo.txt -m 20 -l letras-us.txt > 11x11-j3-us-log.txt
time ./palavras -t 11x11 -j 3 -d /usr/share/hunspell/pt_PT.dic -o 11x11-j3-pt.txt -r 11x11-j3-pt-registo.txt -m 20 -l letras-pt.txt > 11x11-j3-pt-log.txt
# exemplo de modo de jogo 4
time ./palavras -t 7x7   -j 4 -d /usr/share/dict/words         -o 7x7-j4-us.txt   -r 7x7-j4-us-registo.txt -m 20 -l letras-us.txt > 7x7-j4-us-log.txt
time ./palavras -t 7x7   -j 4 -d /usr/share/hunspell/pt_PT.dic -o 7x7-j4-pt.txt   -r 7x7-j4-pt-registo.txt -m 20 -l letras-pt.txt > 7x7-j4-pt-log.txt
time ./palavras          -j 4 -d /usr/share/dict/words         -o 9x9-j4-us.txt   -r 9x9-j4-us-registo.txt -m 20 -l letras-us.txt > 9x9-j4-us-log.txt
time ./palavras          -j 4 -d /usr/share/hunspell/pt_PT.dic -o 9x9-j4-pt.txt   -r 9x9-j4-pt-registo.txt -m 20 -l letras-pt.txt > 9x9-j4-pt-log.txt
time ./palavras -t 11x11 -j 4 -d /usr/share/dict/words         -o 11x11-j4-us.txt -r 11x11-j4-us-registo.txt -m 20 -l letras-us.txt > 11x11-j4-us-log.txt
time ./palavras -t 11x11 -j 4 -d /usr/share/hunspell/pt_PT.dic -o 11x11-j4-pt.txt -r 11x11-j4-pt-registo.txt -m 20 -l letras-pt.txt > 11x11-j4-pt-log.txt

