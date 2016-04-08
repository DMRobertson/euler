#1. Check that the rust file exists.
if [ ! -f src/euler$1.rs ]; then
	echo "Can't find src/euler$1.rs"
	exit 1
fi

#2. If needed, create log and target folders.
[ ! -d log    ] && mkdir log
[ ! -d target ] && mkdir target
#3. Remove any previous binaries for this problem.
[ -f target/euler$1* ] && rm target/euler$1*

#4. Compile and test the given problem, saving stdout to the log directory.
rustc --out-dir target --test src/euler$1.rs
./target/euler$1 > log/euler$1

if [ $? -ne 0 ]; then
	echo "Error in test, output shown below."
	cat log/euler$1.test
	exit 2
fi

#5. Compile again with the optimised flag, and run.
rustc -O --out-dir target src/euler$1.rs
./target/euler$1
