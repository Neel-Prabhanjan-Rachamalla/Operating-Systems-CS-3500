all:
	gcc parent.c -o parent
	gcc child.c -o child
clean:
	rm -rf parent child Child_W Child_R
clean2:
	rm -rf parentfile childfile Child0_W Child0_R Child1_W Child1_R Child2_W Child2_R Child3_W Child3_R Child4_W Child4_R Child5_W Child5_R
all2:
	
	gcc parentfile.c -o parentfile
	gcc childfile.c -o childfile
	
	gnome-terminal -- ./parentfile
	gnome-terminal -- ./childfile 0
	gnome-terminal -- ./childfile 1
	gnome-terminal -- ./childfile 2
	gnome-terminal -- ./childfile 3
	gnome-terminal -- ./childfile 4
	gnome-terminal -- ./childfile 5