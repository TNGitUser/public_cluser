for	r in 0 127 255; do
	for g in 0 127 255; do
		for b in 0 127 255; do
			printf "\x1b[38;2;${r};${g};${b}m($r,$g,$b)\x1b[0m ";
		done;
	printf "\n";
	done;
done;
