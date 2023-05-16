\\cat Makefile
\\echo a
\\echo a | cat Makefile
\\echo a < in | cat Makefile
\\jkl
\\jkl | echo a
\\jkl | export a=youhou
\\jkl | ls
\\echo a | jlk
\\export a=youhou | jkl
\\ls | jkl
\\echo < bad
\\echo > nice
\\echo < no_perm
\\echo >> no_perm
\\echo > no_perm
\\ls < bad
\\ls > nice
\\ls < no_perm
\\ls >> no_perm
\\ls > no_perm
\\fjkadsjfkajkdfljas < bad
\\fjkadsjfkajkdfljas > nice
\\fjkadsjfkajkdfljas < no_perm
\\fjkadsjfkajkdfljas >> no_perm
\\fjkadsjfkajkdfljas > no_perm
\\echo a && echo b
\\echo a || echo b
\\(echo a && echo b)
\\ls && ls
\\asdjfk && jaslk
\\(jfkdls && echo b
(cat << EOF | cat -e && cat test && cat Makefile) || cat << est
