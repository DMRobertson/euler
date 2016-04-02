if [ ! -f src/euler$1.rs ]; then
	echo "Can't find src/euler$1.rs"
	exit 1
fi

[ ! -d log    ] && mkdir log
[ ! -d target ] && mkdir target
rm target/euler$1*

rustc --out-dir target --test src/euler$1.rs
./target/euler$1 > log/euler$1

if [ $? -ne 0 ]; then
	echo "Error in test, output shown below."
	cat log/euler$1
	exit 2
fi

rustc --out-dir target src/euler$1.rs
./target/euler$1
