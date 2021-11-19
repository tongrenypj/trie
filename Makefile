all : trie.test

trie.test : trie_generic.h trie_test.cpp
	g++ trie_test.cpp -o $@ -O2 -g -Wall


clean:
	rm -f trie.test
