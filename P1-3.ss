car + cdr - cons / if * else = and >
or > not >= define <= number? ( symbol? ) list? '
zero?  null?  char?  modulo cadr cddr caddr cdddr
some more symbols and a line of numbers
1 123 12.23 .34 123 -1 -2.2 +15 +.5 +5.
round + modulo

car+cdr-cons/if*else=and>
or>not>=define<=number?(symbol?)list?'
zero?null?char?modulocaddddddddr
somemoresymbolsandalineofnumbers
112312.23.34123-1-2.2+15+.5+5.
round+modulo

car+cdr-cons/if*else=and>
or>not>=define<=number?(symbol?)list?'
zero?%null?#char?modulo
(car '(abc def ghi))
(cons 'abd '(1 2 3))
(cons 'a 'b)
(cons (car '(a b c d)) (cddr '(a b c d)))
(cons (cadr $(a b c d)) (caddr '(a ^ c d)))
(cons (cadr '(a b c d)) (caddr '(a b c d)))
(car '(abc def ghi))
(cons 'abd '(1 2 3))
(cons 'a 'b)
(cons (car '(a b c d)) (cddr '(a b c d)))
(cons (cadr '(a b c d)) (caddr '(a b c d)))

(define (funky L)
	(if (list? L)
		(if (< (length L) 3)
			L
			(cons (car L) (cons (cadr L) (funky (cdddr L))))
		)
		'()
	)
)

(funky '(a b c 1 2 3 x y z 7 8 9))
this file contains
int double  ++ += and +
    int var
var += 123456789 + abc++
var+=123456789+abc++
This     line contains@least $3$errors
symbol 1 1. 1.2 .2 car cdr cons if else and or not define number? string string? lambda list? zero? null? char? modulo error + - / * = > < >= <= ( ) '
 ignore this line please (cdr '(abcd) '(efgh))
"string literal test"
symbol 1 1.2 define number? anobvious$error*thing (cdr '(car (cons '(abc) '(def)))
anobvious$error*thing2
(define (lambda (x y) (cons x y)))
<=>=<>) round % modulo 
(car(cdr'(1 2 3)))
(+ 1.23 466)
+123identifier-int/abc.456*i%--++
i1 ===!=i2><>=<= &&||main!float
& 123.456|123.^while <<.456>>$void
~abc.xyz}123.xyz){ #(else@
,?:
