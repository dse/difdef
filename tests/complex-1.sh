cat >a <<EOF
foo
EOF
cat >b <<EOF
bar
EOF

./diffn --simple -DA a -DB b >out
cat >expected <<EOF
#ifdef A
foo
#endif /* A */
#ifdef B
bar
#endif /* B */
EOF
diff expected out

./diffn --complex -DA a -DB b >out
cat >expected <<EOF
#ifdef A
foo
#else /* B */
bar
#endif /* A || B */
EOF
diff expected out

touch c
./diffn --complex -DA a -DB b -DC c >out
cat >expected <<EOF
#ifdef A
foo
#elif defined(B)
bar
#endif /* A || B */
EOF
diff expected out

rm -f a b c expected out
